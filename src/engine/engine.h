#if !defined(__C8605A33_C1DA_4CC8_AC2C_E0DA72B93DDB__)
#define __C8605A33_C1DA_4CC8_AC2C_E0DA72B93DDB__

namespace local {

 class CppEngine final : public ICppEngine {
 public:
  CppEngine();
  virtual ~CppEngine();
 private:
  void Init();
  void UnInit();
 public:
  void Release() const override final;
 protected:
  IScript* CreateScriptObj() override final;
  ICompileRoute* CreateCompileRoute() override final;
  IEngineConfig* EngineConfigGet() const override final;;
  bool Start() override final;
  void Stop() override final;
  bool Ready() const override final;
  bool CompileCC(ICompileRoute*) override final;
  bool CompileBC(ICompileRoute*) override final;
  bool Execute(ICompileRoute*) override final;
 protected:
  std::atomic_bool m_IsOpen = false;
  EngineConfig* m_pEngineConfig = nullptr;
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 };

#if 0
 class Engine : public IScriptEngineApi
 {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Engine(IScriptEngineSpi*, const int&, const char**);
  virtual ~Engine();
 public:
  bool Start() override final;
  void Stop()  override final;
  bool Ready() const override final;
  void Release() override final;
  IScriptObj* CompileCC(const IScriptObj*) override final;
  IScriptObj* CompileBC(const IScriptObj*) override final;
  IScriptObj* CreateScriptObj(const std::string&) override final;
  IScriptObj* AssignScriptObj(const IScriptObj*) override final;
  IScriptObj* AssignScriptObj(const std::string&) override final;
  IScriptObj* SearchScriptObj(const IScriptObj*) override final;
 private:
  std::atomic_bool m_Ready = false;
  std::vector<std::string> m_Argvs;
  std::vector<ScriptObj*> m_ScriptObjCacheQ;
  std::map<std::string, ScriptObj*> m_ScriptObjQ;
 };
#endif



 extern CppEngine* __gpCppEngine;
}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 13 Jan 2023 14:46:39 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__C8605A33_C1DA_4CC8_AC2C_E0DA72B93DDB__
