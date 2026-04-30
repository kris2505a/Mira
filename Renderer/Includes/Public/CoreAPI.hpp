#pragma once

#ifdef PLATFORM_WINDOWS
    #ifdef MIRE_RENDERER_BUILD 
	    #define RENDER_API __declspec(dllexport)
    #else
	    #define RENDER_API __declspec(dllimport)
    #endif // MIRE_RENDERER_BUILD 

#else
	#define RENDER_API 
#endif // PLATFORM_WINDOWS
