#if !defined(AFX_SK_H__8D0B773F_F8A1_4CE2_9F36_BD8093666144__HEAD__)
#define AFX_SK_H__8D0B773F_F8A1_4CE2_9F36_BD8093666144__HEAD__

#include <dllinterface.h>

namespace cppengine {
 using TypeCompileArgs = std::unordered_multimap<std::string, std::string>;
 using Type_internal_isystem_s = std::unordered_set<std::string>;

 enum class EnOSType : unsigned long long {
  OS_UNKNOWN = 0,
  OS_MICROSOFT_WINDOWS = 1,
  OS_LINUX = 2,
  OS_IOS = 3,
  OS_ANDROID = 4,
 };

 enum class EnDataType : unsigned long long {
  TYPE_INT = 0,
  TYPE_STRING = 1,
  TYPE_UINT = 2,
  TYPE_LONG = 3,
  TYPE_ULONG = 4,
  TYPE_ULONGLONG = 5,
  TYPE_LONGLONG = 6,
  TYPE_SHORT = 7,
  TYPE_USHORT = 8,
 };
 class IEngineConfig {
 public:
  virtual void Release() const = 0;
  virtual const EnOSType& OSType() const = 0;
  virtual void OSType(const EnOSType&) = 0;
  virtual void Default_internal_isystem_s_set(const Type_internal_isystem_s&) = 0;
  virtual Type_internal_isystem_s Default_internal_isystem_s_get() const = 0;
  virtual void Default_internal_isystem_s_add(const std::string&) = 0;
 };

 class ICompileArgs {
 public:
  virtual void operator<<(const TypeCompileArgs&) = 0;
  virtual void Push(const std::string& value, const std::string& key) = 0;
  virtual void Release() const = 0;
 };

 class IMethodModule {
 public:
  virtual void Identify(const std::string&) = 0;
  virtual const std::string& Identify() const = 0;

 };

 typedef class ICompileRoute {
 public:
  virtual void EnableSourceEncrypt(const bool&) = 0;
  virtual void EnableDefault_internal_isystem(const bool&) = 0;
  virtual const bool& EnableDefault_internal_isystem() const = 0;
  virtual const bool& EnableSourceEncrypt() const = 0;
  virtual void Source(const std::string&) = 0;
  virtual const std::string& Source() const = 0;
  virtual const std::string& BufferCC() const = 0;
  virtual void BufferCC(const std::string&) = 0;
  virtual const std::string& BufferBC() const = 0;
  virtual void BufferBC(const std::string&) = 0;
  virtual ICompileArgs* CompileArgsGet() const = 0;
  virtual const time_t& CompileElapsedTimeMS() const = 0;
  virtual void CompileElapsedTimeMS(const time_t&) = 0;
  //!@ serialization
  virtual void operator>>(std::string&) const = 0;
  //!@ deserialization
  virtual bool operator<<(const std::string&) = 0;
  virtual void Release() const = 0;
 }IScript;

 class ICppEngine : public shared::InterfaceDll<ICppEngine> {
 public:
  virtual IScript* CreateScriptObj() = 0;
  virtual ICompileRoute* CreateCompileRoute() = 0;
  virtual IEngineConfig* EngineConfigGet() const = 0;
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual bool Ready() const = 0;
  virtual void Release() const = 0;
  virtual bool CompileCC(ICompileRoute*) = 0;
  virtual bool CompileBC(ICompileRoute*) = 0;
  virtual bool Execute(ICompileRoute*) = 0;
 };




#if 0
 class IScriptObj {
 public:
  virtual void Release() const = 0;
  virtual void Assign(const IScriptObj*) = 0;
  virtual std::string Packet() const = 0;
  virtual bool Packet(const std::string&) = 0;
  virtual void BufferBC(const std::string&) = 0;
  virtual const std::string& BufferBC() const = 0;
  virtual void BufferCC(const std::string&) = 0;
  virtual const std::string& BufferCC() const = 0;
  virtual void EntryFun(const std::string&) = 0;
  virtual const std::string& EntryFun() const = 0;
  virtual void EntryPtr(const uintptr_t&) = 0;
  virtual const std::uintptr_t& EntryPtr() const = 0;
  virtual const unsigned long long& ID() const = 0;
  virtual void ID(const unsigned long long&) = 0;
  virtual std::string Identify() const = 0;
  virtual const unsigned long long& TimeCompileBC() const = 0;
  virtual const unsigned long long& TimeCompileCC() const = 0;
  virtual void TimeCompileCC(const unsigned long long&) = 0;
  virtual void TimeCompileBC(const unsigned long long&) = 0;
  virtual void TargetSystem(const EnTargetSystem&) = 0;
  virtual const EnTargetSystem& TargetSystem() const = 0;
  virtual void Signature(const std::string&) = 0;
  virtual void ServiceIdentify(const std::string&) = 0;
  virtual const std::string& Signature() const = 0;
  virtual const std::string& ServiceIdentify() const = 0;
  virtual bool VerifyCC() const = 0;
  virtual bool VerifyBC() const = 0;
  virtual bool EnableFlag() const = 0;
  virtual void EnableFlag(const bool&) = 0;
  virtual bool StartFlag() const = 0;
  virtual void StartFlag(const bool&) = 0;
  virtual const std::string& CachePathname() const = 0;
  virtual void CachePathname(const std::string&) = 0;
  virtual const std::string& CCCachePathname() const = 0;
  virtual void CCCachePathname(const std::string&) = 0;
  virtual bool Finish() const = 0;
  virtual void BindAppend(const std::string&) = 0;
  virtual void BindRemove(const std::string&) = 0;
  virtual std::set<std::string> BindGet() const = 0;
  virtual bool BindCheck(const std::string&) const = 0;
  virtual bool BindEmpty() const = 0;
  virtual size_t BindSize() const = 0;
 };

