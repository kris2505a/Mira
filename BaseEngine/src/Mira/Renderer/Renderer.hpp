#pragma once
#include "RHI/RHI.hpp"
#include "Mira/Window/WindowTools.h"
#include "Mira/EngineComponents/Component.hpp"
#include "Mira/Renderer/RHI/ConstantBuffer.hpp"
#include "Mira/Camera/Camera.hpp"

#include "Mira/Core/Core.hpp"

namespace Mira {

class MIRA_API Renderer {
public:
    //static methods
    static void preSetup();
    static void postSetup();

    static void clearColor(float r, float g, float b, float a);

    static void resize(unsigned int width, unsigned int height);

    static void submit(RenderComponent& renderComponent, TransformComponent& transformComponent);

    static void useCamera(Camera& camera);

    static void setWireFrameMode(bool cond);

    static RHI* getRHI();
    static Renderer* get();

public:
    Renderer();
    ~Renderer();

private:
    Scope<RHI> m_rhi;

    Scope<ConstantBuffer> m_vertexConstantBuffer;
    Scope<ConstantBuffer> m_pixelConstantBuffer;
    DirectX::XMMATRIX m_viewProjectionMatrix;

    
    static Renderer* s_instance;


};

}
