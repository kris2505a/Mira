#pragma once
#include "Core.h"

template <typename Type>
struct API Vector2D {
	
	//Coordinates
	Type x, y;
	
	//Constructor
	Vector2D() : x(0), y(0) {}
	Vector2D(Type _x, Type _y) : x(_x), y(_x) {}

	Vector2D<Type> operator+(const Vector2D<Type>& other) const {
		return Vector2D<Type>(x + other.x, y + other.y);
	}

	Vector2D<Type> operator-(const Vector2D<Type>& other) const {
		return Vector2D<Type>(x - other.x, y - other.y);
	}

	Vector2D<Type> operator*(const Vector2D<Type>& other) const {
		return Vector2D<Type>(x * other.x, y * other.y);
	}

	Vector2D<Type> operator/(const Vector2D<Type>& other) const {
		return Vector2D<Type>(x / other.x, y / other.y);
	}

	Type dot(const Vector2D<Type>& other) const {
		return (Type)((x * other.x) + (y * other.y));
	}

};