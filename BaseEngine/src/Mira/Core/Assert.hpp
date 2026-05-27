#pragma once

#include <cstdlib>

#include "Mira/Logger/Logger.hpp"


#if defined(MIRA_DEBUG)

    #if defined(PLATFORM_WINDOWS)

        #define MIRA_DEBUG_BREAK() __debugbreak()

    #else

        #define MIRA_DEBUG_BREAK() __builtin_trap()

    #endif

#else

    #define MIRA_DEBUG_BREAK() std::abort()

#endif


#define MIRA_ASSERT(expr, msg)                 \
    do                                         \
    {                                          \
        if (!(expr))                           \
        {                                      \
            Logger::log(                       \
                LogType::Error,                \
                "Assertion failed!"            \
            );                                 \
                                               \
            Logger::log(                       \
                LogType::Error,                \
                "   Message: {}",              \
                std::string(msg)               \
            );                                 \
                                               \
            Logger::log(                       \
                LogType::Error,                \
                "   Expression: {}",           \
                #expr                          \
            );                                 \
                                               \
            Logger::log(                       \
                LogType::Error,                \
                "   Line, File: {}, {}",       \
                __LINE__,                      \
                __FILE__                       \
            );                                 \
                                               \
            MIRA_DEBUG_BREAK();                \
        }                                      \
    } while (0)