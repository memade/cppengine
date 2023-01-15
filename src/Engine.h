#if !defined(AFX_SK_H__2534A104_032F_4502_8407_5A971E1E2037__HEAD__)
#define AFX_SK_H__2534A104_032F_4502_8407_5A971E1E2037__HEAD__

namespace script_engine {

	class Engine : public IScriptEngineApi
	{
		std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
	public:
		Engine(IScriptEngineSpi*,const int&,const char**);
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

}///namespace script_engine


//!@ /*新生联创®（上海）*/
//!@ /*Mon Mar 15 10:18:17 UTC+0800 2021*/
//!@ /*___www.skstu.com___*/
#endif /*AFX_SK_H__2534A104_032F_4502_8407_5A971E1E2037__HEAD__*/