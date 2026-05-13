#pragma once
#include "RHI/RHI.h"
#include "Mira/Window/WindowTools.h"

namespace Mira {

class Renderer {
public:
    //static methods
    static void initialize(WindowHandle handle, unsigned int width, unsigned int height);
    static void shutDown();

    static void preSetup();
    static void postSetup();

    static void clearColor(float r, float g, float b, float a);

    static RHI* getRHI();

public:
    Renderer();
    ~Renderer() = default;

private:
    Scope<RHI> m_rhi;

    static Renderer* s_instance;
};

}