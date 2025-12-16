#pragma once
#include <bitset>
#include <Windows.h>
#include "Core/Core.h"

namespace Mira {

class MIRA_API Keyboard {
	friend class Input;
	friend class Window;

public:
	Keyboard() = delete;
	~Keyboard() = delete;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	Keyboard(Keyboard&&) = delete;
	Keyboard& operator=(Keyboard&&) = delete;

	static void clearState();

	static bool isKeyDown(int key) {
		return m_keys[key];
	}

private:
	static void keyPressed(WPARAM key);
	static void keyReleased(WPARAM key);


private:
	static std::bitset <256> m_keys;
};

}