#pragma once
#include "mi_rhw_core.hpp"

namespace mira::rhw {

enum class DescriptorType {
    RTV,
    DSV,
};

class MI_RENDER_API IDescriptorHeap {
public:
    IDescriptorHeap() = default;
    virtual ~IDescriptorHeap() = default;
};

}