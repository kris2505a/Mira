#pragma once
#include "Core.hpp"
#include "Win32/Window.hpp"
#include "Renderer/Renderer.hpp"
#include "WindowAttributes.hpp"
#include <memory>
#include "Signals/Signal.hpp"
#include "Layers/LayerStack.hpp"
#include "Utils/Timer.hpp"

//debug stuff
#include "Renderer/DbgCube.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/Mesh.hpp"
#include "Components/Camera.hpp"

namespace Mira {

class MIRA_API Engine {
public:
	Engine();
	~Engine();

	void init();
	void shutdown();
	void mainloop();

protected:
	void addLayer(std::unique_ptr <Layer> layer);

private:
	void pulse();
	void render();
	void signal(const Signal& s);

private:
	std::unique_ptr <Window>     m_window;
	std::unique_ptr <Renderer>   m_renderer;
	bool                         m_running;
	WindowAttributes			 m_attrib;
	LayerStack                   m_layerStack;
	Timer						 m_dtClock;
	float						 m_deltaTime;
	bool						 m_initialized;


private:
	//DEBUG STUFF
	DbgCube*					 m_cube;
	DbgCube*					 m_cube2;
	Material*					 m_material;
	Mesh*						 m_mesh;
	Camera*						 m_camera;
};

Engine* createApp();

}