#include "MiraEngine.hpp"

#include <algorithm>

class Cube {
public:
	
	Cube() {
		m_renderComponent.mesh = Mira::RenderResourceManager::createCubeMesh();
		m_renderComponent.material = Mira::RenderResourceManager::createMaterial("CubeMat", "Def", "test.png");
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

class Sandbox : public Mira::Engine {
public:
	Sandbox() : Mira::Engine() {


		m_cube = new Cube();
		getLayerManager().addLayer(Mira::Layer::createLayer<Mira::ImGuiLayer>());
		m_camera.setPosition({ 0.0f, 0.0f, -5.0f });

		Mira::Logger::log(Mira::LogType::Info, "Test Info Log: {}", 1);
		Mira::Logger::log(Mira::LogType::Debug, "Test Debug Log: {}", 2);
		Mira::Logger::log(Mira::LogType::Warning, "Test Warning Log: {}", 3);
		Mira::Logger::log(Mira::LogType::Error, "Test Error Log: {}", 4);

	}

	~Sandbox() {
		if (m_cube)
			delete m_cube;
	}

	void update() override {

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
				-DirectX::XM_PIDIV2 + 0.01f,
				DirectX::XM_PIDIV2 - 0.01f
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

Mira::Engine* Mira::createApp() {
	return new Sandbox;
}
