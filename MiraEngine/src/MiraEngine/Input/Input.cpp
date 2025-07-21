#include <MiraPreCompHeader.h>
#include "Input.h"

namespace Mira {

bool Input::isKeyPressed(int _key) {
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	return state[_key];
}

bool Input::isButtonPressed(int _button) {
	uint32_t buttons = SDL_GetMouseState(nullptr, nullptr);
	return buttons & SDL_BUTTON(_button);
}

Vec2Df Input::getMousePos() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return Vec2Df(x, y);
}

} // namespace Mira
