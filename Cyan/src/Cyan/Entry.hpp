#pragma once

#ifdef PLATFORM_WINDOWS

extern Cyan::Game* Cyan::CreateGame();


int main(int argc, char** argv) {

	Cyan::Log::init();
	CYAN_LOG(CY_ERROR, "YAY");
	LOG(CY_FATAL, "Game YAY");
	auto game = Cyan::CreateGame();
	game->run();
	delete game;

}


#endif