 class IScriptEngineSpi;
 class IScriptEngineApi
 {
 protected:
  IScriptEngineApi(IScriptEngineSpi* pEngineSpi) : m_pEngineSpi(pEngineSpi) { }
  virtual ~IScriptEngineApi() {}
 public:
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual void Release() = 0;
  virtual bool Ready() const = 0;
  virtual IScriptObj* CompileCC(const IScriptObj*) = 0;
  virtual IScriptObj* CompileBC(const IScriptObj*) = 0;
  virtual IScriptObj* CreateScriptObj(const std::string&) = 0;
  virtual IScriptObj* AssignScriptObj(const IScriptObj*) = 0;
  virtual IScriptObj* AssignScriptObj(const std::string&) = 0;
  virtual IScriptObj* SearchScriptObj(const IScriptObj*) = 0;
 protected:
  IScriptEngineSpi* m_pEngineSpi = nullptr;
 };

 class IScriptEngineSpi {
  using tf_api_object_init = int(__stdcall*)(const std::intptr_t&);
  using tf_api_object_uninit = int(__stdcall*)(const std::intptr_t&);
  using tf_api_object_setup_script_engine = std::intptr_t(__stdcall*)(const std::intptr_t&, const int&, const char**);
  using tf_api_object_create_script_engine = std::intptr_t(__stdcall*)(const std::intptr_t&, const int&, const char**);
  using tf_api_object_destroy_script_engine = bool(__stdcall*)(const std::intptr_t&);
 public:
  IScriptEngineSpi(const std::string& dllPathname) {
   do {
    if (dllPathname.empty())
     break;
    m_hModule = ::LoadLibraryA(dllPathname.c_str());
    if (!m_hModule)
     break;
    m_api_object_init = reinterpret_cast<decltype(m_api_object_init)>(::GetProcAddress(m_hModule, "api_object_init"));
    m_api_object_uninit = reinterpret_cast<decltype(m_api_object_uninit)>(::GetProcAddress(m_hModule, "api_object_uninit"));
    m_api_object_setup_script_engine = reinterpret_cast<decltype(m_api_object_setup_script_engine)>(::GetProcAddress(m_hModule, "api_object_setup_script_engine"));
    m_api_object_create_script_engine = reinterpret_cast<decltype(m_api_object_create_script_engine)>(::GetProcAddress(m_hModule, "api_object_create_script_engine"));
    m_api_object_destroy_script_engine = reinterpret_cast<decltype(m_api_object_destroy_script_engine)>(::GetProcAddress(m_hModule, "api_object_destroy_script_engine"));
    if (!m_api_object_init || !m_api_object_uninit || !m_api_object_setup_script_engine || !m_api_object_create_script_engine || !m_api_object_destroy_script_engine)
     break;
    if (m_api_object_init(0))
     break;

   } while (0);
  }
  virtual ~IScriptEngineSpi()
  {
   if (m_pScriptEngineApi)
   {
    m_pScriptEngineApi->Release();
    m_pScriptEngineApi = nullptr;
   }
   if (m_api_object_uninit)
    m_api_object_uninit(0);
  }
 public:
  virtual std::intptr_t OnEngineSetup() { return 0; }
  virtual bool Start()
  {
   m_pScriptEngineApi = reinterpret_cast<IScriptEngineApi*>(OnEngineSetup());
   if (!m_pScriptEngineApi)
    return false;
   if (!m_pScriptEngineApi->Start())
    false;
   return m_pScriptEngineApi->Ready();
  }
  virtual void Stop()
  {
   if (!m_pScriptEngineApi)
    return;
   m_pScriptEngineApi->Stop();
  }
  virtual bool Ready() const {
   if (!m_pScriptEngineApi)
    return false;
   return m_pScriptEngineApi->Ready();
  }
  virtual IScriptObj* CreateScriptObj(const std::string& from) const {
   if (!m_pScriptEngineApi)
    return nullptr;
   if (!m_pScriptEngineApi->Ready())
    return nullptr;
   return m_pScriptEngineApi->CreateScriptObj(from);
  }
  virtual IScriptObj* AssignScriptObj(const std::string& from) const {
   if (!m_pScriptEngineApi)
    return nullptr;
   if (!m_pScriptEngineApi->Ready())
    return nullptr;
   return m_pScriptEngineApi->AssignScriptObj(from);
  }
  virtual IScriptObj* SearchScriptObj(const IScriptObj* search) {
   if (!m_pScriptEngineApi)
    return nullptr;
   if (!m_pScriptEngineApi->Ready())
    return nullptr;
   return m_pScriptEngineApi->SearchScriptObj(search);
  }
  virtual IScriptObj* AssignScriptObj(const IScriptObj* from) const {
   if (!m_pScriptEngineApi)
    return nullptr;
   if (!m_pScriptEngineApi->Ready())
    return nullptr;
   return m_pScriptEngineApi->AssignScriptObj(from);
  }
  virtual IScriptObj* CompileCC(const IScriptObj* pScriptObj) const {
   if (!m_pScriptEngineApi || !pScriptObj)
    return nullptr;
   if (!m_pScriptEngineApi->Ready())
    return nullptr;
   return m_pScriptEngineApi->CompileCC(pScriptObj);
  }
  virtual IScriptObj* CompileBC(const IScriptObj* pScriptObj) const {
   if (!m_pScriptEngineApi || !pScriptObj)
    return nullptr;
   if (!m_pScriptEngineApi->Ready())
    return nullptr;
   return m_pScriptEngineApi->CompileBC(pScriptObj);
  }
 protected:
  HMODULE m_hModule = nullptr;
  tf_api_object_init m_api_object_init = nullptr;
  tf_api_object_uninit m_api_object_uninit = nullptr;
  tf_api_object_setup_script_engine m_api_object_setup_script_engine = nullptr;
  tf_api_object_create_script_engine m_api_object_create_script_engine = nullptr;
  tf_api_object_destroy_script_engine m_api_object_destroy_script_engine = nullptr;
  IScriptEngineApi* m_pScriptEngineApi = nullptr;
 };

#if 0//compile action ----------   <arg key = "-triple" value = "x86_64-pc-windows-msvc19.28.29912" / >

