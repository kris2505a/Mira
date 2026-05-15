#pragma once
#include "Core.h"
#include "Mira/Window/WIN32Window.h"
#include "Mira/Renderer/Renderer.h"

//Temp
#include "Mira/Renderer/RHI/Shader.h"
#include "Mira/Event/Event.h"
#include "Mira/Renderer/InstanceManager.h"
#include "Mira/Renderer/RHI/ConstantBuffer.h"

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
    Ref<Mesh> m_cubeMesh;
    Scope<Shader> m_shader;
    Scope<ConstantBuffer> m_cbo;
};

Engine* createApp();

}
