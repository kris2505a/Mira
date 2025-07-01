#include <MiraPreCompHeader.h>
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
	MIRA_ELOG(INFO, "{}",event.toString());
	while (true) {
	
	}
}
}