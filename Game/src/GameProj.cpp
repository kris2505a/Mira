#include "PreCompHeaders.hpp"
#include <Cyan.hpp>


class GameProj : public Cyan::Game {
public:
	
	GameProj() {

	}

	~GameProj() {

	}
};

Cyan::Game* Cyan::CreateGame() {
	return new GameProj;
}