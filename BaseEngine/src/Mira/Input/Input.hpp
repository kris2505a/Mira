#pragma once
#include <bitset>

#include "Mira/Math/Vec2D.hpp"

#include "InputCodes.hpp"

namespace Mira {

class Input {
friend class Engine;

public:
    static bool isKeyDown(Key key);
    static bool isKeyUp(Key key);
    static bool isKeyHeld(Key key);

    static bool isButtonDown(Button button);
    static bool isButtonUp(Button button);
    static bool isButtonHeld(Button button);



    enum State {
        Down,
        Up
    };

private:
    static Input& get();
    
    static void setKeyState(Key key, State state);

    static void setButtonState(Button button, State state);
    static void mouseMove(Vec2D pos);
    static void mouseScroll(float offset);

    static Vec2D getMousePosition();
    static Vec2D getMouseDelta();
    static float getMouseWheelOffset();

    static void endState();
    static void resetState();


private:
    std::bitset<256> keyState;
    std::bitset<256> previousKeyState;
    std::bitset<5> buttonState;
    std::bitset<5> previousButtonState;

    float xPosition = 0.0f;
    float yPosition = 0.0f;

    Vec2D mousePosition = { 0.0f, 0.0f };

    float dx = 0.0f;
    float dy = 0.0f;
    Vec2D mouseDelta = { 0.0f, 0.0f };

    bool firstMove = true;

    float wheelOffset = 0.0f;

    static Input s_inputState;
};

}
