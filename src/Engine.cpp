#include "stdafx.h"
#include "Engine.h"

namespace script_engine {

	Engine::Engine(IScriptEngineSpi* engineSpi, const int& argc, const char** argv) :
		IScriptEngineApi(engineSpi)
	{
		for (int i = 0; i < argc; ++i)
			m_Argvs.emplace_back(argv[i]);
	}
	Engine::~Engine() {
	}

	bool Engine::Start()
	{
		if (m_Ready.load()) return true;
		if (!m_pEngineSpi)
			return false;

		m_Ready.store(true);
		return m_Ready.load();
	}
	void Engine::Release()
	{
		delete this;
	}
	void Engine::Stop()
	{
		if (!m_Ready.load()) return;
		for (auto it = m_ScriptObjCacheQ.begin(); it != m_ScriptObjCacheQ.end(); ++it) {
			(*it)->Release();
		}
		for (const auto& it : m_ScriptObjQ) {
			it.second->Release();
		}
		m_ScriptObjCacheQ.clear();
		m_ScriptObjQ.clear();
		m_Ready.store(false);
	}
	bool Engine::Ready() const
	{
		return m_Ready.load();
	}
	IScriptObj* Engine::AssignScriptObj(const IScriptObj* pScriptObj) {
		if (!pScriptObj)
			return nullptr;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		ScriptObj* assign = new ScriptObj(pScriptObj);
		if (assign->Identify().empty()) {
			SK_DELETE_PTR(assign);
			return nullptr;
		}
		auto found = m_ScriptObjQ.find(assign->Identify());
		if (found != m_ScriptObjQ.end()) {
			SK_DELETE_PTR(found->second);
			m_ScriptObjQ.erase(assign->Identify());
		}
		return m_ScriptObjQ.emplace(std::make_pair(assign->Identify(), assign)).first->second;
	}
	IScriptObj* Engine::AssignScriptObj(const std::string& scriptObjPak) {
		if (scriptObjPak.empty())
			return nullptr;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		ScriptObj* assign = new ScriptObj(scriptObjPak);
		if (assign->Identify().empty()) {
			SK_DELETE_PTR(assign);
			return nullptr;
		}
		auto found = m_ScriptObjQ.find(assign->Identify());
		if (found!= m_ScriptObjQ.end()) {
			SK_DELETE_PTR(found->second);
			m_ScriptObjQ.erase(assign->Identify());
		}
		return m_ScriptObjQ.emplace(std::make_pair(assign->Identify(), assign)).first->second;
	}
	IScriptObj* Engine::CreateScriptObj(const std::string& from) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		auto pScriptObj = new ScriptObj(from);
		m_ScriptObjCacheQ.emplace_back(pScriptObj);
		return dynamic_cast<IScriptObj*>(pScriptObj);
	}
	IScriptObj* Engine::SearchScriptObj(const IScriptObj* pSearch) {
		if (!pSearch)
			return nullptr;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		auto found = m_ScriptObjQ.find(pSearch->Identify());
		if (found == m_ScriptObjQ.end())
			return nullptr;
		return dynamic_cast<IScriptObj*>(found->second);
	}
	IScriptObj* Engine::CompileCC(const IScriptObj* pRequest) {
		if (!pRequest)
			return nullptr;
		if (pRequest->BufferCC().empty() || pRequest->Identify().empty())
			return nullptr;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		auto found = m_ScriptObjQ.find(pRequest->Identify());
		if (found != m_ScriptObjQ.end()) {
			if (!found->second->BufferBC().empty() && \
				found->second->TimeCompileCC() > 0 && \
				!memcmp(found->second->BufferCC().data(), pRequest->BufferCC().data(), found->second->BufferCC().size())) {
				return dynamic_cast<IScriptObj*>(found->second);
			}
			else {
				found->second->Release();
				m_ScriptObjQ.erase(found);
			}
		}
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmPrinters();
		llvm::InitializeAllAsmParsers();
		llvm::SmallVector<const char*, 256> Argvs;
		for (auto& argv : m_Argvs) {
			Argvs.emplace_back(argv.c_str());
		}
		auto Compiler = std::make_shared<clang::CompilerInstance>();
		auto Invocation = std::make_shared<clang::CompilerInvocation>();
		Compiler->createDiagnostics();
		do {
			if (!clang::CompilerInvocation::CreateFromArgs(*Invocation, llvm::makeArrayRef(Argvs).slice(1), Compiler->getDiagnostics(), Argvs[0]))
				break;
			if (Invocation->getFrontendOpts().Inputs.size() == 1) {
				if (Invocation->getFrontendOpts().Inputs[0].getFile() == "-")
					Invocation->getFrontendOpts().Inputs.clear();
			}
			Invocation->getFrontendOpts().Inputs.push_back(clang::FrontendInputFile(".cc", clang::Language::CXX));
			Invocation->getPreprocessorOpts().addRemappedFile(".cc", llvm::MemoryBuffer::getMemBuffer(pRequest->BufferCC()).release());
			llvm::SmallVector<char, 256> IRBuffer;
			std::unique_ptr<llvm::raw_pwrite_stream> IRStream(new llvm::raw_svector_ostream(IRBuffer));
			Compiler->setOutputStream(std::move(IRStream));
			Compiler->setInvocation(Invocation);
			if (!clang::ExecuteCompilerInvocation(Compiler.get()))
				break;
			if (!llvm::StringRef(IRBuffer.data()).startswith("BC"))
				break;
			auto pScriptObj = new ScriptObj(pRequest);
			pScriptObj->TimeCompileCCUpdate();
			pScriptObj->BufferBC(std::string(IRBuffer.data(), IRBuffer.size()));
			return dynamic_cast<IScriptObj*>(m_ScriptObjQ.emplace(std::make_pair(pScriptObj->Identify(), pScriptObj)).first->second);
		} while (0);
		return nullptr;
	}
	IScriptObj* Engine::CompileBC(const IScriptObj* pRequest) {
		if (!pRequest)
			return nullptr;
		if (pRequest->Identify().empty())
			return nullptr;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		ScriptObj* pScriptObj = nullptr;
		auto found = m_ScriptObjQ.find(pRequest->Identify());
		if (found == m_ScriptObjQ.end()) {
			if (pRequest->BufferBC().empty())
				return nullptr;
			if (pRequest->EntryFun().empty())
				return nullptr;
			pScriptObj = new ScriptObj(pRequest);
		}
		else {
			pScriptObj = found->second;
			if (!pScriptObj)
				return nullptr;

			if (!pScriptObj->BufferBC().empty() && \
				pScriptObj->TimeCompileBC() > 0 && \
				!pScriptObj->EntryFun().empty() && \
				pScriptObj->EntryPtr() > 0 && \
				!memcmp(pScriptObj->BufferBC().data(), pRequest->BufferBC().data(), pScriptObj->BufferBC().size()) && \
				pScriptObj->TimeCompileBC() == pRequest->TimeCompileBC()) {
				return dynamic_cast<IScriptObj*>(pScriptObj);
			}
		}

		pScriptObj->EntryPtr(0);
		pScriptObj->TimeCompileBCUpdate();
		if (pScriptObj->Compile()) {
			return dynamic_cast<IScriptObj*>(m_ScriptObjQ.emplace(std::make_pair(pScriptObj->Identify(), pScriptObj)).first->second);
		}
		return nullptr;
	}

}///namespace script_engine