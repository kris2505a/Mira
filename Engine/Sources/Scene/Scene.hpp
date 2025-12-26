#pragma once
#include "Core/Core.hpp"
#include <vector>

namespace Mira {

class MIRA_API Scene {
public:
	Scene();
	~Scene();

	void init();
	void shutdown();

private:
	unsigned int m_sceneId;
};

}