#pragma once

namespace Mira {

class Drawable {
public:
	virtual void render(const class Renderer* renderer) = 0;
	virtual class Mesh* mesh() const = 0;
	virtual class Material* material() const = 0;
};

}