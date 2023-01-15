#include "stdafx.h"

namespace local {
 EngineConfig::EngineConfig() {
  Init();
 }
 EngineConfig::~EngineConfig() {
  UnInit();
 }
 void EngineConfig::Release() const {
  delete this;
 }
 void EngineConfig::Init() {
#ifdef _WINDOWS
  m_OSType = EnOSType::OS_MICROSOFT_WINDOWS;
#endif

  m_Default_internal_isystem_s = Type_internal_isystem_s
  {
  R"(C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Tools\MSVC\14.34.31933\include)",
  R"(C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\um)",
  R"(C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt)",
  R"(C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\winrt)",
  R"(C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\shared)",
  };
 }
 void EngineConfig::UnInit() {

 }
 const EnOSType& EngineConfig::OSType() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_OSType;
 }
 void EngineConfig::OSType(const EnOSType& os) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_OSType = os;
 }
 Type_internal_isystem_s EngineConfig::Default_internal_isystem_s_get() const {
  Type_internal_isystem_s result;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  result = m_Default_internal_isystem_s;
  return result;
 }
 void EngineConfig::Default_internal_isystem_s_set(const Type_internal_isystem_s& value_s) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  for (const auto& value : value_s) {
   auto append = shared::IConv::ToLowerA(value);
   do {
    if (append.empty())
     break;
    if (m_Default_internal_isystem_s.find(append) != m_Default_internal_isystem_s.end())
     break;
    m_Default_internal_isystem_s.emplace(append);
   } while (0);
  }
 }
 void EngineConfig::Default_internal_isystem_s_add(const std::string& value) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  auto append = shared::IConv::ToLowerA(value);
  do {
   if (append.empty())
    break;
   if (m_Default_internal_isystem_s.find(append) != m_Default_internal_isystem_s.end())
    break;
   m_Default_internal_isystem_s.emplace(append);
  } while (0);
 }
}///namespace local