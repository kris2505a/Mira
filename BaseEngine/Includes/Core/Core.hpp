#pragma once

#ifdef MIRA_ENGINE_BUILD
#define MIRA_API __declspec(dllexport)
#else
#define MIRA_API __declspec(dllimport)
#endif // BUILD_DLL
