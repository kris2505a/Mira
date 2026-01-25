#include <Window/Window.hpp>
#include <Rendering/Renderer.hpp>
#include <Rendering/ConstantBuffer.hpp>
#include <Entity/Cube.hpp>
#include <Input/Keyboard.hpp>

#include <Rendering/Vertex.hpp>
#include <vector>
#include <Components/Camera.hpp>
#include <Input/Mouse.hpp>
#include <Input/Input.hpp>
#include <Input/KeyCodes.hpp>

void updateCamera(Camera* camera) {
	
	auto pos = camera->getPosition();
	float speed = 0.005f;

	if (Input::isKeyDown(Key::A)) {
		pos = dx::XMVectorSubtract(pos, dx::XMVectorScale(camera->getRightVector(), speed));
	}
	if (Input::isKeyDown(Key::D)) {
		pos = dx::XMVectorAdd(pos, dx::XMVectorScale(camera->getRightVector(), speed));
	}
	if (Input::isKeyDown(Key::W)) {
		pos = dx::XMVectorAdd(pos, dx::XMVectorScale(camera->getForwardVector(), speed));
	}
	if (Input::isKeyDown(Key::S)) {
		pos = dx::XMVectorSubtract(pos, dx::XMVectorScale(camera->getForwardVector(), speed));
	}

	camera->setPosition(pos);

	if (Input::isButtonDown(Button::Right)) {
		Mouse::lockMouse(true);
	}

	if (Input::isButtonUp(Button::Right)) {
		Mouse::lockMouse(false);
	}

	if (Input::isButtonDown(Button::Right)) {
		Mouse::lockMouse(true);
		auto dx = camera->getYaw() + Mouse::xDelta() * 0.002;
		auto dy = camera->getPitch() - Mouse::yDelta() * 0.002;

		camera->setRotation(0.0f, dy, dx);
	}
}

int main() {

	Window window(1280, 720, L"Medium Gyatt");
	Renderer renderer(window.getHandle());

	Camera camera;

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

	while (window.isOpen()) {
		window.handleMessages();
		renderer.preRender();

		updateCamera(&camera);

		for (auto& i : cubes) {
			i->update(1 / 60.0f);
			renderer.renderEntity(i);
		}

		renderer.postRender();
		Keyboard::endState();

	}
	for (auto& i : cubes) {
		if (i)
			delete i;
	}
}
