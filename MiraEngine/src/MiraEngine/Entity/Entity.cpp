#include <MiraPreCompHeader.h>
#include "Entity.h"
#include <MiraEngine/Scene/Scene.h>

namespace Mira {

Entity::Entity(Scene* _scene, uint32_t _entityId)
	: p_scene(_scene), m_entityId(_entityId) {

}

} // namespace ends