#pragma once
#include "Mira/Core/Core.hpp"
#include "Mira/Event/Event.hpp"
#include "Mira/Core/MemoryType.hpp"


#include <concepts>
#include <string>
#include <type_traits>

namespace Mira {

class MIRA_API Layer {
public:
	Layer(const std::string& name) : m_name(name) {}
	virtual ~Layer() = default;
	virtual void begin() {}
	virtual void end() {}
	virtual void update(float deltaTime) {}
	virtual void handleEvent(Event& e) {}

	[[nodiscard]]
	inline const std::string& getLayerName() const {
		return m_name;
	}

	template<std::derived_from<Layer> T, typename... Args>
	static Scope<Layer> createLayer(Args&... args) {
		return createScope<T>(args...);
	}

private:
	std::string m_name;
};

}