#pragma once
#include "mi_rhw_core.hpp"
#include <helpers/mi_types.hpp>
#include "mi_device.hpp"

namespace mira::rhw {

class MI_RENDER_API IFence {
public:
    IFence() = default;
    virtual ~IFence() = default;
    virtual void wait(core::u64 fenceValue) = 0;
    virtual void signal(core::u64 value) = 0;

    static core::Scope<IFence> create(IDevice* device);
};

}