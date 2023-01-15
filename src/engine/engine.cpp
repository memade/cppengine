#include "stdafx.h"
#include "Engine.h"

namespace local {
 CppEngine::CppEngine() {
  Init();
 }
 CppEngine::~CppEngine() {
  UnInit();
 }
 void CppEngine::Init() {
  m_pEngineConfig = new EngineConfig();
 }
 void CppEngine::UnInit() {
  m_pEngineConfig->Release();
 }
 void CppEngine::Release() const {
  delete this;
 }
 bool CppEngine::Ready() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_IsOpen.load();
 }
 bool CppEngine::Start() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_IsOpen.load())
    break;

#if ENABLE_LLVM
   llvm::install_fatal_error_handler([](void* UserData, const char* Message,
    bool GenCrashDiag) {
     llvm::sys::RunInterruptHandlers();
   llvm::sys::Process::Exit(GenCrashDiag ? 70 : 1);
    }, nullptr);
#endif

   m_IsOpen.store(true);
  } while (0);
  return m_IsOpen.load();
 }
 void CppEngine::Stop() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_IsOpen.load())
    break;

#if ENABLE_LLVM
   llvm::llvm_shutdown_obj();
#endif
  } while (0);
  m_IsOpen.store(false);
 }
 IScript* CppEngine::CreateScriptObj() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<IScript*>(new CppScript());
 }
 ICompileRoute* CppEngine::CreateCompileRoute() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<ICompileRoute*>(new CompileRoute());
 }
 IEngineConfig* CppEngine::EngineConfigGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_pEngineConfig;
 }
 bool CppEngine::CompileBC(ICompileRoute* route) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!route)
    break;
   auto source = route->BufferBC();
   if (source.empty())
    break;

#if 0
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
#endif


   result = true;
  } while (0);
  return result;
 }
 bool CppEngine::CompileCC(ICompileRoute* route) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  time_t time_compile_begin = shared::Win::Time::TimeStamp<std::chrono::milliseconds>(), \
   time_compile_end = time_compile_begin;
  do {
   if (!route)
    break;
   auto src = route->Source();
   if (src.empty())
    break;
   if (route->EnableSourceEncrypt()) {
    src = shared::Win::Encryption::WemadeDecode(src);
    if (src.empty())
     break;
   }
#if ENABLE_LLVM
   llvm::InitializeAllTargets();
   llvm::InitializeAllTargetMCs();
   llvm::InitializeAllAsmPrinters();
   llvm::InitializeAllAsmParsers();
   do {
    if (!route->EnableDefault_internal_isystem())
     break;
    auto default_internal_isystem_s = m_pEngineConfig->Default_internal_isystem_s_get();
    if (default_internal_isystem_s.empty())
     break;
    for (const auto& internal_isystem_node : default_internal_isystem_s)
     route->CompileArgsGet()->Push(internal_isystem_node, "-internal-isystem");
   } while (0);
   auto llvmArgvs = dynamic_cast<CompileArgs*>(route->CompileArgsGet())->Args();
   auto Compiler = std::make_shared<clang::CompilerInstance>();
   auto Invocation = std::make_shared<clang::CompilerInvocation>();
   Compiler->createDiagnostics();
   if (!clang::CompilerInvocation::CreateFromArgs(*Invocation, llvm::makeArrayRef(llvmArgvs).slice(1), Compiler->getDiagnostics(), llvmArgvs[0]))
    break;
   if (Invocation->getFrontendOpts().Inputs.size() == 1) {
    if (Invocation->getFrontendOpts().Inputs[0].getFile() == "-")
     Invocation->getFrontendOpts().Inputs.clear();
   }
   Invocation->getFrontendOpts().Inputs.push_back(clang::FrontendInputFile(".cc", clang::Language::CXX));
   Invocation->getPreprocessorOpts().addRemappedFile(".cc", llvm::MemoryBuffer::getMemBuffer(src).release());
   llvm::SmallVector<char, 256> IRBuffer;
   std::unique_ptr<llvm::raw_pwrite_stream> IRStream(new llvm::raw_svector_ostream(IRBuffer));
   Compiler->setOutputStream(std::move(IRStream));
   Compiler->setInvocation(Invocation);
   if (!clang::ExecuteCompilerInvocation(Compiler.get()))
    break;
   if (!llvm::StringRef(IRBuffer.data()).startswith("BC"))
    break;
   route->BufferBC(std::string(IRBuffer.data(), IRBuffer.size()));
#endif
   result = true;
  } while (0);
  time_compile_end = shared::Win::Time::TimeStamp<std::chrono::milliseconds>();
  route->CompileElapsedTimeMS(::abs(time_compile_end - time_compile_begin));
  return result;
 }
 bool CppEngine::Execute(ICompileRoute* route) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return false;
 }

#if 0
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
  if (found != m_ScriptObjQ.end()) {
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
#endif




 extern CppEngine* __gpCppEngine = nullptr;
}///namespace local