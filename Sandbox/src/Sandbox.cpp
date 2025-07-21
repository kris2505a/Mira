#include <MiraEngine.h>

class GameLayer : public Mira::Layer {
private:
	Mira::Vec2Df pos = { 100.0f, 100.0f };
	SDL_Rect rect = { 10, 10, 50, 50 };

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

	void limitRect() {
		if (rect.x <= 0)
			rect.x = 0;
		if (rect.x >= Mira::GameApp::getInstance()->getWindow()->getWidth() - rect.w)
			rect.x = Mira::GameApp::getInstance()->getWindow()->getWidth() - rect.w;

		if (rect.y <= 0)
			rect.y = 0;
		if (rect.y >= Mira::GameApp::getInstance()->getWindow()->getHeight() - rect.h)
			rect.y = Mira::GameApp::getInstance()->getWindow()->getHeight() - rect.h;
	}

	virtual void onUpdate(float deltaTime) override {
		//MIRA_LOG(INFO, "Game Layer Updating. Deltatime: {}", deltaTime);
		if (Mira::Input::isKeyPressed(SDL_SCANCODE_RIGHT)) {
			pos.x += (3000 * deltaTime);
		}
		if (Mira::Input::isKeyPressed(SDL_SCANCODE_LEFT)) {
			pos.x -= (3000 * deltaTime);
		}
		if (Mira::Input::isKeyPressed(SDL_SCANCODE_UP)) {
			pos.y -= (3000 * deltaTime);
		}
		if (Mira::Input::isKeyPressed(SDL_SCANCODE_DOWN)) {
			pos.y += (3000 * deltaTime);
		}
		rect.x = static_cast<int>(pos.x);
		rect.y = static_cast<int>(pos.y);
		limitRect();
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