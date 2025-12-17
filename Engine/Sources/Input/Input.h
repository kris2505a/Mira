#pragma once
#include "KeyCodes.h"

namespace Mira {

class Input {
public:
	static bool keyDown(Key key);
	static bool keyUp(Key key);
	static bool buttonDown(Button button);
	static bool buttonUp(Button button);
	static int getMouseX();
	static int getMouseY(); 
};

}