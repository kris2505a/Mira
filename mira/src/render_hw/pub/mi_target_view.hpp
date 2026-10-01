#pragma once
#include "mi_rhw_core.hpp"
#include "mi_image.hpp"

namespace mira::rhw {

class MI_RENDER_API ITargetView {
public:
    ITargetView() = default;
    virtual ~ITargetView() = default;

    virtual Image& getImage() const = 0;

};

}