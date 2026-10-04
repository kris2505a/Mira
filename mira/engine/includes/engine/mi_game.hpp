#pragma once
#include "mi_engine_api.hpp"
#include "core/mi_types.hpp"

MI_ENGINE

class MI_ENGINE_API Game {
public:
    Game(std::string_view gameName) 
        : m_gameName(gameName) {}
    virtual ~Game() = default;
    virtual auto init() -> void = 0;
    virtual auto update(mira::core::f32 dt) -> void = 0;

    inline auto getName() const -> std::string_view {
        return m_gameName;
    }

    
    private:
    std::string m_gameName;
};

auto createGame() -> core::Scope<Game>;

MI_ENGINE_END