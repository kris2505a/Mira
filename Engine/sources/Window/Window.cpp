#include <MiraPreCompHeader.h>
#include "Window.h"
#include "D3D/Win32Window.h"

namespace Mira {

WindowBase::WindowBase() {
	m_properties = { 1600u, 900u, "MiraEngine", false, false, true };
}

WindowBase::~WindowBase() {

}


std::unique_ptr <WindowBase> WindowBase::createWindow() {
#ifdef PLATFORM_WINDOWS
	return std::make_unique <Win32Window>();
#elifdef PLATFORM_LINUX
	return std::make_unique <Win32Window>();
#endif

}

}