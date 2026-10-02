#pragma once
#include "mi_rhw_core.hpp"

namespace mira::rhw {

class MI_RENDER_API Image {
public:
    Image() = default;
    virtual ~Image() = default;

    template <typename T>
    T* as() {
        return static_cast<T*>(this);
    }

};

}