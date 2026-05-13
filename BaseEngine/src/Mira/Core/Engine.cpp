#include "MiraPch.h"
#include "Mira/Logger/Logger.h"
#include "Engine.h"

namespace Mira {

    WindowAttributes attribs;
    attribs.width = 1280;
    attribs.height = 720;
    attribs.title = "Mira";
    m_window = createScope<WIN32Window>(attribs);


    m_renderer = createScope<Renderer>();
}

void Engine::run() {
    initialize();
    mainLoop();
    shutDown();
}

void Engine::initialize() {

    Logger::log(LogType::Info, "Engine Initializing...");

    Renderer::initialize(m_window->getHandle(), m_window->getWidth(), m_window->getHeight());

    Renderer::clearColor(0.02f, 0.04f, 0.10f, 1.0f);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    m_vbo = VertexBuffer::create(vertices, 3, 3 * sizeof(float));

    uint32_t indices[] = {
        0, 2, 1
    };

    m_ibo = IndexBuffer::create(indices, 3);

    InputLayout layout;
    layout.addLayout({
        "POSITION",
        LayoutDataType::Float,
        3,
        0
    });

    m_shader = Shader::create(L"Def", layout);
}

void Engine::shutDown() {
    Renderer::shutDown();
    Logger::log(LogType::Info, "Engine Shutting Down...");
}

void Engine::mainLoop() {
    Logger::log(LogType::Info, "Engine Running...");
    while (m_window->open) {
        pollEvent();
        update();
        render();
    }
}

void Engine::update() {
    m_vbo->bind();
    m_ibo->bind();
    m_shader->bind();
}

void Engine::render() {
    Renderer::preSetup();

    Renderer::getRHI()->drawIndexed(m_ibo->getCount());

    Renderer::postSetup();
}

void Engine::pollEvent() {
    m_window->pollEvents();
}

}
