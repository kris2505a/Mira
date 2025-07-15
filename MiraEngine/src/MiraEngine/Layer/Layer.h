#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Event/Event.h>

namespace Mira {

class MIRA_API Layer {
public:
	virtual void onAttach() {}
	virtual void onDetach() {}

	virtual void onUpdate(float deltaTime) {}
	virtual void onRender() {}

	virtual void onEvent(Event& e) {}
	Layer() = default;
	virtual ~Layer() = default;

};

}