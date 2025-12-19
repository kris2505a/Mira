#pragma once
#include "Signal.h"

namespace Mira {

class WindowResizeSignal : public Signal {
public:
	WindowResizeSignal() = default;
	~WindowResizeSignal() = default;
	SignalType type() const {
		return SignalType::WindowResize;
	}
	std::string name() const {
		return "WindowResize";
	}
};

class WindowCloseSignal : public Signal {
public:
	WindowCloseSignal() = default;
	~WindowCloseSignal() = default;
	SignalType type() const {
		return SignalType::WindowClose;
	}
	std::string name() const {
		return "WindowClose";
	}
};

}