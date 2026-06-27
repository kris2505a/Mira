#include "MiraPch.hpp"
#include "Mira/Logger/Logger.hpp"
#include "Renderer.hpp"
#include "Mira/Stats/EngineStats.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>


namespace Mira {

struct VertexShaderData {
    glm::mat4 mvp;
    glm::mat4 model;

};

struct PixelShaderData {
    glm::vec4 color;
};

Renderer* Renderer::s_instance = nullptr;

Renderer::Renderer() {
    if (s_instance) {
        throw std::runtime_error("Instance of renderer already exists!");
    }

    s_instance = this;

    Logger::log(LogType::Info, "Renderer - Initializing");

    m_rhi = RHI::createRHI(API::D3D11);

    VertexShaderData nullVertexData;
    nullVertexData.model = glm::mat4(0.0f);
    nullVertexData.mvp = glm::mat4(0.0f);

    PixelShaderData nullPixelData;
    nullPixelData.color = { 0.0f, 0.0f, 0.0f, 0.0f };

    m_vertexConstantBuffer = ConstantBuffer::create(&nullVertexData, sizeof(nullVertexData), ShaderType::VertexShader);
    m_pixelConstantBuffer = ConstantBuffer::create(&nullPixelData, sizeof(nullPixelData), ShaderType::PixelShader);

    m_viewProjectionMatrix = glm::mat4(0.0f);

    Logger::log(LogType::Info, "Renderer - Initialization Successful");
    
    getRHI()->logGPUInfo();
}

Renderer::~Renderer() {
    Logger::log(LogType::Info, "Renderer - Shutting Down");
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

void Renderer::resize() {
    getRHI()->resize();
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
    camera.reCalculateProjection();
    get()->m_viewProjectionMatrix = camera.getViewProjection();
}

void Renderer::submit(RenderComponent& renderComponent, TransformComponent& transformComponent) {
    VertexShaderData vertexData;


    auto translation = glm::translate(glm::mat4(1.0f), glm::vec3(transformComponent.position.x, transformComponent.position.y, transformComponent.position.z));
    auto rotation = glm::yawPitchRoll(transformComponent.rotation.yaw, transformComponent.rotation.pitch, transformComponent.rotation.roll);
    auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(transformComponent.scale.x, transformComponent.scale.y, transformComponent.scale.z));

    auto model = translation * rotation * scale;

    vertexData.model = model;
    vertexData.mvp = get()->m_viewProjectionMatrix * model;

    

    get()->m_vertexConstantBuffer->update(&vertexData, sizeof(vertexData));

    PixelShaderData pixelData;
    pixelData.color = renderComponent.color;
    get()->m_pixelConstantBuffer->update(&pixelData, sizeof(pixelData));

    renderComponent.mesh->bind();
    get()->m_vertexConstantBuffer->bind();
    renderComponent.material->bind();
    get()->m_pixelConstantBuffer->bind();

    getRHI()->drawIndexed(renderComponent.mesh->getIndexCount());

}

void Renderer::setWireFrameMode(bool cond) {
    get()->m_rhi->setWireFrameMode(cond);
}


}
