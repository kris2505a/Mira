#pragma once

#ifdef PLATFORM_WINDOWS
	#ifdef PROJECT_ENGINE
		#define CYANAPI __declspec(dllexport)
	#else
		#define CYANAPI __declspec(dllimport)
	#endif
#else
	#error Unsupported Platform
#endif

#define BIT(X) (1 << X)

#ifdef ENABLE_ASSERTS
	#define ASSERTS(x, ...) {if(!(x)){LOG(CY_ERROR, ("Assertion failed: {0}", __VA_ARGS__)); __debugbreak; }}
	#define CYAN_ASSERTS(x, ...) {if(!(x)){CYAN_LOG(CY_ERROR, ("Assertion failed: {0}", __VA_ARGS__)); __debugbreak; }}
#else
	#define ASSERTS(x, ...)
	#define CYAN_ASSERTS(x, ...)
#endif // ENABLE_ASSERTS
