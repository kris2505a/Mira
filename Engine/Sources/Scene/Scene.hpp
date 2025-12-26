#pragma once
#include "Core/Core.hpp"
#include <vector>
#include <cstdint>
#include "Entity.hpp"

namespace Mira {

class MIRA_API Scene {
public:
	Scene(uint32_t id);
	~Scene();

	void init();
	void shutdown();

	virtual void spark();
	virtual void pulse(float deltaTime);
	void render();

	template <typename T> 
	T* create();
	

private:
	uint32_t m_sceneId;
	bool m_initialized;
	std::vector <Entity*> m_entities;
};

template<typename T>
inline T* Scene::create() {
	T* ent = new T;
	m_entities.push_back(ent);
	return ent;
}

}