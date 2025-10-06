#pragma once
#include "Event.h"
#include <Base/MiraAPI.h>

namespace Mira {

class MIRA_API WindowCloseEvent : public Event {
public:
	WindowCloseEvent() {}
	std::string name() const override {
		return "WindowClosed";
	}

	static std::string staticName() {
		return "WindowClosed";
	}

	std::string print() override {
		return name();
	}
};

class MIRA_API WindowLostFocusEvent : public Event {
public:
	WindowLostFocusEvent() {}
	std::string name() const override {
		return "WindowLostFocus";
	}

	static std::string staticName() {
		return "WindowLostFocus";
	}

	std::string print() override {
		return name();
	}
};

}