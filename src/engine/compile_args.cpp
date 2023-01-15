#include "stdafx.h"

namespace local {

 CompileArgs::CompileArgs() {

 }

 CompileArgs::~CompileArgs() {

 }
 void CompileArgs::Release() const {
  delete this;
 }
 void CompileArgs::operator<<(const TypeCompileArgs& args) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Args = args;
 }
 void CompileArgs::Push(const std::string& value, const std::string& key) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  if (key.empty() && value.empty())
   return;
  m_Args.emplace(key, value);
 }

 size_t CompileArgs::Argc() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Args.size();
 }
#if ENABLE_LLVM
 llvm::SmallVector<const char*, 256> CompileArgs::Args() const {
  llvm::SmallVector<const char*, 256> result;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  for (const auto& arg : m_Args) {
   if (!arg.first.empty())
    result.emplace_back(arg.first.c_str());
   if (!arg.second.empty())
    result.emplace_back(arg.second.c_str());
  }
  return result;
 }
#endif
}///namespace local

