#pragma once
#include <Core/Core.hpp>
#include <string>
#include <Logging/Log.hpp>

namespace Mira {

class MIRA_API Layer {
public:
	Layer(const std::string& name) : m_name(name) {
        Logger::Log(LogType::Info, "Layer Create: {}", m_name);
    }
	virtual ~Layer() = default;
	virtual void update(float deltaTime) {}
	virtual void render() {}
	virtual void event() {}
    
    inline const std::string& getLayerName() const { return m_name;}

private:
    std::string m_name;
};

}
