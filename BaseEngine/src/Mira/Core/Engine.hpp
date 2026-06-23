#pragma once
#include "Core.hpp"
#include "Mira/Window/WIN32Window.h"
#include "Mira/Renderer/Renderer.hpp"
#include "Mira/Event/Event.hpp"

#include "Mira/EngineComponents/Layer/LayerManager.hpp"

#include "Mira/Renderer/RenderResourceManager.hpp"
#include "Mira/EngineComponents/Component.hpp"

#include "Game.hpp"


#include <chrono>

namespace Mira {

class MIRA_API Engine {
public:
    void run();
    Engine();
    ~Engine();

    LayerManager& getLayerManager();
    static Engine& get();
    
    Window& getWindow() const;
    auto attachGame(Scope<Game> game) -> void;


private:
    auto mainLoop() -> void;

    auto update() -> void;
    auto handleEvent(Event& e) -> void;
    auto pollEvent() -> void;


private:
    Scope<Window> m_window;
    bool m_running{ true };
    Scope<Renderer> m_renderer;
    LayerManager m_layerManager;
    
    Scope<Game> m_activeGame;

    static Engine* s_instance;

};

auto attachGame() -> void;

}
