#pragma once
#include "mi_rhw_core.hpp"
#include <helpers/mi_types.hpp>
#include "mi_device.hpp"


namespace mira::rhw {

class MI_RENDER_API IFrameContext {
public:
    IFrameContext() = default;
    virtual ~IFrameContext() = default;
    virtual core::u64 getFencevalue() const = 0;
    virtual void setFenceValue(core::u64 value) = 0;

    static core::Scope<IFrameContext> create(IDevice* device);   

    template<typename T>
    requires std::is_base_of_v<IFrameContext, T>
    T* as() {
        return static_cast<T*>(this);
    }
};

}