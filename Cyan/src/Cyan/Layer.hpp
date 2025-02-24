#pragma once
#include "Cyan/core.hpp"
#include "Cyan/Events/Event.hpp"
#include <string>

namespace Cyan {
	
	class CYANAPI Layer {

	protected:
		std::string m_debugName;

	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event);

		inline const std::string& getName() const { return m_debugName; }
	};
}