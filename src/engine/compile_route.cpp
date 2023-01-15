#include "stdafx.h"

namespace local {
 CompileRoute::CompileRoute() {
  Init();
 }
 CompileRoute::~CompileRoute() {
  UnInit();
 }
 void CompileRoute::Init() {
  m_EnableDefault_internal_isystem = true;
  m_pCompileArgs = new CompileArgs();
 }
 void CompileRoute::UnInit() {
  m_pCompileArgs->Release();
 }
 void CompileRoute::Release() const {
  delete this;
 }
 const time_t& CompileRoute::CompileElapsedTimeMS() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_CompileElapsedTimeMS;
 }
 void CompileRoute::CompileElapsedTimeMS(const time_t& ms) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_CompileElapsedTimeMS = ms;
 }
 void CompileRoute::Source(const std::string& source) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Source = source;
 }
 const std::string& CompileRoute::BufferCC() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_BufferCC;
 }
 const std::string& CompileRoute::BufferBC() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_BufferBC;
 }
 void CompileRoute::BufferCC(const std::string& cc) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_BufferCC = cc;
 }
 void CompileRoute::BufferBC(const std::string& bc) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_BufferBC = bc;
 }
 const std::string& CompileRoute::Source() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Source;
 }
 void CompileRoute::EnableDefault_internal_isystem(const bool& enable) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_EnableDefault_internal_isystem = enable;
 }
 const bool& CompileRoute::EnableDefault_internal_isystem() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_EnableDefault_internal_isystem;
 }
 void CompileRoute::EnableSourceEncrypt(const bool& enable) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_EnableSourceEncrypt = enable;
 }
 const bool& CompileRoute::EnableSourceEncrypt() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_EnableSourceEncrypt;
 }
 ICompileArgs* CompileRoute::CompileArgsGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_pCompileArgs;
 }
 void CompileRoute::operator>>(std::string& output) const {
  output.clear();
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   




  } while (0);
 }
 bool CompileRoute::operator<<(const std::string& input) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (input.empty())
    break;





   result = true;
  } while (0);
  return result;
 }
}///namespace local

