#include <MiraPreCompHeader.h>
#include "GameApp.h"
#include <MiraEngine/Logging/Log.h>

namespace Mira {

GameApp::GameApp() {

}

GameApp::~GameApp() {

}

void GameApp::run() {
	while (true) {
		MIRA_ELOG(INFO, "Sixty Nine: {}", 69);
	}
}

} //Namespace Ends