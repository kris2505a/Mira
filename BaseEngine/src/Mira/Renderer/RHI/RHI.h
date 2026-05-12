#pragma once
#include <cstdint>
#include <Windows.h>

#include "Mira/Core/MemoryType.h"


namespace Mira {

enum class API {
    None,
    D3D11
};

class RHI {
public:
    RHI() = default;
    virtual ~RHI() = default;

    virtual void initialize(HWND handle)        = 0;
    virtual void shutdown()                     = 0;

    virtual void bindRenderTarget()             = 0;
    virtual void bindRasterizer()               = 0;
    virtual void bindDepthStencil()             = 0;
    virtual void setViewPort()                  = 0;
    virtual void setTopology()                  = 0;
    virtual void clear()                        = 0;
    virtual void swap()                         = 0;
    virtual void drawIndexed(uint32_t indices)  = 0;
    virtual void resize(int width, int height)  = 0;
    virtual void logGPUInfo()                   = 0;

    virtual void clearColor(float r, float g, float b, float a) = 0;
    virtual void setWireFrameMode(bool cond) = 0;

    static Scope<RHI> createRHI(API api);

    static API getCurrentAPI();

protected:
    static API s_api;
};

}
