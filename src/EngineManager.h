#if !defined(AFX_SK_H__68417CD0_2298_4E36_84B6_68B55ECD4AC4__HEAD__)
#define AFX_SK_H__68417CD0_2298_4E36_84B6_68B55ECD4AC4__HEAD__

namespace script_engine {

	class EngineManager final {
		std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
	public:
		EngineManager();
		~EngineManager();
	public:
		Engine* Create(const std::uintptr_t&, const int&, const char**);
		bool Destroy(const std::uintptr_t& EngineID);
	private:
		std::map<std::uintptr_t, Engine*> m_EngineQ;
	};
	extern EngineManager* __gpEngineManager;

}///namespace script_engine

/*!@ 新生联创®（上海）*/
/*!@ Fri Apr 23 09:32:12 UTC+0800 2021*/
/*!@ ___www.skstu.com___*/
#endif /*AFX_SK_H__68417CD0_2298_4E36_84B6_68B55ECD4AC4__HEAD__*/