#include "MiraEngine.hpp"

#include <algorithm>
#include <glm/gtc/constants.hpp>

class Cube {
public:

	Cube() {
		m_renderComponent.mesh = Mira::RenderResourceManager::createCubeMesh();
		m_renderComponent.material = Mira::RenderResourceManager::createMaterial("CubeMat");
		m_renderComponent.color = { 1.0f, 1.0f, 1.0f, 1.0f };

		m_transformComponent.position = Mira::Vec3(0.0f);
		m_transformComponent.rotation = 0;
		m_transformComponent.scale = Mira::Vec3(1.0f, 1.0f, 1.0f);
	}

	Mira::RenderComponent& getRenderComponent() {
		return m_renderComponent;
	}

	Mira::TransformComponent& getTransformComponent() {
		return m_transformComponent;
	}

private:
	Mira::RenderComponent m_renderComponent;
	Mira::TransformComponent m_transformComponent;
};

class TestGame : public Mira::Game 
{
public:
	TestGame() 
	{
		m_cube = new Cube();
		m_camera.setPosition({ 0.0f, 0.0f, -5.0f });

		m_cube->getRenderComponent().color = { 1.0f, 0.0f, 0.0f, 1.0f };
	}

	~TestGame() override 
	{
		if (m_cube)
			delete m_cube;
	}

	auto update() -> void 
	{
		auto pos = m_camera.getPosition();

		if (Mira::Input::isButtonHeld(Mira::Button::Right)) {

			if (Mira::Input::isKeyHeld(Mira::Key::S)) {
				pos -= m_camera.getForwardVector() * speed * Mira::EngineStats::DeltaTime::inSeconds();
			}

			if (Mira::Input::isKeyHeld(Mira::Key::W)) {
				pos += m_camera.getForwardVector() * speed * Mira::EngineStats::DeltaTime::inSeconds();
			}

			if (Mira::Input::isKeyHeld(Mira::Key::A)) {
				pos -= m_camera.getRightVector() * speed * Mira::EngineStats::DeltaTime::inSeconds();
			}

			if (Mira::Input::isKeyHeld(Mira::Key::D)) {
				pos += m_camera.getRightVector() * speed * Mira::EngineStats::DeltaTime::inSeconds();
			}

			auto rot = m_camera.getRotation();

			rot.pitch -= Mira::Input::getMouseDelta().y * sensitivity * Mira::EngineStats::DeltaTime::inMilliseconds();
			rot.yaw += Mira::Input::getMouseDelta().x * sensitivity * Mira::EngineStats::DeltaTime::inMilliseconds();

			rot.pitch = std::clamp(
				rot.pitch,
				-glm::pi<float>() / 2.0f + 0.01f,
				glm::pi<float>() / 2.0f - 0.01f
			);

			m_camera.setRotation(rot);
			m_camera.setPosition(pos);
		}

		Mira::Renderer::useCamera(m_camera);
		Mira::Renderer::submit(m_cube->getRenderComponent(), m_cube->getTransformComponent());
	}

private:
	Mira::PerspectiveCamera m_camera;
	Cube* m_cube;
	float sensitivity{ 0.0005f };
	float speed{ 7.5f };
};



class Sandbox : public Mira::Engine {
public:
	Sandbox() : Mira::Engine() {
		getLayerManager().addLayer(Mira::Layer::createLayer<Mira::ImGuiLayer>());
		attachGame(createScope<TestGame>());

	}

	~Sandbox() {

	}

private:


};

Mira::Engine* Mira::createApp() {
	return new Sandbox;
}
