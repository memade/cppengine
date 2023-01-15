#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Psapi.h>
#include <version>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH: {

	}break;
	case DLL_THREAD_ATTACH: {

	}break;
	case DLL_THREAD_DETACH: {

	}break;
	case DLL_PROCESS_DETACH: {

	}break;
	}
	return TRUE;
}
