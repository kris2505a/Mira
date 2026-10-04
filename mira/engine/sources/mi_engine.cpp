#include "engine/mi_engine.hpp"
#include "core/mi_log.hpp"

MI_ENGINE

auto Engine::init() -> bool {
    auto tmpWnd = core::Window::create();
    if (!tmpWnd) {
        core::Log::error("window creation failed: {}", tmpWnd.error());
        return false;
    }
    m_window = std::move(*tmpWnd);
    return true;
}

auto Engine::run() -> void {
    bool running = true;

    m_game->init();
    while (running) {
        running = m_window->pollEvents();
        m_game->update(0.0f);
    }
}

auto Engine::attachGame(core::Scope<Game> game) -> void {
    m_game = std::move(game);
}


MI_ENGINE_END