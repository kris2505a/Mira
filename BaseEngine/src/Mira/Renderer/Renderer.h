#pragma once
#include "RHI/RHI.h"
#include "Mira/Window/WindowTools.h"
#include "Mira/Components/RenderComponent.h"
#include "Mira/Renderer/RHI/ConstantBuffer.h"
#include "Mira/Camera/Camera.h"

namespace Mira {

class Renderer {
public:
    //static methods
    static void initialize(WindowHandle handle, unsigned int width, unsigned int height);
    static void shutDown();

    static void preSetup();
    static void postSetup();

    static void clearColor(float r, float g, float b, float a);

    static void resize(unsigned int width, unsigned int height);

    static void submit(RenderComponent& component);

    static void useCamera(Camera& camera);

    static RHI* getRHI();
    static Renderer* get();

public:
    Renderer();
    ~Renderer() = default;

private:
    Scope<RHI> m_rhi;

    Scope<ConstantBuffer> m_vertexConstantBuffer;
    Scope<ConstantBuffer> m_pixelConstantBuffer;
    DirectX::XMMATRIX m_viewProjectionMatrix;

    
    static Renderer* s_instance;


};

}
