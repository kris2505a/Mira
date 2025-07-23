#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Entity/Entity.h>
#include <MiraEngine/Renderer/Renderer.h>
#include <memory>
#include <vector>

namespace Mira {

class MIRA_API Scene {
public:
	Scene(uint32_t _sceneId, const std::string& _name);
	~Scene();
	virtual void onUpdate(float deltaTime);
	virtual void onRender(Renderer* renderer);
	std::vector<std::shared_ptr<Entity>>& getEntities();
	
	template <typename T, typename... Args> 
	T& createEntity(Args&... args);

	uint32_t getId() const;
	const std::string& getName() const;

private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	uint32_t m_sceneId;
	std::string m_name;
};

}//namespace ends