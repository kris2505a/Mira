#pragma once
#include "Core.hpp"
#include "Mira/Window/WIN32Window.h"
#include "Mira/Renderer/Renderer.hpp"
#include "Mira/Event/Event.hpp"

#include "Mira/Renderer/InstanceManager.hpp"
#include "Mira/EngineComponents/Component.hpp"

#include "Mira/Camera/OrthographicCamera.hpp"

namespace Mira {

class MIRA_API Engine {
public:
    void run();
    Engine();

private:
    void initialize();
    void shutDown();
    void mainLoop();
    
    void update();
    void render();
    void handleEvent(Event& e);
    void pollEvent();

    
private:
    Scope<Window> m_window;
    bool m_running{ true };
    Scope<Renderer> m_renderer;

    //tmp
    RenderComponent component;
    OrthographicCamera camera;
};

Engine* createApp();

}
