#include <MiraEngine.h>

class GameLayer : public Mira::Layer {
private:
	SDL_Rect rect = { 100, 100, 200, 150 };

public:

	virtual void onRender(Mira::Renderer* renderer) override {
		SDL_SetRenderDrawColor(renderer->getRenderer(), 50u, 0u, 200u, 255u);
		SDL_RenderFillRect(renderer->getRenderer(), &rect);
	}

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