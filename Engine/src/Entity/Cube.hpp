#pragma once
#include "Entity.hpp"

class Cube : public Entity {
public:
	Cube()
		: Entity(Mesh::createCubeMesh(), Material::createSolidMaterial()){

	}
	~Cube() = default;
	void update(float deltaTime) override {

	}

private:

};