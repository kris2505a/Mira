#include <MiraPreCompHeader.h>
#include "GameApp.h"
#include <MiraEngine/Logging/Log.h>

namespace Mira {

GameApp::GameApp() {

}

GameApp::~GameApp() {

}

void GameApp::render() {

}

void GameApp::update() {

}

void GameApp::run() {
	while (true) {
		update();
		render();
	}
}

} //Namespace Ends