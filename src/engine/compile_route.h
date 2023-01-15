#if !defined(__51DC028B_D824_468A_A8AE_D152E7DC0C26__)
#define __51DC028B_D824_468A_A8AE_D152E7DC0C26__

namespace local {

 typedef class CompileRoute final : public ICompileRoute {
 public:
  CompileRoute();
  virtual ~CompileRoute();
 private:
  void Init();
  void UnInit();
 protected:
  void EnableDefault_internal_isystem(const bool&) override final;
  const bool& EnableDefault_internal_isystem() const override final;
  void Source(const std::string&) override final;
  const std::string& BufferCC() const override final;
  const std::string& BufferBC() const override final;
  void EnableSourceEncrypt(const bool&) override final;
  ICompileArgs* CompileArgsGet() const override final;
  const time_t& CompileElapsedTimeMS() const override final;
   void operator>>(std::string&) const override final;
   bool operator<<(const std::string&) override final;
  void Release() const override final;
 public:
  void BufferCC(const std::string&) override final;
  void BufferBC(const std::string&) override final;
  const std::string& Source() const override final;
  const bool& EnableSourceEncrypt() const override final;
  void CompileElapsedTimeMS(const time_t&) override final;
 protected:
  bool m_EnableSourceEncrypt = false;
  bool m_EnableDefault_internal_isystem = false;
  std::string m_BufferCC;
  std::string m_BufferBC;
  std::string m_Source;
  time_t m_CompileElapsedTimeMS = 0;
  CompileArgs* m_pCompileArgs = nullptr;
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 }CppScript;

}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 13 Jan 2023 14:36:15 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__51DC028B_D824_468A_A8AE_D152E7DC0C26__

