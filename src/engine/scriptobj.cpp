#include "stdafx.h"
#include "ScriptObj.h"

namespace local {

#if 0
	ScriptObj::ScriptObj(const std::string& obj) {
		*this = obj;
	}
	ScriptObj::ScriptObj(const ScriptObj& obj) {
		*this = obj;
	}
	ScriptObj::ScriptObj(const IScriptObj* obj) {
		*this = obj;
	}
	ScriptObj::~ScriptObj() {

	}
	void ScriptObj::Release() const {
		delete this;
	}
	void ScriptObj::Reset() {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_BufferBC.clear();
		m_BufferCC.clear();
		m_EntryFun.clear();
		m_ID = 0;
		m_EntryPtr = 0;
		m_TimeCompileBC = 0;
		m_TimeCompileCC = 0;
		m_BindQ.clear();
	}
	void ScriptObj::operator=(const std::string& obj) {
		Packet(obj);
	}
	void ScriptObj::Assign(const IScriptObj* assign) {
		*this = assign;
	}
	void ScriptObj::operator=(const ScriptObj& obj) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_BufferBC = obj.m_BufferBC;
		m_BufferCC = obj.m_BufferCC;
		m_EntryFun = obj.m_EntryFun;
		m_ID = obj.m_ID;
		m_EntryPtr = obj.m_EntryPtr;
		m_TimeCompileBC = obj.m_TimeCompileBC;
		m_TimeCompileCC = obj.m_TimeCompileCC;
		m_Signature = obj.m_Signature;
		m_ServiceIdentify = obj.m_ServiceIdentify;
		m_BindQ = obj.m_BindQ;
	}
	void ScriptObj::operator=(const IScriptObj* obj) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_Signature = obj->Signature();
		m_ServiceIdentify = obj->ServiceIdentify();
		m_BufferBC = obj->BufferBC();
		m_BufferCC = obj->BufferCC();
		m_EntryFun = obj->EntryFun();
		m_ID = obj->ID();
		m_EntryPtr = obj->EntryPtr();
		m_TimeCompileBC = obj->TimeCompileBC();
		m_TimeCompileCC = obj->TimeCompileCC();
		m_BindQ = obj->BindGet();
	}
	void ScriptObj::BindAppend(const std::string& obj) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_BindQ.insert(obj);
	}
	void ScriptObj::BindRemove(const std::string& obj) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		auto found = m_BindQ.find(obj);
		if (found != m_BindQ.end()) {
			m_BindQ.erase(found);
		}
	}
	bool ScriptObj::BindEmpty() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_BindQ.empty();
	}
	size_t ScriptObj::BindSize() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_BindQ.size();
	}
	std::set<std::string> ScriptObj::BindGet() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_BindQ;
	}
	bool ScriptObj::BindCheck(const std::string& assign) const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_BindQ.find(assign) != m_BindQ.end();
	}
	void ScriptObj::BufferBC(const std::string& bc) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_BufferBC = bc;
	}
	const std::string& ScriptObj::BufferBC() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_BufferBC;
	}
	void ScriptObj::BufferCC(const std::string& cc) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_BufferCC = cc;
	}
	const std::string& ScriptObj::BufferCC() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_BufferCC;
	}
	void ScriptObj::EntryFun(const std::string& entry) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_EntryFun = entry;
	}
	const std::string& ScriptObj::EntryFun() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_EntryFun;
	}
	const std::uintptr_t& ScriptObj::EntryPtr() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_EntryPtr;
	}
	void ScriptObj::EntryPtr(const std::uintptr_t& ptr) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_EntryPtr = ptr;
	}
	const std::uint64_t& ScriptObj::ID() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_ID;
	}
	void ScriptObj::ID(const std::uint64_t& id) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_ID = id;
	}
	void ScriptObj::Signature(const std::string& signature) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_Signature = signature;
	}
	void ScriptObj::ServiceIdentify(const std::string& serviceIdentify) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_ServiceIdentify = serviceIdentify;
	}
	const std::string& ScriptObj::Signature() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return		m_Signature;
	}
	const std::string& ScriptObj::ServiceIdentify() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_ServiceIdentify;
	}
	bool ScriptObj::VerifyCC() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		if (m_Signature.empty() || m_BufferCC.empty())
			return false;
		return true;
	}
	bool ScriptObj::VerifyBC() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		if (m_EntryFun.empty() || m_Signature.empty() || m_BufferBC.empty())
			return false;
		if (m_BufferBC.size() < 2)
			return false;
		if (memcmp("BC", m_BufferBC.data(), 2))
			return false;
		return true;
	}
	std::string ScriptObj::Identify() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		if (!m_ServiceIdentify.empty())
			return m_ServiceIdentify + "@" + m_Signature;
		return m_Signature;
	}
	void ScriptObj::TargetSystem(const EnTargetSystem& TargetSystem) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_TargetSystem = TargetSystem;
	}
	const EnTargetSystem& ScriptObj::TargetSystem() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_TargetSystem;
	}
	void ScriptObj::TimeCompileCC(const std::uint64_t& time) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_TimeCompileCC = time;
	}
	void ScriptObj::TimeCompileBC(const std::uint64_t& time) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_TimeCompileBC = time;
	}
	const std::uint64_t& ScriptObj::TimeCompileBC() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_TimeCompileBC;
	}
	const std::uint64_t& ScriptObj::TimeCompileCC() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_TimeCompileCC;
	}
	void ScriptObj::TimeCompileBCUpdate() {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_TimeCompileBC = \
			std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
	void ScriptObj::TimeCompileCCUpdate() {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_TimeCompileCC = \
			std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
	bool ScriptObj::EnableFlag() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_EnableFlag.load();
	}
	void ScriptObj::EnableFlag(const bool& flag) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_EnableFlag.store(flag);
	}
	bool ScriptObj::StartFlag() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_StartFlag.load();
	}
	void ScriptObj::StartFlag(const bool& flag) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_StartFlag.store(flag);
	}
	const std::string& ScriptObj::CachePathname() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_CachePathname;
	}
	void ScriptObj::CachePathname(const std::string& pathname) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_CachePathname = pathname;
	}
	const std::string& ScriptObj::CCCachePathname() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_CCCachePathname;
	}
	void ScriptObj::CCCachePathname(const std::string& pathname) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		m_CCCachePathname = pathname;
	}
	std::string ScriptObj::Packet() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		rapidjson::Document jdoc;
		auto& jallocator = jdoc.GetAllocator();
		jdoc.SetObject();

		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_ServiceIdentify), jallocator).Move(),
			rapidjson::Value().SetString(m_ServiceIdentify.c_str(), jallocator).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_Signature), jallocator).Move(),
			rapidjson::Value().SetString(m_Signature.c_str(), jallocator).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_EntryFun), jallocator).Move(),
			rapidjson::Value().SetString(m_EntryFun.c_str(), jallocator).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_TargetSystem), jallocator).Move(),
			rapidjson::Value().SetUint64(static_cast<std::uint64_t>(m_TargetSystem)).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_ID), jallocator).Move(),
			rapidjson::Value().SetUint64(m_ID).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_TimeCompileBC), jallocator).Move(),
			rapidjson::Value().SetUint64(m_TimeCompileBC).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_TimeCompileCC), jallocator).Move(),
			rapidjson::Value().SetUint64(m_TimeCompileCC).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_StartFlag), jallocator).Move(),
			rapidjson::Value().SetBool(m_StartFlag.load()).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_EnableFlag), jallocator).Move(),
			rapidjson::Value().SetBool(m_EnableFlag.load()).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_CachePathname), jallocator).Move(),
			rapidjson::Value().SetString(m_CachePathname.c_str(), jallocator).Move(), jallocator);
		//!@
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_CCCachePathname), jallocator).Move(),
			rapidjson::Value().SetString(m_CCCachePathname.c_str(), jallocator).Move(), jallocator);
		//!@
		if (!m_BufferBC.empty()) {
			auto encode = Global::Encode6Bit(m_BufferBC);
			if (encode.empty())
				return "";
			jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_BufferBC), jallocator).Move(),
				rapidjson::Value().SetString(encode.c_str(), jallocator).Move(),
				jallocator);
		}
		//!@
		if (!m_BufferCC.empty()) {
			auto encode = Global::Encode6Bit(m_BufferCC);
			if (encode.empty())
				return "";
			jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_BufferCC), jallocator).Move(),
				rapidjson::Value().SetString(encode.c_str(), jallocator).Move(),
				jallocator);
		}

		//!@
		rapidjson::Value jarray_bind_s(rapidjson::kArrayType);
		for (const auto& obj : m_BindQ) {
			rapidjson::Value jobj_bind_obj(rapidjson::kObjectType);
			jobj_bind_obj.AddMember(rapidjson::Value().SetString("TargetObj", jallocator).Move(),
				rapidjson::Value().SetString(obj.c_str(), jallocator).Move(),
				jallocator);
			jarray_bind_s.PushBack(jobj_bind_obj, jallocator);
		}
		jdoc.AddMember(rapidjson::Value().SetString(SK_VNAME(m_BindQ), jallocator).Move(),
			jarray_bind_s,
			jallocator);

		rapidjson::StringBuffer jbuffer;
		if (jdoc.IsObject()) {
			rapidjson::Writer<rapidjson::StringBuffer> jwriter(jbuffer);
			jdoc.Accept(jwriter);
		}
		return std::string(jbuffer.GetString(), jbuffer.GetLength());
	}
	bool ScriptObj::Packet(const std::string& jsonPak) {
		if (jsonPak.empty())
			return false;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		rapidjson::Document jdoc;
		if (jdoc.Parse(jsonPak.data()).HasParseError())
			return false;
		if (!jdoc.IsObject())
			return false;
		if (!jdoc.HasMember(SK_VNAME(m_Signature)))
			return false;
		auto& vSignature = jdoc[SK_VNAME(m_Signature)];
		if (!vSignature.IsString())
			return false;
		m_Signature = std::string(vSignature.GetString(), vSignature.GetStringLength());

		//!@
		if (jdoc.HasMember(SK_VNAME(m_BindQ))) {
			auto& vBindQ = jdoc[SK_VNAME(m_BindQ)];
			if (vBindQ.IsArray()) {
				for (auto it = vBindQ.Begin(); it != vBindQ.End(); ++it) {
					if (!it->IsObject())
						continue;
					if (!it->HasMember("TargetObj"))
						continue;
					auto& vTargetObj = (*it)["TargetObj"];
					if (!vTargetObj.IsString())
						continue;
					m_BindQ.insert(std::string(vTargetObj.GetString(), vTargetObj.GetStringLength()));
				}
			}
		}


		//!@
		if (jdoc.HasMember(SK_VNAME(m_ServiceIdentify))) {
			auto& vServiceIdentify = jdoc[SK_VNAME(m_ServiceIdentify)];
			if (vServiceIdentify.IsString())
				m_ServiceIdentify = std::string(vServiceIdentify.GetString(), vServiceIdentify.GetStringLength());
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_TargetSystem))) {
			auto& vTargetSystem = jdoc[SK_VNAME(m_TargetSystem)];
			if (vTargetSystem.IsUint64())
				m_TargetSystem = static_cast<EnTargetSystem>(vTargetSystem.GetUint64());
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_ID))) {
			auto& vID = jdoc[SK_VNAME(m_ID)];
			if (vID.IsUint64())
				m_ID = vID.GetUint64();
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_TimeCompileBC))) {
			auto& vTimeCompileBC = jdoc[SK_VNAME(m_TimeCompileBC)];
			if (vTimeCompileBC.IsUint64())
				m_TimeCompileBC = vTimeCompileBC.GetUint64();
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_TimeCompileCC))) {
			auto& vTimeCompileCC = jdoc[SK_VNAME(m_TimeCompileCC)];
			if (vTimeCompileCC.IsUint64())
				m_TimeCompileCC = vTimeCompileCC.GetUint64();
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_EntryPtr))) {
			auto& vEntryPtr = jdoc[SK_VNAME(m_EntryPtr)];
			if (vEntryPtr.IsUint64())
				m_EntryPtr = vEntryPtr.GetUint64();
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_EntryFun))) {
			auto& vEntryFun = jdoc[SK_VNAME(m_EntryFun)];
			if (vEntryFun.IsString())
				m_EntryFun = std::string(vEntryFun.GetString(), vEntryFun.GetStringLength());
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_EnableFlag))) {
			auto& vEnableFlag = jdoc[SK_VNAME(m_EnableFlag)];
			if (vEnableFlag.IsBool())
				m_EnableFlag = vEnableFlag.GetBool();
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_StartFlag))) {
			auto& vStartFlag = jdoc[SK_VNAME(m_StartFlag)];
			if (vStartFlag.IsBool())
				m_StartFlag = vStartFlag.GetBool();
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_CachePathname))) {
			auto& vCachePathname = jdoc[SK_VNAME(m_CachePathname)];
			if (vCachePathname.IsString())
				m_CachePathname = std::string(vCachePathname.GetString(), vCachePathname.GetStringLength());
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_CCCachePathname))) {
			auto& vCCCachePathname = jdoc[SK_VNAME(m_CCCachePathname)];
			if (vCCCachePathname.IsString())
				m_CCCachePathname = std::string(vCCCachePathname.GetString(), vCCCachePathname.GetStringLength());
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_BufferBC))) {
			auto& vBufferBC = jdoc[SK_VNAME(m_BufferBC)];
			if (vBufferBC.IsString()) {
				m_BufferBC = Global::Decode6Bit(std::string(vBufferBC.GetString(), vBufferBC.GetStringLength()));
			}
		}

		//!@
		if (jdoc.HasMember(SK_VNAME(m_BufferCC))) {
			auto& vBufferCC = jdoc[SK_VNAME(m_BufferCC)];
			if (vBufferCC.IsString())
				m_BufferCC = Global::Decode6Bit(std::string(vBufferCC.GetString(), vBufferCC.GetStringLength()));
		}

		return true;
	}

	bool ScriptObj::Finish() const {
		auto cache = Packet();
		if (cache.empty())
			return false;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		if (m_CachePathname.empty())
			return false;
		std::ofstream of(m_CachePathname, std::ios::out | std::ios::trunc | std::ios::binary);
		if (of.is_open()) {
			of << cache;
			of.close();
			return true;
		}
		return false;
	}


	bool ScriptObj::Compile() {
		if (m_EntryFun.empty() || m_BufferBC.empty())
			return false;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();
		llvm::InitializeNativeTargetAsmParser();
		std::unique_ptr<llvm::Module> M = \
			llvm::parseIR(llvm::MemoryBuffer::getMemBuffer(m_BufferBC)->getMemBufferRef(), m_ParseIRErr, m_Context);
		if (!M)
			return false;
		auto Mod = M.get();
		if (!Mod)
			return false;
		llvm::EngineBuilder builder(std::move(M));
		m_pEE = std::shared_ptr<llvm::ExecutionEngine>(builder.setEngineKind(llvm::EngineKind::JIT).create());
		if (!m_pEE)
			return false;
		builder.setMCJITMemoryManager(std::unique_ptr<llvm::RTDyldMemoryManager>(new llvm::SectionMemoryManager()));
		m_pEE->finalizeObject();
		m_EntryPtr = m_pEE->getFunctionAddress(m_EntryFun);
		return m_EntryPtr != 0;
	}
#endif
}///namespace local