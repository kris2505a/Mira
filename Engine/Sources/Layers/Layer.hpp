#pragma once
#include "Signals/Signal.hpp"
#include "Core/Core.hpp"

namespace Mira {

class MIRA_API Layer {
public:
	Layer() {}
	~Layer() {}

	virtual void pulse(float deltaTime) {}
	virtual void render() {}
	virtual void signal(const Signal& s) {}

};

}