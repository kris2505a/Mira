#include "MiraPch.hpp"
#include "Mira/Logger/Logger.hpp"
#include "Renderer.hpp"
#include "Mira/Stats/EngineStats.hpp"

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

    getRHI()->initialize(
        EngineStats::WindowProperties::getHandle(), 
        EngineStats::WindowProperties::getWidth(), 
        EngineStats::WindowProperties::getHeight()
    );


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

Renderer::~Renderer() {
    getRHI()->shutdown();
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

void Renderer::useCamera(Camera& camera) {
    camera.setViewWidthHeight(get()->m_rhi->getRenderDimensions().x, get()->m_rhi->getRenderDimensions().y);
    get()->m_viewProjectionMatrix = camera.getViewProjection();
}

void Renderer::submit(RenderComponent& renderComponent, TransformComponent& transformComponent) {
    VertexShaderData vertexData;

    auto model = DirectX::XMMatrixScaling(transformComponent.scale.x, transformComponent.scale.y, transformComponent.scale.z) *
        DirectX::XMMatrixRotationRollPitchYaw(transformComponent.rotation.x, transformComponent.rotation.y, transformComponent.rotation.z) *
        DirectX::XMMatrixTranslation(transformComponent.position.x, transformComponent.position.y, transformComponent.position.z);

    vertexData.model = DirectX::XMMatrixTranspose(model);
    vertexData.mvp = DirectX::XMMatrixTranspose(
        model *
        get()->m_viewProjectionMatrix
    );
    get()->m_vertexConstantBuffer->update(&vertexData, sizeof(vertexData));

    PixelShaderData pixelData;
    pixelData.color = renderComponent.color;
    pixelData.useTexture = renderComponent.material->hasTexture() ? 1 : 0;
    get()->m_pixelConstantBuffer->update(&pixelData, sizeof(pixelData));

    renderComponent.mesh->bind();
    get()->m_vertexConstantBuffer->bind();
    renderComponent.material->bind();
    get()->m_pixelConstantBuffer->bind();

    getRHI()->drawIndexed(renderComponent.mesh->getIndexCount());

}


}
