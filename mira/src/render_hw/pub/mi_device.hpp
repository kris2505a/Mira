#pragma once
#include "mi_rhw_core.hpp"
#include "helpers/mi_types.hpp"

namespace mira::rhw {

class MI_RENDER_API IDevice {
public:
    IDevice() = default;
    virtual ~IDevice() = default;

    template <typename T>
    requires std::is_base_of_v<IDevice, T>
    T& as() {
        return dynamic_cast<T&>(*this);
    }

    const IDevice& getRef() const {
        return *this;
    }

    static core::Scope<IDevice> create();
};


}