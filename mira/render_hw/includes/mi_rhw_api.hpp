#pragma once  
#if defined(BUILD_DLL)
    #define MI_RHW_API __attribute__((visibility("default")))
#else
    #define MI_RHW_API
#endif


#define MI_RHW namespace mira::eng {

#define MI_RHW_END }