#include <MiraEngine.hpp>
#include <exception>

class Sandbox : public Mira::Engine {
public:
    Sandbox() {
        addLayer(std::make_unique<Mira::Layer>("TestLayer"));
    }

};


int main() {
	Mira::Engine* game = new Sandbox();

    try {
	    game->run();
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete game;
}
