#pragma once
#include "Core/Core.hpp"
#include <vector>
#include "Entity/Entity.hpp"

namespace Mira {

class MIRA_API World {
public:
	World();
	~World();

	virtual void init();
	virtual void shutdown();

	void render(class Renderer* renderer);
	void spark();
	virtual void pulse(float deltaTime);

protected:
	std::vector <Entity*> m_entities;
};

}