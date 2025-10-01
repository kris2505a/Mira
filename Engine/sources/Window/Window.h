#pragma once
#include <memory>
#include <string>
#include <Base/MiraAPI.h>
#include <functional>
#include <Events/Event.h>

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
	using EventCallBack = std::function<void(Event&)>;

public:
	WindowBase();
	virtual ~WindowBase();
	static std::unique_ptr <WindowBase> createWindow();
	virtual void handleMessages() = 0;
	void setCallBack(const EventCallBack& callback);
	bool isOpen() const;

private:
	virtual void init() = 0;
	virtual void shutdown() = 0;

protected:
	WindowProperties m_properties;
	EventCallBack m_callback;

};

}