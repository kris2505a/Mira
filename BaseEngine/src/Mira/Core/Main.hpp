#pragma once
#include "Engine.hpp"
#include <exception>
#include "Mira/Logger/Logger.hpp"

extern auto Mira::attachGame() -> void;

int main(int argc, char** argv) {
    auto engine = new Mira::Engine();
    Mira::attachGame();
    engine->run();
    delete engine;
    return 0;
}

