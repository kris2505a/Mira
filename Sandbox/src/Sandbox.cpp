#include <MiraEngine.h>
#include <SFML/Graphics.hpp>

class Rectangle : public Mira::Entity {
private:
	Mira::Vec2Df m_position;
	Mira::Vec2Df m_size;
	Mira::Vec2Df m_velocity;
	sf::RectangleShape m_rectangle;

	
public:
	Rectangle() {
		
		m_position = { 100, 100 };
		 
		m_size = { 50, 50 };

		m_rectangle.setPosition(m_position);
		m_rectangle.setSize(m_size);
		m_velocity = { 1000.0f, 1000.0f };
		m_rectangle.setFillColor(sf::Color::White);
	}
	virtual void update(float deltatime) override {

		if (Mira::Input::isKeyPressed(sf::Keyboard::Left)) {
			m_position.x -= m_velocity.x * deltatime;
		}
		if (Mira::Input::isKeyPressed(sf::Keyboard::Right)) {
			m_position.x += m_velocity.x * deltatime;
		}
		if (Mira::Input::isKeyPressed(sf::Keyboard::Up)) {
			m_position.y -= m_velocity.y * deltatime;
		}
		if (Mira::Input::isKeyPressed(sf::Keyboard::Down)) {
			m_position.y += m_velocity.y * deltatime;
		}
		
		m_rectangle.setPosition(m_position);

	}

	virtual void render(Mira::Renderer* renderer) override {
		renderer->render(m_rectangle);
	}
};

class GameScene : public Mira::Scene {

public:
	GameScene() : Mira::Scene(0, "Scene") {
		m_entities.push_back(std::make_shared<Rectangle>());
		//this->createEntity <Rectangle> ();
	}
};


class GameLayer : public Mira::Layer {
private:
	int m_sceneId;
public:

	GameLayer() : m_sceneId(0) {
		//m_sceneId = this->createScene <Mira::Scene> ();
		m_scenes.push_back(std::make_unique <GameScene>());
	}

	virtual void onAttach() override {
		MIRA_LOG(INFO, "Game Layer Attached");
	}

	virtual void onDetach() override {
		MIRA_LOG(INFO, "Game Layer Detatched");
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