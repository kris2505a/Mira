#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Renderer/Renderer.h>
#include <MiraEngine/Event/Event.h>
#include <MiraEngine/Event/EventDispatcher.h>
#include <MiraEngine/Event/KeyboardEvent.h>
#include <MiraEngine/Event/MouseEvent.h>
#include <MiraEngine/Logging/Log.h>
#include <MiraEngine/Scene/Scene.h>

namespace Mira {

class MIRA_API Layer {
public:
	virtual void onAttach();
	virtual void onDetach();

	virtual void onUpdate(float deltaTime);
	virtual void onRender(Renderer* renderer);

	void onEvent(Event& e);
	Layer() = default;
	virtual ~Layer() = default;
	Scene* getCurrentScene() const;

private:
	std::unique_ptr <Scene> m_scene;
	static uint32_t s_idGenerator;

};

}