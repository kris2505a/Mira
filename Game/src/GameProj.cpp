#include "PreCompHeaders.hpp"
#include <Cyan.hpp>

class ExampleLayer : public Cyan::Layer {
public:
	ExampleLayer() : Layer("Example") {

	}

	virtual void onUpdate() override {

	}

};


class GameProj : public Cyan::Game {
public:
	
	Cyan::Layer* exLayer = new ExampleLayer();

	GameProj() {
		pushLayer(exLayer);
	}

	~GameProj() {

	}
};

Cyan::Game* Cyan::CreateGame() {
	return new GameProj;
}