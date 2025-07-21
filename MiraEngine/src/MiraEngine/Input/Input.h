#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Math/Vector.h>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>


namespace Mira {
class MIRA_API Input {
public:

	Input() = delete;
	~Input() = delete;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	static bool isKeyPressed(int _key);	
	static bool isButtonPressed(int _button);
	static Vec2Df getMousePos();

};

}