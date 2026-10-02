#pragma once
#include "mi_rhw_core.hpp"

#include <helpers/mi_types.hpp>
#include "mi_device.hpp"

namespace mira::rhw {

enum class DescriptorType {
    RTV,
    DSV,
};

class MI_RENDER_API IDescriptorHeap {
public:
    IDescriptorHeap() = default;
    virtual ~IDescriptorHeap() = default;

    template<typename T>
    T* as() {
        return static_cast<T*>(this);
    }

    static core::Scope<IDescriptorHeap> create(core::u32 count, DescriptorType type, IDevice* device, bool shaderVisible);

};

}