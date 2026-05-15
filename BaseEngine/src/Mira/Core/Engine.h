#pragma once
#include "Core.h"
#include "Mira/Window/WIN32Window.h"
#include "Mira/Renderer/Renderer.h"
#include "Mira/Event/Event.h"

//Temp
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
    Ref<Material> m_cubeMaterial;
    Scope<ConstantBuffer> m_vcbo;
    Scope<ConstantBuffer> m_pcbo;
};

Engine* createApp();

}
