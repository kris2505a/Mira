#include <Window/Window.hpp>
#include <Rendering/Renderer.hpp>
#include <Rendering/ConstantBuffer.hpp>
#include <Entity/Cube.hpp>

#include <Rendering/Vertex.hpp>
#include <vector>
#include <Components/Camera.hpp>


int main() {

	Window window(1280, 720, "Medium Gyatt");
	Renderer renderer(window.handle());

	Camera camera;
	camera.position = dx::XMVectorSet(0, 0, -5, 1);

	renderer.setActiveCamera(&camera);

	std::vector	<Entity*> cubes;
	cubes.push_back(new Cube());
	cubes[0]->setPosition({ -2, 0, 0 });
	cubes[0]->getMaterial()->setTexture("texture/block.png");
	cubes.push_back(new Cube());
	cubes[1]->setPosition({ 2, 0, 0 });
	cubes[1]->getMaterial()->setColor(0, 1, 0, 1);
	cubes.push_back(new Cube());
	cubes[2]->getMaterial()->setColor(1, 1, 0, 1);

	while (window.open()) {
		window.pollEvents();
		renderer.preRender();

		for (auto& i : cubes) {
			i->update(1 / 60.0f);
			renderer.renderEntity(i);
		}

		renderer.postRender();
	}
	for (auto& i : cubes) {
		if (i)
			delete i;
	}
}