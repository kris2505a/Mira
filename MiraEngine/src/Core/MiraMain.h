#pragma once
#include "MiraGameApp.h"

extern Mira::GameApp* Mira::createGameApp();

int main(int argc, char** argv) {
	auto gameApp = Mira::createGameApp();
	gameApp->run();
	delete gameApp;
	return 0;
}