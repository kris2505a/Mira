#include "MiraPch.hpp"
#include "ImGuiLayer.hpp"

#include "Mira/Renderer/Renderer.hpp"
#include <imgui.h>

#include "Mira/Logger/Logger.hpp"
#include "Mira/Core/Engine.hpp"
#include "Mira/Stats/EngineStats.hpp"

#include "Mira/Input/Input.hpp"

#include "Mira/Event/KeyboardEvent.hpp"
#include "Mira/Event/MouseEvent.hpp"
#include "Mira/Event/WindowEvent.hpp"
#include <imgui_impl_win32.h>


namespace Mira {

ImGuiLayer::ImGuiLayer() 
		: Layer("ImGuiLayer") {}


void ImGuiLayer::attach() {

	Logger::log(LogType::Info, "Layer Attached: {}", getLayerName());

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	Renderer::getRHI()->setupImGui();
}

void ImGuiLayer::detach() {
	Renderer::getRHI()->shutDownImGui();
	ImGui::DestroyContext();
	Logger::log(LogType::Info, "Layer Detached: {}", getLayerName());

}

void ImGuiLayer::update() {
	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize = ImVec2(Engine::get().getWindow().getWidth(), Engine::get().getWindow().getHeight());

	io.DeltaTime = EngineStats::DeltaTime::inSeconds();

}

void ImGuiLayer::render() {
	Renderer::getRHI()->beginImGuiFrame();
	ImGui::NewFrame();

	ImGui::Begin("Greetings");
	ImGui::Text("Vanakkam da mapla, Engine lerunthu...");
	ImGui::End();

	ImGui::Render();
	Renderer::getRHI()->endImGuiFrame();
}

void ImGuiLayer::handleEvent(Event& e) {
	EventDispatcher dispatcher(e);


    dispatcher.dispatch<KeyPressEvent>([this](KeyPressEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		
        io.AddKeyEvent(
            static_cast<ImGuiKey>(toImGuiKey(static_cast<Key>(event.getKey()))),
            true
        );

        return false;
    });

    dispatcher.dispatch<KeyReleaseEvent>([this](KeyReleaseEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        io.AddKeyEvent(
            static_cast<ImGuiKey>(toImGuiKey(static_cast<Key>(event.getKey()))),
            false
        );

        return false;
    });

    dispatcher.dispatch<MouseButtonPressEvent>([this](MouseButtonPressEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        io.AddMouseButtonEvent(
            toImGuiMouseButton(static_cast<Button>(event.getButton())),
            true
        );

        return false;
    });

    dispatcher.dispatch<MouseButtonReleaseEvent>([this](MouseButtonReleaseEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        io.AddMouseButtonEvent(
            toImGuiMouseButton(static_cast<Button>(event.getButton())),
            false
        );
        return false;
    });

    dispatcher.dispatch<MouseMoveEvent>([](const MouseMoveEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        io.AddMousePosEvent(event.getX(), event.getY());

        return false;
    });

    dispatcher.dispatch<MouseScrollEvent>([](MouseScrollEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        io.AddMouseWheelEvent(0.0f, event.getOffset());
        return false;
    });

    dispatcher.dispatch<WindowResizeEvent>([](WindowResizeEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        
        io.DisplaySize = ImVec2(event.getWidth(), event.getHeight());

        return false;
    });

}

int ImGuiLayer::toImGuiKey(Key key) {
    switch (key) {
    case Key::Tab:        
        return ImGuiKey_Tab;
    
    case Key::Left:       
        return ImGuiKey_LeftArrow;
    
    case Key::Right:      
        return ImGuiKey_RightArrow;
    
    case Key::Up:         
        return ImGuiKey_UpArrow;
    
    case Key::Down:       
        return ImGuiKey_DownArrow;


    case Key::Space:      
        return ImGuiKey_Space;
    
    case Key::Enter:      
        return ImGuiKey_Enter;
    
    case Key::Escape:     
        return ImGuiKey_Escape;
    
    case Key::Backspace:  
        return ImGuiKey_Backspace;


    case Key::LeftCtrl:   
        return ImGuiKey_LeftCtrl;
    
    case Key::RightCtrl:  
        return ImGuiKey_RightCtrl;


    case Key::LeftShift:  
        return ImGuiKey_LeftShift;
    
    case Key::RightShift: 
        return ImGuiKey_RightShift;


    case Key::LeftAlt:    
        return ImGuiKey_LeftAlt;
    
    case Key::RightAlt:   
        return ImGuiKey_RightAlt;

    default:
        break;
    }

    // Letters
    if (key >= Key::A && key <= Key::Z) {
        return static_cast<ImGuiKey>(
            ImGuiKey_A +
            (static_cast<int>(key) - static_cast<int>(Key::A))
        );
    }

    // Numbers
    if (key >= Key::Num0 && key <= Key::Num9) {
        return static_cast<ImGuiKey>(
            ImGuiKey_0 +
            (static_cast<int>(key) - static_cast<int>(Key::Num0))
        );
    }

    // Function keys
    if (key >= Key::F1 && key <= Key::F12) {
        return static_cast<ImGuiKey>(
            ImGuiKey_F1 +
            (static_cast<int>(key) - static_cast<int>(Key::F1))
        );
    }

    return ImGuiKey_None;
}

int ImGuiLayer::toImGuiMouseButton(Button button) {
    switch (button) {
    case Button::Left:   
        return 0;

    case Button::Right:  
        return 1;
    
    case Button::Middle: 
        return 2;
    
    case Button::X1:     
        return 3;
    
    case Button::X2:     
        return 4;
    }

    return 0;
}

}