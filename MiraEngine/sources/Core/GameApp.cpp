#include "MiraPreCompHeader.h"
#include "GameApp.h"

#include <Logger/Log.h>

namespace Mira {
GameApp::GameApp() {

#ifdef MIRA_DEBUG
	this->allocateConsole();
#endif
	m_window = std::make_unique <Window>(GetModuleHandle(nullptr));
	m_renderer = std::make_unique <Renderer>(m_window->getHandle());
}

void GameApp::run() {
	while (m_window->isOpen()) {
		this->handleMessages();
		m_renderer->wipeScreen(0.047f, 0.078f, 0.271f, 1.0f);

		m_renderer->swapBuffers();
	}
}


void GameApp::handleMessages() {
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void GameApp::allocateConsole() {
	AllocConsole();

	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);

	std::ios::sync_with_stdio();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode)) return;

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}

}