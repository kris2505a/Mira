#include <MiraEngine.h>

class GameLayer : public Mira::Layer {
private:
	std::vector <SDL_Rect> m_rectangles;
	std::vector <Mira::Vec2Df> m_velocities;
public:

	virtual void onRender(Mira::Renderer* renderer) override {
		SDL_SetRenderDrawColor(renderer->getRenderer(), 50u, 0u, 200u, 255u);
		for (auto& iter : m_rectangles)
			SDL_RenderFillRect(renderer->getRenderer(), &iter);
	}

	virtual void onAttach() override {
		MIRA_LOG(INFO, "Game Layer Attached");
	}

	virtual void onDetach() override {
		MIRA_LOG(INFO, "Game Layer Detatched");
	}

	virtual void onUpdate(float deltaTime) override {
		
		//MIRA_LOG(INFO, "Number of Particles: {}", m_rectangles.size());

		if (Mira::Input::isButtonPressed(SDL_BUTTON_LEFT)) {
			m_rectangles.push_back(SDL_Rect(Mira::Input::getMousePos().x, Mira::Input::getMousePos().y, 10, 10));
			m_velocities.push_back({2000, 2000});
		}

		for (int i = 0; i < m_rectangles.size(); i++) {
			m_rectangles[i].x += (m_velocities[i].x * deltaTime);
			m_rectangles[i].y += (m_velocities[i].y * deltaTime);

			if (m_rectangles[i].x <= 0 || m_rectangles[i].x >= Mira::GameApp::getInstance()->getWindow()->getWidth())
				m_velocities[i].x *= -1;
			if (m_rectangles[i].y <= 0 || m_rectangles[i].y >= Mira::GameApp::getInstance()->getWindow()->getHeight())
				m_velocities[i].y *= -1;


		}

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