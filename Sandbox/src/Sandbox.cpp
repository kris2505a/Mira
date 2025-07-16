#include <MiraEngine.h>

class GameLayer : public Mira::Layer {
public:
	virtual void onAttach() override {
		MIRA_LOG(INFO, "Game Layer Attached");
	}

	virtual void onDetach() override {
		MIRA_LOG(INFO, "Game Layer Detatched");
	}

	virtual void onUpdate(float _deltaTime) override {
		//MIRA_LOG(INFO, "Game Layer Updating. Deltatime: {}", _deltaTime);
	}

	virtual void onEvent(Mira::Event& _e) override {
		Mira::EventDispatcher dispatcher(_e);
		dispatcher.dispatch<Mira::KeyPressedEvent>([](Mira::KeyPressedEvent& e) {
			MIRA_LOG(INFO, "{}", e.toString());
			return false;
		});
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