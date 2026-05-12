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

void Renderer::initialize(HWND handle) {
    if (!s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }

    s_instance->m_rhi->initialize(handle);
}

void Renderer::preSetup() {
    if (!s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }
    s_instance->m_rhi->bindRenderTarget();
    s_instance->m_rhi->bindDepthStencil();
    s_instance->m_rhi->setViewPort();
    s_instance->m_rhi->bindRasterizer();
    s_instance->m_rhi->setTopology();
    s_instance->m_rhi->clear();
}

void Renderer::postSetup() {
    if (!s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }
    s_instance->m_rhi->swap();
}

void Renderer::clearColor(float r, float g, float b, float a) {
    if (!s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }

    s_instance->m_rhi->clearColor(r, g, b, a);
}

RHI* Renderer::getRHI() {
    return s_instance->m_rhi.get();
}

void Renderer::shutDown() {
    if (!s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }

    s_instance->m_rhi->shutdown();

    //RAII. NOTHING TO DO.
}


}
