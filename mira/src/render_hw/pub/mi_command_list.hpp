#pragma once
#include "mi_rhw_core.hpp"

#include "mi_device.hpp"
#include "mi_frame_context.hpp"

namespace mira::rhw {

class MI_RENDER_API ICommandList {
public:
    ICommandList() = default;
    virtual ~ICommandList() = default;

    static core::Scope<ICommandList> create(IFrameContext* frameContext, IDevice* device);

};

}