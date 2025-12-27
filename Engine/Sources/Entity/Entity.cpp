#include <PreCompHeader.hpp>
#include "Entity.hpp"

namespace Mira {

Entity::Entity() {

}

Entity::~Entity() {

}


uint32_t Entity::id() const {
	return m_id;
}

}