#pragma once 

#ifdef BUILD_DLL
#define MI_CORE_API __declspec(dllexport)
#else
#define MI_CORE_API __declspec(dllimport)

#endif // ENGINE_SHARED
