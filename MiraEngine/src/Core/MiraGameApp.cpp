#include "MiraGameApp.h"
#include <Logging/Log.h>

namespace Mira {
GameApp::GameApp() {

}

GameApp::~GameApp() {

}

void GameApp::run() {
	MIRA_ELOG(Type::INFO, "Mira Init Successful. code:{}", (int)1);
	while (true) {
	
	}
}
}