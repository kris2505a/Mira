#pragma once

#ifdef BUILD_DLL
#define MI_RENDER_API __declspec(dllexport)
#else
#define MI_RENDER_API __declspec(dllimport)
#endif