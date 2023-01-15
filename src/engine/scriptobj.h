#if !defined(AFX_SK_H__9055B6BE_A01B_4438_A188_3B443C229997__HEAD__)
#define AFX_SK_H__9055B6BE_A01B_4438_A188_3B443C229997__HEAD__

namespace local {

#if 0
	class ScriptObj final : public IScriptObj
	{
		std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
		friend class Engine;
	public:
		ScriptObj(const std::string&);
		ScriptObj(const IScriptObj*);
		ScriptObj(const ScriptObj&);
		virtual ~ScriptObj();
	protected:
		void Assign(const IScriptObj*) override final;
		void Release() const override final;
		void BufferBC(const std::string&) override final;
		const std::string& BufferBC() const override final;
		void BufferCC(const std::string&) override final;
		const std::string& BufferCC() const override final;
		void EntryFun(const std::string&) override final;
		const std::string& EntryFun() const override final;
		void EntryPtr(const uintptr_t&) override final;
		const std::uintptr_t& EntryPtr() const override final;
		const std::uint64_t& ID() const override final;
		void ID(const std::uint64_t&) override final;
		std::string Packet() const override final;
		bool Packet(const std::string&) override final;
		std::string Identify() const override final;
		const std::uint64_t& TimeCompileBC() const override final;
		const std::uint64_t& TimeCompileCC() const override final;
		void TimeCompileCC(const std::uint64_t&) override final;
		void TimeCompileBC(const std::uint64_t&) override final;
		void TargetSystem(const EnTargetSystem&) override final;
		const EnTargetSystem& TargetSystem() const override final;
		void Signature(const std::string&) override final;
		void ServiceIdentify(const std::string&) override final;
		const std::string& Signature() const override final;
		const std::string& ServiceIdentify() const override final;
		bool VerifyCC() const override final;
		bool VerifyBC() const override final;
		bool EnableFlag() const override final;
		void EnableFlag(const bool&) override final;
		bool StartFlag() const override final;
		void StartFlag(const bool&) override final;
		const std::string& CachePathname() const override final;
		void CachePathname(const std::string&) override final;
		const std::string& CCCachePathname() const override final;
		void CCCachePathname(const std::string&) override final;
		bool Finish() const override final;
		void BindAppend(const std::string&) override final;
		void BindRemove(const std::string&) override final;
		std::set<std::string> BindGet() const override final;
		bool BindCheck(const std::string&) const override final;
		bool BindEmpty() const override final;
		size_t BindSize() const override final;
	private:
		void TimeCompileBCUpdate();
		void TimeCompileCCUpdate();
		bool Compile();
		void Reset();
		void operator=(const ScriptObj&);
		void operator=(const IScriptObj*);
		void operator=(const std::string&);
	private:
		std::set<std::string> m_BindQ;
		std::string m_Signature;
		std::string m_ServiceIdentify;
		std::string m_EntryFun;
		std::string m_BufferBC;
		std::string m_BufferCC;
		std::uintptr_t m_EntryPtr = 0;
		std::uint64_t m_TimeCompileBC = 0;
		std::uint64_t m_TimeCompileCC = 0;
		std::uint64_t m_ID = 0;
		std::atomic_bool m_EnableFlag = false;
		std::atomic_bool m_StartFlag = false;
		std::string m_CachePathname;
		std::string m_CCCachePathname;
		EnTargetSystem m_TargetSystem = EnTargetSystem::SYSTEM_WINDOWS;
		llvm::LLVMContext m_Context;
		llvm::SMDiagnostic m_ParseIRErr;
		std::shared_ptr<llvm::ExecutionEngine> m_pEE = nullptr;
	};
#endif
}///namespace local

/*!@ 新生联创®（上海）*/
/*!@ Fri Apr 23 09:33:30 UTC+0800 2021*/
/*!@ ___www.skstu.com___*/
#endif /*AFX_SK_H__9055B6BE_A01B_4438_A188_3B443C229997__HEAD__*/