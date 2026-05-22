#include "MiraEngine.hpp"

class Quad {
public:
	
	Quad() {
		m_renderComponent.mesh = Mira::InstanceManager::createQuadMesh();
		m_renderComponent.material = Mira::InstanceManager::createMaterial("Def");
		m_renderComponent.color = { 0.0f, 1.0f, 1.0f, 1.0f };

		m_transformComponent.position = Mira::Vec3D(0.0f);
		m_transformComponent.rotation = 0;
		m_transformComponent.scale = Mira::Vec3D(m_width * 1.0f, m_height * 1.0f, 1.0f);
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
	float m_width{ 200.0f };
	float m_height{ 200.0f };
};

class Sandbox : public Mira::Engine {
public:
	Sandbox() : Mira::Engine() {

		float width = static_cast<float>(Mira::EngineStats::WindowProperties::getWidth());
		float height = static_cast<float>(Mira::EngineStats::WindowProperties::getHeight());

		m_camera.setViewWidthHeight(width, height);
		m_quad = new Quad();
		getLayerManager().addLayer(Mira::Layer::createLayer<Mira::ImGuiLayer>());
	}

	~Sandbox() {
		if (m_quad)
			delete m_quad;
	}

	void update() {
		Mira::Renderer::useCamera(m_camera);
		Mira::Renderer::submit(m_quad->getRenderComponent(), m_quad->getTransformComponent());
	}

private:
	Mira::OrthographicCamera m_camera;
	Quad* m_quad;

};

Mira::Engine* Mira::createApp() {
	return new Sandbox;
}
