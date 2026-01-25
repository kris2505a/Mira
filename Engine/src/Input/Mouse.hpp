#pragma once
#include <Windows.h>
#include "KeyCodes.hpp"



class Mouse {
	friend class Input;
	friend class Window;
public:
	Mouse() = delete;
	~Mouse() = delete;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	Mouse(Mouse&&) = delete;
	Mouse& operator=(Mouse&&) = delete;

	static void lockMouse(bool condition);
	static float xDelta();
	static float yDelta();


	//functions accessible using window.cpp
private:
	static void buttonDown(Button button);
	static void buttonUp(Button button);
	static void move(int x, int y);
	static void scroll(int delta);
	static bool isInWindow();
	static void inWindow();
	static void offWindow();

private:
	static bool m_left;
	static bool m_right;
	static bool m_middle;
	static bool m_x1;
	static bool m_x2;
	static bool m_inWindow;
	static int m_xPos;
	static int m_yPos;
	static float m_deltaX;
	static float m_deltaY;
	static int m_wheel;
	static bool m_firstMove;
	static bool m_locked;
	static bool m_ignoreMove;
};

