#pragma once
#include <string>
#include "Input/KeyCodes.h"

namespace Mira {

enum SignalType {
	NONE = 0,
	KeyDown,
	KeyUp,
	ButtonDown,
	ButtonUp,
	MouseMove,
	MouseScroll,
	WindowResize,
	WindowClose
};

class Signal {
public:
	template <typename T>
	static bool match(const Signal& signal) {
		return dynamic_cast<const T*> (&signal) != nullptr;
	}

public:
	Signal() = default;
	virtual ~Signal() = default;
	virtual SignalType type() const   = 0;
	virtual std::string name() const  = 0;
};

}