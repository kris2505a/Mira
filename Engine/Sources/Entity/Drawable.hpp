#pragma once

namespace Mira {

class Drawable {
public:
	virtual void render(class Renderer* renderer) = 0;
};

}