#pragma once

#ifdef API_ENGINE
	#define MIRA_API __declspec(dllexport)
#else
	#define MIRA_API __declspec(dllimport)
#endif // API_ENGINE

#define MIRA_ASSERT(x, msg)              \
    do {                                 \
        if (!(x)) {                      \
            MIRA_LOG(LOG_ERROR, msg);    \
            std::abort();                \
        }                                \
    } while (0)


#ifdef _MSC_VER
#pragma warning(disable : 4251 4275 4661)
#endif
