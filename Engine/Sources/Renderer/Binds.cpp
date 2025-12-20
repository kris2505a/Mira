#include <PreCompHeader.h>
#include "Binds.h"
#include "Renderer.h"

namespace Mira {

ID3D11Device* Binds::device() const {
	return Renderer::s_instance->m_device.Get();
}

ID3D11DeviceContext* Binds::context() const {
	return Renderer::s_instance->m_context.Get();
}

}