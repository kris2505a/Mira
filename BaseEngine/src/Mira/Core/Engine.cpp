#include "MiraPch.h"
#include "Engine.h"
#include "Mira/Logger/Logger.h"

namespace Mira {

Engine::Engine() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        Logger::log(LogType::Error, "Failed to init SDL: {}", std::string(SDL_GetError()));
        throw std::runtime_error("Initialization failed!");
    }

    m_window = SDL_CreateWindow("Mira", 1280, 720, 0);

    if (!m_window) {
        Logger::log(LogType::Error, "Failed to create window: {}", std::string(SDL_GetError()));
        throw std::runtime_error("window creation failed");
    }



    m_renderer = createScope<Renderer>();
}

void Engine::run() {
    initialize();
    mainLoop();
    shutDown();
}

void Engine::initialize() {

    HWND hwnd = (HWND)SDL_GetPointerProperty(
    SDL_GetWindowProperties(m_window),
    SDL_PROP_WINDOW_WIN32_HWND_POINTER,
        nullptr
    );

    Renderer::initialize(hwnd);

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
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Engine::mainLoop() {
    Logger::log(LogType::Info, "Engine Running...");
    while (m_running) {
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
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_EVENT_QUIT:
        {
            m_running = false;
            break;
        }

        case SDL_EVENT_WINDOW_RESIZED:
        {
            Logger::log(LogType::Info, "Window Resized!");
            break;
        }
        default:
            break;
        }
    }
}


}