#pragma once

#ifdef PLATFORM_WINDOWS
    typedef struct HWND__*  HWND;
#endif

namespace mr {

struct WindowHandle {
#ifdef PLATFORM_WINDOWS
	HWND hwnd;
#endif // PLATFORM_WINDOWS

};

}
