#pragma once
#include "mi_rhw_core.hpp"
#include <helpers/mi_types.hpp>
#include "mi_device.hpp"

namespace mira::rhw {

class MI_RENDER_API IFence {
public:
    IFence() = default;
    virtual ~IFence() = default;
    
    static core::Scope<IFence> create(IDevice* device);
};

}