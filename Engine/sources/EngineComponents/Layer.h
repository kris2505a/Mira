#pragma once
#include <Base/MiraAPI.h>
#include <string>

namespace Mira {

class MIRA_API Layer {
public:
	Layer(const std::string& name);
	~Layer();

	const std::string& getLayerName() const;

protected:
	std::string m_layerName;
};

}