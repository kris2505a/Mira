#pragma once
#include "Mira/Core/MemoryType.h"
#include "InputLayout.h"

namespace Mira {

class Shader {
public:
    Shader() = default;
    virtual ~Shader() = default;
    virtual void bind() const = 0;

    static Scope<Shader> create(const std::wstring& path, InputLayout layout);
};

}