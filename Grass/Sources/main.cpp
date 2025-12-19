#include <Core/Engine.h>
#include <Core/Main.h>

class Grass : public Mira::Engine {
public:
	Grass() {}
	~Grass() {}
};

CREATE_GAME(Grass);