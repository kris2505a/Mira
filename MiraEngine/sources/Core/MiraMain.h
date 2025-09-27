#pragma once
#include "GameApp.h"
#include <windows.h>

extern Mira::GameApp* Mira::createGame();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	Mira::GameApp* game = Mira::createGame();
	game->run();
	delete game;
	return 0;

}