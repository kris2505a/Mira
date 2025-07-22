#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Entity/Entity.h>
#include <MiraEngine/Renderer/Renderer.h>
#include <memory>
#include <vector>

namespace Mira {

class MIRA_API Scene {
public:

	void onUpdate(float deltaTime);
	void onRender(Renderer* renderer);
	void addEntity(...);
	std::vector<std::shared_ptr<Entity>>& getEntities() const;
private:
	std::vector<std::shared_ptr<Entity>> m_entities;
};

}//namespace ends