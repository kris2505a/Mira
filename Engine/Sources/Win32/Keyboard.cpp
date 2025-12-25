#include <PreCompHeader.hpp>
#include "Keyboard.hpp"

namespace Mira {

std::bitset <256> Keyboard::m_keys;
std::bitset <256> Keyboard::m_prevState;

void Keyboard::keyPressed(WPARAM key) {
	if (key < 256) {
		m_keys.set(static_cast<size_t>(key), true);
		m_prevState.set(static_cast <size_t>(key), true);
	}
}

void Keyboard::endState() {
	m_prevState = m_keys;
}

void Keyboard::clearState() {
	m_keys.reset();
}

void Keyboard::keyReleased(WPARAM key) {
	if (key < 256) {
		m_keys.set(static_cast<size_t>(key), false);
		m_prevState.set(static_cast <size_t>(key), false);
	}
}

}