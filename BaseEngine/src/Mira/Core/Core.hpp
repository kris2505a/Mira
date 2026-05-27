#pragma once

#ifdef _WIN32

    #ifdef BUILD_DLL
        #define MIRA_API __declspec(dllexport)
    #else
        #define MIRA_API __declspec(dllimport)
    #endif

#else

    #define MIRA_API __attribute__((visibility("default")))

#endif

#define BIT(x) (1 << x)
