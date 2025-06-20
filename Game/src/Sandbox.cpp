#include <Engine.h>

class API SandBox : public GameApp {
public:
	SandBox() {}
	~SandBox() {}
};

GameApp* createGameApp() {
	return new SandBox();
}