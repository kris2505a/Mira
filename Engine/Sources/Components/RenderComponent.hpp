#pragma once
#include "Renderer/Mesh.hpp"
#include "Renderer/Material.hpp"
#include "Component.hpp"

namespace Mira {

struct RenderComponent : public Component {
	Mesh* mesh;
	Material* material;

};


}