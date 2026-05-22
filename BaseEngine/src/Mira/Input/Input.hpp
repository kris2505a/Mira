#pragma once
#include <bitset>

#include "Mira/Math/Vec2.hpp"

#include "InputCodes.hpp"

#include "Mira/Core/Core.hpp"

namespace Mira {

class MIRA_API Input {
friend class Engine;

public:
    static bool isKeyDown(Key key);
    static bool isKeyUp(Key key);
    static bool isKeyHeld(Key key);

    static bool isButtonDown(Button button);
    static bool isButtonUp(Button button);
    static bool isButtonHeld(Button button);

    static Vec2 getMousePosition();
    static Vec2 getMouseDelta();
    static float getMouseWheelOffset();

    enum State {
        Down,
        Up
    };

private:
    static Input& get();
    
    static void setKeyState(Key key, State state);

    static void setButtonState(Button button, State state);
    static void mouseMove(Vec2 pos);
    static void mouseScroll(float offset);


    static void endState();
    static void resetState();


private:
    std::bitset<256> keyState;
    std::bitset<256> previousKeyState;
    std::bitset<5> buttonState;
    std::bitset<5> previousButtonState;

    float xPosition = 0.0f;
    float yPosition = 0.0f;

    Vec2 mousePosition = { 0.0f, 0.0f };

    float dx = 0.0f;
    float dy = 0.0f;
    Vec2 mouseDelta = { 0.0f, 0.0f };

    bool firstMove = true;

    float wheelOffset = 0.0f;

    static Input s_inputState;
};

}
