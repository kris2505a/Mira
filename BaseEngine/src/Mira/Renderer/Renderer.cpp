#include "MiraPch.h"
#include "Mira/Logger/Logger.h"
#include "Renderer.h"

namespace Mira {

Renderer* Renderer::s_instance = nullptr;

Renderer::Renderer() {
    if (s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }

    s_instance = this;
    m_rhi = RHI::createRHI(API::D3D11);

}

void Renderer::initialize(WindowHandle handle, unsigned int width, unsigned int height) {
    if (!s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }

    getRHI()->initialize(handle, width, height);
}

void Renderer::preSetup() {
    if (!s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }
    getRHI()->bindRenderTarget();
    getRHI()->bindDepthStencil();
    getRHI()->setViewPort();
    getRHI()->bindRasterizer();
    getRHI()->setTopology();
    getRHI()->clear();
}

void Renderer::postSetup() {
    getRHI()->swap();
}

void Renderer::clearColor(float r, float g, float b, float a) {
    getRHI()->clearColor(r, g, b, a);
}

void Renderer::resize(unsigned int width, unsigned int height) {
    getRHI()->resize(width, height);
}

RHI* Renderer::getRHI() {
    if (!s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }

    return s_instance->m_rhi.get();
}

void Renderer::shutDown() {

    getRHI()->shutdown();

    //RAII. NOTHING TO DO.
}


}
