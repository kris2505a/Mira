#pragma once
#include "mi_engine_api.hpp"
#include <core/mi_window.hpp>
#include "mi_game.hpp"

MI_ENGINE

class MI_ENGINE_API Engine {
public:
    Engine() = default;
    ~Engine() = default;

    auto init() -> bool;
    auto attachGame(core::Scope<Game> game) -> void;
    auto run() -> void;

private:
    core::Scope<core::Window> m_window;
    core::Scope<Game> m_game;
};

MI_ENGINE_END