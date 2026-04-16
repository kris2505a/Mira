#include <MiraEngine.hpp>

class Sandbox : public Mira::Engine {
public:
    Sandbox() {
        addLayer(std::make_unique<Mira::Layer>("TestLayer"));
    }
};


int main() {
	Mira::Engine* game = new Sandbox();
	game->run();
    delete game;
}
