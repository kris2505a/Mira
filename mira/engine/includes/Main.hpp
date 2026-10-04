#pragma once
#include "engine/mi_engine.hpp"

extern auto createGame() -> mira::core::Scope<mira::eng::Game>;


auto main(int argc, char** argv) -> int {
    auto engine = mira::core::createScope<mira::eng::Engine>();
    if (!engine->init()) {
        return EXIT_FAILURE;
    }
    engine->attachGame(mira::eng::createGame());
    engine->run();
    return EXIT_SUCCESS;
}