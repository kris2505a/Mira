#pragma once
#include "Binds.h"

namespace Mira {

class VertexBuffer : public Binds {
public:
	VertexBuffer(const void* vertices, size_t size);
	~VertexBuffer() = default;
};

}