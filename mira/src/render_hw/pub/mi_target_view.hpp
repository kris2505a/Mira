#pragma once
#include "mi_rhw_core.hpp"
#include "mi_image.hpp"
#include <helpers/mi_types.hpp>
#include <vector>
#include "mi_device.hpp"
#include "mi_descriptor_heap.hpp"

namespace mira::rhw {

class MI_RENDER_API ITargetView {
public:
    ITargetView() = default;
    virtual ~ITargetView() = default;

    virtual Image& getImage() const = 0;

    static std::vector<core::Scope<ITargetView>> create(std::vector<core::Scope<Image>>& images, IDescriptorHeap* heap, IDevice* device);

    template<typename T>
    T* as() {
        return static_cast<T*>(this);
    }

};

}