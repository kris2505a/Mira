#include <Private/Dx11GraphicsFactory.hpp>
#include <Private/Dx11RenderAPI.hpp>
#include <Private/Dx11VertexBuffer.hpp>
#include <Private/Dx11IndexBuffer.hpp>
#include <Private/Dx11Shader.hpp>

namespace mr {

std::unique_ptr<RenderAPI> Dx11GraphicsFactory::createRenderAPI(HWND handle) {
    auto api = std::make_unique <Dx11RenderAPI>();
    api->init(handle);
    p_device    = api->getDevice();
    p_context   = api->getContext();
    return api;
}

std::unique_ptr<VertexBuffer> Dx11GraphicsFactory::createVertexBuffer(const void* data, int count, int stride, int offset) {
    return std::make_unique<Dx11VertexBuffer>(p_device, p_context, data, count, stride, offset);
}

std::unique_ptr<IndexBuffer> Dx11GraphicsFactory::createIndexBuffer(const void* data, int count, int offset) {
    return std::make_unique<Dx11IndexBuffer>(p_device, p_context, data, count, offset);
}

std::unique_ptr<Shader> Dx11GraphicsFactory::createShader(const std::wstring& name, const InputLayout& layout) {
    return std::make_unique<Dx11Shader>(name, layout, p_device, p_context);
}

}