#include "MiraPch.h"
#include "Mira/Logger/Logger.h"
#include "Renderer.h"

namespace Mira {

struct VertexShaderData {
    DirectX::XMMATRIX mvp;
    DirectX::XMMATRIX model;
};

struct alignas(16) PixelShaderData {
    DirectX::XMFLOAT4 color;
    int useTexture = 0;
};

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


    VertexShaderData nullVertexData;
    nullVertexData.model = DirectX::XMMatrixIdentity();
    nullVertexData.mvp = DirectX::XMMatrixIdentity();
    
    PixelShaderData nullPixelData;
    nullPixelData.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    nullPixelData.useTexture = 0;
    
    get()->m_vertexConstantBuffer = ConstantBuffer::create(&nullVertexData, sizeof(nullVertexData), ShaderType::VertexShader);
    get()->m_pixelConstantBuffer = ConstantBuffer::create(&nullPixelData, sizeof(nullPixelData), ShaderType::PixelShader);

    get()->m_viewProjectionMatrix = DirectX::XMMatrixIdentity();

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

Renderer* Renderer::get() {
    return s_instance;
}

void Renderer::shutDown() {

    getRHI()->shutdown();

    //RAII. NOTHING TO DO.
}

void Renderer::useCamera(Camera& camera) {
    get()->m_viewProjectionMatrix = camera.getViewProjection();
}

void Renderer::submit(RenderComponent& component) {
    component.mesh->bind();
    component.material->bind();

    VertexShaderData vertexData;
    vertexData.model = DirectX::XMMatrixTranspose(component.modelMatrix);
    vertexData.mvp = DirectX::XMMatrixTranspose(
        component.modelMatrix *
        get()->m_viewProjectionMatrix
    );
    get()->m_vertexConstantBuffer->update(&vertexData, sizeof(vertexData));

    PixelShaderData pixelData;
    pixelData.color = component.color;
    pixelData.useTexture = component.material->hasTexture();
    get()->m_pixelConstantBuffer->update(&pixelData, sizeof(pixelData));

    component.mesh->bind();
    get()->m_vertexConstantBuffer->bind();
    component.material->bind();
    get()->m_pixelConstantBuffer->bind();

    getRHI()->drawIndexed(component.mesh->getIndexCount());

}


}
