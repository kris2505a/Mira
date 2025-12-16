#include "Keyboard.h"
#include <iostream>

namespace Mira {

std::bitset <256> Keyboard::m_keys;

void Keyboard::keyPressed(WPARAM key) {
	if (key < 256) {
		m_keys.set(static_cast<size_t>(key), true);
	}
}

void Keyboard::clearState() {
	m_keys.reset();
}

void Keyboard::keyReleased(WPARAM key) {
	if (key < 256) {
		m_keys.set(static_cast<size_t>(key), false);
	}
}

}