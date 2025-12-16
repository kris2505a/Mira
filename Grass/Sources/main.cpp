#include <Core/GameApp.h>
#include <Core/Main.h>

class Grass : public Mira::GameApp {
public:
	Grass() {}
	~Grass() {}
};

CREATE_GAME(Grass);