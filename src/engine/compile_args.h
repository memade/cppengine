#if !defined(__7ADBD283_6F21_485D_92AB_7DF96FC26919__)
#define __7ADBD283_6F21_485D_92AB_7DF96FC26919__

namespace local {

 class CompileArgs final : public ICompileArgs {
 public:
  CompileArgs();
  virtual ~CompileArgs();
 public:
#if ENABLE_LLVM
  llvm::SmallVector<const char*, 256> Args() const;
#endif
  size_t Argc() const;
  void Release() const override final;
 protected:
  void operator<<(const TypeCompileArgs&) override final;
  void Push(const std::string& value, const std::string& key) override final;
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
  TypeCompileArgs m_Args;
 };

}

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 14 Jan 2023 08:52:10 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__7ADBD283_6F21_485D_92AB_7DF96FC26919__


