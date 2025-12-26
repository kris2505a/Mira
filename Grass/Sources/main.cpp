#include <MiraEngine.hpp>

class GameLayer : public Mira::Layer {
public:
	GameLayer() {}
	~GameLayer() {}
	virtual void pulse(float deltaTime) override {
		
	}

	virtual void signal(const Mira::Signal& s) override {
		
	}

};

class Grass : public Mira::Engine {
public:
	Grass() {
		m_layer = new GameLayer;
		addLayer(m_layer);
	}
	~Grass() {}

private:
	Mira::Layer* m_layer;
};

CREATE_GAME(Grass);