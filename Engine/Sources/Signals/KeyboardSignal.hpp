#pragma once
#include "Signal.hpp"

namespace Mira {
class KeyboardSignal : public Signal {
protected:
	KeyboardSignal(Key key) :m_key(key) {}
	~KeyboardSignal() = default;

public:
	SignalType type() const { return SignalType::NONE; }
	std::string name() const { return "None"; }
	Key getKey() const {
		return m_key;
	}

protected:
	Key m_key;

};

class KeyDownSignal : public KeyboardSignal {
public:
	KeyDownSignal(Key key) : KeyboardSignal(key) {}
	~KeyDownSignal() = default;

	SignalType type() const {
		return SignalType::KeyDown;
	}

	std::string name() const {
		return "KeyDown";
	}
};

class KeyUpSignal : public KeyboardSignal {
public:
	KeyUpSignal(Key key) : KeyboardSignal(key) {}
	~KeyUpSignal() = default;

	SignalType type() const {
		return SignalType::KeyUp;
	}

	std::string name() const {
		return "KeyUp";
	}
};
}