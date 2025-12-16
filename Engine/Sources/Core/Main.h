#pragma once
#include "GameApp.h"

extern Mira::GameApp* Mira::createApp();

#define CREATE_GAME(x) Mira::GameApp* Mira::createApp() { return new x; }

int main() {
	Mira::GameApp* app = Mira::createApp();
	app->init();
	app->mainloop();
	app->shutdown();
	delete app;
	return 0;
}