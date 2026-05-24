#pragma once
#include "Mira/Core/MemoryType.hpp"
#include "InputLayout.hpp"

namespace Mira {

class Shader {
public:
    Shader() = default;
    virtual ~Shader() = default;
    virtual void bind() const = 0;

    static Ref<Shader> create(const std::wstring& path, const InputLayout& layout);
};

}