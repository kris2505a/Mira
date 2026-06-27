#pragma once
#include <bitset>

#include "Mira/Math/Vec2.hpp"

#include "InputCodes.hpp"

#include "Mira/Core/Core.hpp"

namespace Mira {

class MIRA_API Input {
friend class Engine;

public:
    static auto isKeyDown(Key key) -> bool;
    static auto isKeyUp(Key key) -> bool;
    static auto isKeyHeld(Key key) -> bool;

    static auto isButtonDown(Button button) -> bool;
    static auto isButtonUp(Button button) -> bool;
    static auto isButtonHeld(Button button) -> bool;

    static auto getMousePosition() -> Vec2;
    static auto getMouseDelta() -> Vec2;
    static auto getMouseWheelOffset() -> float;

    static auto lockMouse(bool cond) -> void;


    enum State {
        Down,
        Up
    };

private:
    static auto get() -> Input&;
    
    static auto setKeyState(Key key, State state) -> void;

    static auto setButtonState(Button button, State state) -> void;
    static auto mouseMove(Vec2 pos) -> void;
    static auto mouseScroll(float offset) -> void;


    static auto endState() -> void;
    static auto resetState() -> void;


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
    bool mouseLock = false;

    float wheelOffset = 0.0f;

    static Input s_inputState;
};

}
