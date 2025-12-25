#include <MiraEngine.hpp>

class GameLayer : public Mira::Layer {
public:
	GameLayer() {}
	~GameLayer() {}
	virtual void pulse(float deltaTime) override {
		
	}

	virtual void signal(const Mira::Signal& s) override {
		if (Mira::Signal::match <Mira::MouseButtonDownSignal>(s) || Mira::Signal::match <Mira::KeyboardSignal>(s)) {
			MIRA_LOG(LOG_DEBUG, "{}", s.name());
		}
		
	}

};

class Grass : public Mira::Engine {
public:
	Grass() {
		m_layer = std::make_unique <GameLayer>();
		addLayer(std::move(m_layer));
	}
	~Grass() {}

private:
	std::unique_ptr <Mira::Layer> m_layer;
};

CREATE_GAME(Grass);