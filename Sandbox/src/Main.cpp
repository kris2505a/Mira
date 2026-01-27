#include <App/Engine.h>

class SandBox : public Mira::Engine {
public:
	SandBox() {
		dxr::Renderer::setBackGroundColor(0.0f, 1.0f, 1.0f, 1.0f);
	}
	~SandBox() {}
};

int main() {
	Mira::Engine* app = new SandBox();
	app->run();
	delete app;
	return 0;
}