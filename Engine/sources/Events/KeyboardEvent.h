#pragma once
#include "Event.h"

namespace Mira {

class KeyboardEvent : public Event {
protected:
	KeyboardEvent(int key) : m_key(key) {}
	int m_key;
};

class KeyPressedEvent : public KeyboardEvent {
public:
	KeyPressedEvent(int key) : KeyboardEvent(key) {}
	std::string name() const override {
		return "KeyPressed";
	}

	static std::string staticName() { 
		return "KeyPressed"; 
	}

	std::string print() override {
		return name() + ": " + std::to_string(m_key);
	}
};

class KeyReleasedEvent : public KeyboardEvent {
public:
	KeyReleasedEvent(int key) : KeyboardEvent(key) {}
	std::string name() const override {
		return "KeyReleased";
	}

	static std::string staticName() {
		return "KeyReleased";
	}

	std::string print() override {
		return name() + ": " + std::to_string(m_key);
	}
};

}