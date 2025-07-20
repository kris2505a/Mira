#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Event/Event.h>
#include <MiraEngine/Event/EventDispatcher.h>
#include <MiraEngine/Event/KeyboardEvent.h>
#include <MiraEngine/Event/MouseEvent.h>
#include <MiraEngine/Logging/Log.h>

namespace Mira {

class MIRA_API Layer {
public:
	virtual void onAttach() {}
	virtual void onDetach() {}

	virtual void onUpdate(float deltaTime) {}
	virtual void onRender() {}

	void onEvent(Event& e) {
		
	}
	Layer() = default;
	virtual ~Layer() = default;

};

}