#include "MiraEngine.h"

class Sandbox : public Mira::Engine {
public:
	Sandbox() = default;
	~Sandbox() = default;
};

Mira::Engine* Mira::createApp() {
	return new Sandbox;
}