#include "MiraGameApp.h"
#include <Logging/Log.h>
#include <Events/ApplicationEvent.h>

namespace Mira {
GameApp::GameApp() {

}

GameApp::~GameApp() {

}

void GameApp::run() {

	WindowResizeEvent event(1920, 1080);
	MIRA_LOG_RAW(INFO, event.toString());
	while (true) {
	
	}
}
}