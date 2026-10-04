#if defined(BUILD_DLL)
    #define MI_ENGINE_API __attribute__((visibility("default")))
#else
    #define MI_ENGINE_API
#endif


#define MI_ENGINE namespace mira::eng {

#define MI_ENGINE_END }