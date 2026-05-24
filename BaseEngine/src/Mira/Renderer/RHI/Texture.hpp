#pragma once
#include "Mira/Core/MemoryType.hpp"
#include <string>

namespace Mira {

class Texture {
public:
    Texture() = default;
    virtual ~Texture() = default;
    virtual void bind(int slot = 0) const = 0;
    static Ref<Texture> create(const std::string& path);
    static Ref<Texture> create();
};

}