#pragma once
#include "core.hpp"

#ifdef PLATFORM_WINDOWS

extern Cyan::Game* Cyan::CreateGame();


int main(int argc, char** argv) {

	printf("Cyan Game Engine");
	auto game = Cyan::CreateGame();
	game->run();
	delete game;

}


#endif