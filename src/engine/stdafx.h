#if !defined(AFX_SK_H__1DB42C86_C6B6_46E7_8CB4_A5F29E9E3BBB__HEAD__)
#define AFX_SK_H__1DB42C86_C6B6_46E7_8CB4_A5F29E9E3BBB__HEAD__

#define ENABLE_LLVM 1

#define WINLIB_DISABLE_IMAGEHLP
#include <win.h>
#include <rapidjson.h>
#include <rapidxml.h>

#include "cppengine.h"
using namespace cppengine;
#include "define.h"
#if ENABLE_LLVM 
#include "dependon.h"
#endif
#include "config.h"
#include "compile_args.h"
#include "compile_route.h"
#include "global.h"
#include "scriptobj.h"
#include "engine.h"
#include "manager.h"
#include "exports.h"

//!@ /*新生联创®（上海）*/
//!@ /*Mon Mar 15 09:01:55 UTC+0800 2021*/
//!@ /*___www.skstu.com___*/
#endif /*AFX_SK_H__1DB42C86_C6B6_46E7_8CB4_A5F29E9E3BBB__HEAD__*/
