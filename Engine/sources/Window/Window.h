#pragma once
#include <memory>
#include <string>
#include <Base/MiraAPI.h>


namespace Mira {

struct WindowProperties {
	unsigned int width;
	unsigned int height;
	std::string title;
	bool fullScreen;
	bool vSync;
	bool open;
};

class MIRA_API WindowBase {
public:
	WindowBase();
	virtual ~WindowBase();
	static std::unique_ptr <WindowBase> createWindow();
	virtual void wipeOff(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
	virtual void handleMessages() = 0;

private:
	virtual void init() = 0;
	virtual void shutdown() = 0;

protected:
	WindowProperties m_properties;

};

}