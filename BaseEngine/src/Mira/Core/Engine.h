#pragma once
#include "Core.h"
#include "Mira/Window/WIN32Window.h"
#include "Mira/Renderer/Renderer.h"

//Temp
#include "Mira/Renderer/RHI/IndexBuffer.h"
#include "Mira/Renderer/RHI/Shader.h"
#include "Mira/Renderer/RHI/VertexBuffer.h"
#include "Mira/Event/Event.h"

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
    Ref<VertexBuffer> m_vbo;
    Ref<IndexBuffer> m_ibo;
    Ref<Shader> m_shader;
};

Engine* createApp();

}