 class CompileArgs final
 {
 public:
  std::unordered_multimap<std::string, std::string> m_Args;
 public:
  int Argc() const { return static_cast<int>(m_Args.size()); }
  std::vector<const char*> Args() const {
   std::vector<const char*> result;
   for (const auto& arg : m_Args) {
    if (!arg.first.empty())
     result.emplace_back(arg.first.c_str());
    if (!arg.second.empty())
     result.emplace_back(arg.second.c_str());
   }
   return result;
  }
 };

 < Compile >
  <Args>
  <arg key = "" value = "cc1" / >
  <arg key = "" value = "-O3" / >
  <arg key = "-target-cpu" value = "x86-64" / >
  <arg key = "-triple" value = "x86_64-pc-windows-msvc" / >
  <arg key = "" value = "-emit-llvm-bc" / >
  <arg key = "" value = "-std=c++14" / >
  <arg key = "-x" value = "c++" / >
  <arg key = "" value = "-fms-extensions" / >
  <arg key = "-internal-isystem" value = "D:\XSSDK\Microsoft Visual Studio\2019\14.28.29910\include" / >
  <arg key = "-internal-isystem" value = "D:\XSSDK\Windows Kits\10\Include\10.0.18362.0\ucrt" / >
  <arg key = "-internal-isystem" value = "D:\XSSDK\Windows Kits\10\Include\10.0.18362.0\shared" / >
  <arg key = "-internal-isystem" value = "D:\XSSDK\Windows Kits\10\Include\10.0.18362.0\um" / >
  <arg key = "-internal-isystem" value = "D:\XSSDK\Windows Kits\10\Include\10.0.18362.0\winrt" / >
  <arg key = "-internal-isystem" value = "E:\www.skstu.com\Project.Interface" / >
  < / Args>
  < / Compile>
#endif
#endif

}///namespace cppengine



//!@ /*新生联创®（上海）*/
//!@ /*Thu Mar 18 16:18:54 UTC+0800 2021*/
//!@ /*___www.skstu.com___*/
#endif /*AFX_SK_H__8D0B773F_F8A1_4CE2_9F36_BD8093666144__HEAD__*/