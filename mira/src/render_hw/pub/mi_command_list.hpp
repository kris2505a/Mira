#pragma once
#include "mi_rhw_core.hpp"

#include "mi_device.hpp"
#include "mi_frame_context.hpp"
#include "mi_image.hpp"
#include "mi_target_view.hpp"

#include <array>

namespace mira::rhw {

enum class ResourceState {
    Present,
    RenderTarget,
    CopySource,
    CopyDestination,
    VertexBuffer,
    IndexBuffer
};

class MI_RENDER_API ICommandList {
public:
    ICommandList() = default;
    virtual ~ICommandList() = default;
    virtual void reset(IFrameContext* frameContext) = 0;
    virtual void changeState(Image* img, ResourceState previous, ResourceState next) = 0;
    virtual void setRenderTarget(ITargetView* view) = 0;
    virtual void clearRenderTarget(ITargetView* view, std::array<float, 4>& color) = 0;
    virtual void close() = 0;

    template<typename T>
    T* as() {
        return static_cast<T*>(this);
    }


    static core::Scope<ICommandList> create(IFrameContext* frameContext, IDevice* device);

};

}