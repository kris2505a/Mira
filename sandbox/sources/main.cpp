#include "Main.hpp"
#include <engine/mi_game.hpp>
#include <core/mi_log.hpp>

class BlehGame : public mira::eng::Game {
public:
    BlehGame() : mira::eng::Game("Bleh") {}
    
    auto init() -> void override {
        mira::core::Log::debug("initializing game {}", getName());
    }
    
    auto update(mira::core::f32 dt) -> void override {
        // mira::core::Log::debug("updating {} with DeltaTime {}", getName(), dt);
    }

    ~BlehGame() override = default;
};

mira::core::Scope<mira::eng::Game> mira::eng::createGame() {
    return mira::core::createScope<BlehGame>();
}