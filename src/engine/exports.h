#if !defined(AFX_SK_H__88BBB088_F32B_41A9_936D_BE6DC01FAD81__HEAD__)
#define AFX_SK_H__88BBB088_F32B_41A9_936D_BE6DC01FAD81__HEAD__

#if defined(SHARED_API)
#define __shared_api_ extern "C" __declspec(dllexport)
#else
#define __shared_api_ extern "C" __declspec(dllimport)
#endif

__shared_api_ void* __stdcall api_object_init(const void*,unsigned long);
__shared_api_ void __stdcall api_object_uninit(void);

#if 0
__shared_api_ int __stdcall api_object_init(const std::intptr_t&);
__shared_api_ int __stdcall api_object_uninit(const std::intptr_t&);
__shared_api_ std::intptr_t __stdcall api_object_setup_script_engine(const std::intptr_t&,const int& argc,const char** argv);
__shared_api_ std::intptr_t __stdcall api_object_create_script_engine(const std::intptr_t&, const int& argc, const char** argv);
__shared_api_ bool __stdcall api_object_destroy_script_engine(const std::intptr_t&);
#endif

//!@ /*新生联创®（上海）*/
//!@ /*Mon Mar 15 09:08:26 UTC+0800 2021*/
//!@ /*___www.skstu.com___*/
#endif /*AFX_SK_H__88BBB088_F32B_41A9_936D_BE6DC01FAD81__HEAD__*/