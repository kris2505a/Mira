#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Entity/Entity.h>
#include <MiraEngine/Renderer/Renderer.h>
#include <MiraEngine/Entity/Components.h>
#include <memory>
#include <vector>

namespace Mira {

class MIRA_API Scene {

	friend class Entity;
public:
	Scene(uint32_t _sceneId, const std::string& _name);
	~Scene();
	virtual void update(float deltaTime);
	virtual void render(Renderer* renderer);
	std::vector<std::shared_ptr<Entity>>& getEntities();
	
	template <typename T, typename... Args> 
	T& createEntity(Args&... args);

	uint32_t getId() const;
	const std::string& getName() const;

private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	uint32_t m_sceneId;
	std::string m_name;
	static uint32_t m_entityIdGenerator;
	std::unordered_map <uint32_t, TransformComponent> m_transformComponents;
};

}//namespace ends