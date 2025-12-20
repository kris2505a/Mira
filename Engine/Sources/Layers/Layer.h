#pragma once
#include "Signals/Signal.h"
#include "Core/Core.h"

namespace Mira {

class MIRA_API Layer {
public:
	Layer() {}
	~Layer() {}

	virtual void pulse(float deltaTime) {}
	void render() {}
	virtual void signal(const Signal& s) {}

};

}