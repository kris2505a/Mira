#include <MiraEngine.h>

class SandBox : public Mira::GameApp {
public:
	SandBox() {
		MIRA_LOG(DEBUG, "Sandbox created Successfully code:{}", 69);
	}
	~SandBox() {}
};

Mira::GameApp* Mira::createGameApp() {
	return new SandBox();
}