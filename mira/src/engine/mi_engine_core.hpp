#pragma once

#ifdef BUILD_DLL
#define MI_ENGINE_API __declspec(dllexport)
#else
#define MI_ENGINE_API __declspec(dllimport)
#endif // BUILD_DLL
