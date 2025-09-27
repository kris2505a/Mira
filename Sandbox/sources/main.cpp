#include "MiraEngine.h"

class Sandbox : public Mira::GameApp {
public:
	Sandbox() {}
	~Sandbox() {}
};

Mira::GameApp* Mira::createGame() {
	return new Sandbox();
}