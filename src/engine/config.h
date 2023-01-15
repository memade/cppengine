#if !defined(__4599A211_A277_4722_BB02_A8C5FE56F186__)
#define __4599A211_A277_4722_BB02_A8C5FE56F186__

namespace local {

 class EngineConfig final : public IEngineConfig {
 public:
  EngineConfig();
  void Release() const override final;
 public:
  const EnOSType& OSType() const override final;
  Type_internal_isystem_s Default_internal_isystem_s_get() const override final;
 private:
  void Init();
  void UnInit();
 protected:
  void OSType(const EnOSType&) override final;
  void Default_internal_isystem_s_set(const Type_internal_isystem_s&) override final;
  void Default_internal_isystem_s_add(const std::string&) override final;
  virtual ~EngineConfig();
  EnOSType m_OSType = EnOSType::OS_UNKNOWN;
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
  Type_internal_isystem_s m_Default_internal_isystem_s;
 };

}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 13 Jan 2023 14:28:21 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__4599A211_A277_4722_BB02_A8C5FE56F186__
