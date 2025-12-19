#pragma once
#include "Engine.h"

extern Mira::Engine* Mira::createApp();

#define CREATE_GAME(x) Mira::Engine* Mira::createApp() { return new x; }

int main() {
	Mira::Engine* app = Mira::createApp();
	app->init();
	app->mainloop();
	app->shutdown();
	delete app;
	return 0;
}