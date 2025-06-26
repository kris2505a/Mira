#include <MiraEngine.h>

class SandBox : public Mira::GameApp {
public:
	SandBox() {}
	~SandBox() {}
};

Mira::GameApp* Mira::createGameApp() {
	return new SandBox();
}