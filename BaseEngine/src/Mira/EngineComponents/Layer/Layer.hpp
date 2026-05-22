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
	virtual void attach() {}
	virtual void detach() {}
	virtual void update() {}
	virtual void render() {}
	virtual void handleEvent(Event& e) {}

	inline bool isAttached() const {
		return m_attached;
	}

	[[nodiscard]]
	inline const std::string& getLayerName() const {
		return m_name;
	}

	template<std::derived_from<Layer> T, typename... Args>
	static Layer* createLayer(Args&&... args) {
		return new T(std::forward<Args>(args)...);
	}

protected:
	bool m_attached{ false };

private:
	std::string m_name;
};

}