#pragma once
#include "Core.hpp"
#include "Win32/Window.hpp"
#include "Renderer/Renderer.hpp"
#include "WindowAttributes.hpp"
#include <memory>
#include "Signals/Signal.hpp"
#include "Utils/Timer.hpp"
#include "Layers/ImGuiLayer.hpp"

//debug stuff
#include "Renderer/Material.hpp"
#include "Renderer/Mesh.hpp"
#include "Components/Camera.hpp"
#include "Entity/Cube.hpp"

namespace Mira {

class MIRA_API Engine {
public:
	Engine();
	~Engine();

	void init();
	void shutdown();
	void mainloop();

private:
	void pulse();
	void render();
	void signal(const Signal& s);

private:
	Window*					     m_window;
	Renderer*				     m_renderer;
	bool                         m_running;
	WindowAttributes			 m_attrib;
	Timer						 m_dtClock;
	float						 m_deltaTime;
	bool						 m_initialized;
	ImGuiLayer*					 m_imguiLayer;

private:
	//DEBUG STUFF
	Material*					 m_material;
	Mesh*						 m_mesh;
	Camera*						 m_camera;
	Cube*						 m_cube;
};

Engine* createApp();

}