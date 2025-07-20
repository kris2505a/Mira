#include <MiraEngine.h>

class GameLayer : public Mira::Layer {
public:
	virtual void onAttach() override {
		MIRA_LOG(INFO, "Game Layer Attached");
	}

	virtual void onDetach() override {
		MIRA_LOG(INFO, "Game Layer Detatched");
	}

	virtual void onUpdate(float deltaTime) override {
		//MIRA_LOG(INFO, "Game Layer Updating. Deltatime: {}", deltaTime);
	}



};

class Sandbox : public Mira::GameApp {
public:
	Sandbox() {
		pushLayer(new GameLayer());
	}
	~Sandbox() { 
	
	}

};

Mira::GameApp* Mira::createGame() {
	return new Sandbox();
}