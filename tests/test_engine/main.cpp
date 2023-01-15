#include <win.h>
#include <cppengine.h>
int main(int argc, char** argv) {
#if defined(_DEBUG)
 ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 //::_CrtSetBreakAlloc(3709);
#endif

 auto engine = cppengine::ICppEngine::CreateInterface(R"(D:\__Github__\Windows\projects\cppengine\bin\x64\Debug\engine.dll)");
 auto engine_config = engine->EngineConfigGet();
 auto os_type = engine_config->OSType();
 engine->Start();

 shared::Win::MainProcess(
  [&](const std::string& input, bool& exit) {
   if (input == "q") {
    if (engine) {
     engine->Stop();
     cppengine::ICppEngine::DestoryInterface(engine);
    }
    exit = true;
   }
   else if (input == "test") {
    do {
     if (!engine)
      break;
     auto route = engine->CreateCompileRoute();
     if (!route)
      break;
     route->Source(R"(
#include <stdio.h>
int main(int argc, char** argv) {

return 0;
}
)");
#if 0
     < Args >
      <arg key = "" value = "cc1" / >
      <arg key = "" value = "-O3" / >
      <arg key = "-target-cpu" value = "x86-64" / >
      <arg key = "-triple" value = "x86_64-pc-windows-msvc" / >
      <arg key = "" value = "-emit-llvm-bc" / >
      <arg key = "" value = "-std=c++14" / >
      <arg key = "-x" value = "c++" / >
      <arg key = "" value = "-fms-extensions" / >
      <arg key = "-internal-isystem" value = "D:\XSSDK\Microsoft Visual Studio\2019\14.28.29910\include" / >
      <arg key = "-internal-isystem" value = "D:\XSSDK\Windows Kits\10\Include\10.0.18362.0\ucrt" / >
      <arg key = "-internal-isystem" value = "D:\XSSDK\Windows Kits\10\Include\10.0.18362.0\shared" / >
      <arg key = "-internal-isystem" value = "D:\XSSDK\Windows Kits\10\Include\10.0.18362.0\um" / >
      <arg key = "-internal-isystem" value = "D:\XSSDK\Windows Kits\10\Include\10.0.18362.0\winrt" / >
      <arg key = "-internal-isystem" value = "E:\www.skstu.com\Project.Interface" / >
      < / Args>
#endif
      auto compile_args = route->CompileArgsGet();
     *compile_args << cppengine::TypeCompileArgs{
{"","cc1"},
{"","-O3"},
{"-target-cpu","x86-64"},
{"-triple","x86_64-pc-windows-msvc"},
{"","-emit-llvm-bc"},
{"","-std=c++14"},
{"-x","c++"},
{"-stdlib"," libc++"},
{"","-fms-extensions"},
     };
     engine->CompileCC(route);
     engine->Execute(route);
     route->Release();
     auto sk = 0;
    } while (0);


   }
  });

 return 0;
}
