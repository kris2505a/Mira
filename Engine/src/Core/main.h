#pragma once
#include "GameApp.h"

extern GameApp* createGameApp();

int main(int argc, char** argv) {
	GameApp* game = createGameApp();
	game->run();
	delete game;
}