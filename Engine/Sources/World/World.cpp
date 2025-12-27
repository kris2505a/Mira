#include <PreCompHeader.hpp>
#include "World.hpp"
#include "Renderer/Renderer.hpp"

namespace Mira {

World::World() {

}

void World::init() {

}

void World::shutdown() {

}

void World::spark() {
	for (size_t ind = 0; ind < m_entities.size(); ind++) {
		m_entities[ind]->spark();
	}
}

void World::render(Renderer* renderer) {
	for (size_t ind = 0; ind < m_entities.size(); ind++) {
		m_entities[ind]->render(renderer);
	}
}

void World::pulse(float deltaTime) {
	for (size_t ind = 0; ind < m_entities.size(); ind++) {
		m_entities[ind]->pulse(deltaTime);
	}
}

World::~World() {
	for (size_t ind = 0; ind < m_entities.size(); ind++) {
		delete m_entities[ind];
	}
	m_entities.clear();
}

}