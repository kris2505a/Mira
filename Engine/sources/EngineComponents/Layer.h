#pragma once
#include <Base/MiraAPI.h>
#include <Events/Event.h>
#include <string>

namespace Mira {

class MIRA_API Layer {
public:
	Layer(const std::string& name);
	~Layer();
	
	void render();
	void update(float deltaTime);
	void event(Event& e);

	const std::string& getLayerName() const;

protected:
	std::string m_layerName;
};

}