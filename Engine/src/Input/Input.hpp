#pragma once
#include "KeyCodes.hpp"

class Input {
public:
	static bool isKeyDown(Key key);
	static bool isKeyUp(Key key);

	static bool isButtonDown(Button button);
	static bool isButtonUp(Button button);
};