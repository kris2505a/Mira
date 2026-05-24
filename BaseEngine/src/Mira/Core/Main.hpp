#pragma once
#include "Engine.hpp"
#include <exception>
#include "Mira/Logger/Logger.hpp"

extern Mira::Engine* Mira::createApp();

int main(int argc, char** argv) {
    auto app = Mira::createApp();

    try {
        app->run();
    }
    catch (std::exception& e) {
        Mira::Logger::log(Mira::LogType::Error, "{}", std::string(e.what()));
    }
}

