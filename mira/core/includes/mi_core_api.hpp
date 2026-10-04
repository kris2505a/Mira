#if defined(BUILD_DLL)
    #define MI_CORE_API __attribute__((visibility("default")))
#else
    #define MI_CORE_API
#endif

#define MI_CORE namespace mira::core {

#define MI_CORE_END }