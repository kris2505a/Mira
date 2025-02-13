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