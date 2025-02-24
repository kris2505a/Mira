#include "PreCompHeaders.hpp"
#include "Layer.hpp"
#include "Log.hpp"

namespace Cyan{
	Layer::Layer(const std::string& name) {
		m_debugName = name;
	}

	Layer::~Layer() {

	}

	void Layer::onEvent(Event& event) {
		LOG(CY_TRACE, event.toString());
	}


}
