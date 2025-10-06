#pragma once
#include <Windows.h>
#include <Base/MiraAPI.h>

namespace Mira {

class MIRA_API Mouse {
	friend class Input;
	friend class Win32Window;

private:
	Mouse() = delete;
	~Mouse() = delete;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	Mouse(Mouse&&) = delete;
	Mouse& operator=(Mouse&&) = delete;

	//functions accessible using window.cpp
	static void buttonDown(WPARAM button);
	static void buttonUp(WPARAM button);
	static void move(int x, int y);
	static void scroll(int delta);
	static bool isInWindow();
	static void inWindow();
	static void offWindow();

private:
	static bool m_left;
	static bool m_right;
	static bool m_middle;
	static bool m_inWindow;
	static int m_xPos;
	static int m_yPos;
	static int m_wheel;
};

}