#include "stdafx.h"

__shared_api_ void* __stdcall api_object_init(const void*, unsigned long) {
 do {
  if (local::__gpCppEngine)
   break;
  local::__gpCppEngine = new local::CppEngine();
 } while (0);
 return dynamic_cast<cppengine::ICppEngine*>(local::__gpCppEngine);
}
__shared_api_ void __stdcall api_object_uninit(void) {
 if (local::__gpCppEngine) {
  local::__gpCppEngine->Release();
 }
 local::__gpCppEngine = nullptr;
}
#if 0
__shared_api_ int __stdcall api_object_init(const std::intptr_t&)
{
 llvm::install_fatal_error_handler([](void* UserData, const char* Message,
  bool GenCrashDiag) {
   llvm::sys::RunInterruptHandlers();
 llvm::sys::Process::Exit(GenCrashDiag ? 70 : 1);
  }, nullptr);
 return 0;
}

__shared_api_ int __stdcall api_object_uninit(const std::intptr_t&)
{
 if (local::__gpEngineManager) {
  delete local::__gpEngineManager;
  local::__gpEngineManager = nullptr;
 }
 llvm::llvm_shutdown_obj();
 return 0;
}

__shared_api_ std::intptr_t __stdcall api_object_setup_script_engine(const std::intptr_t& spi, const int& argc, const char** argv)
{
 if (spi <= 0)
  return 0;
#if 0
 if (!script_engine_api::__gpEngine) {
  script_engine_api::__gpEngine = new script_engine_api::Engine(
   dynamic_cast<script_engine_api::IScriptEngineSpi*>(reinterpret_cast<script_engine_api::IScriptEngineSpi*>(spi)),
   argc, argv);
  if (!script_engine_api::__gpEngine)
   return false;
 }
 return reinterpret_cast<std::intptr_t>(script_engine_api::__gpEngine);
#endif
 return 0;
}

__shared_api_ std::intptr_t __stdcall api_object_create_script_engine(const std::intptr_t& spi, const int& argc, const char** argv) {
 if (!spi)
  return 0;
 if (!local::__gpEngineManager)
  local::__gpEngineManager = new local::EngineManager();
 return reinterpret_cast<std::intptr_t>(local::__gpEngineManager->Create(spi, argc, argv));
}

__shared_api_ bool __stdcall api_object_destroy_script_engine(const std::intptr_t& spi) {
 if (!spi || !local::__gpEngineManager)
  return false;
 return local::__gpEngineManager->Destroy(spi);
}
#endif