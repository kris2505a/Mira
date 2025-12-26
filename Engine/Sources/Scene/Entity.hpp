#pragma once
#include "Core/Core.hpp"

namespace Mira {

class MIRA_API Entity {
public:
	Entity() {}
	~Entity() {}
	
	void render() {}
	void spark() {}
	void pulse(float deltaTime) {}

};

}