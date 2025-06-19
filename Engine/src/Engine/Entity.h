#pragma once
#include "Vector.h"
#include <SDL.h>
#include "Core.h"

class API Entity {
protected:
	Vector2D<float> m_position;
	Vector2D<float> m_size;

public:
	
	Entity(const Vector2D<float>& _pos = {0.0f, 0.0f}, const Vector2D<float>& _size = {0.0f, 0.0f}) 
		: m_position(_pos), m_size(_size) {
		
	}

	virtual ~Entity() {}

	virtual void render(SDL_Renderer* renderer) {}
	virtual void update(const float& deltaTime) {}
	virtual void handleInput(const float& deltaTime) {}

	inline Vector2D<float> getPosition() const { 
		return m_position;
	}
	inline Vector2D<float> getSize() const { 
		return m_size; 
	}
	inline void setPosition(const Vector2D<float>& _position) { 
		m_position = _position; 
	}
	inline void setPosition(const float _x, const float _y) { 
		m_position.x = _x;
		m_position.y = _y;
	}
		

};