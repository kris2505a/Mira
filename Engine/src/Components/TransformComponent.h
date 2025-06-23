#pragma once
#include <Core.h>
#include <Vector.h>
#include <cmath>

struct API TransformComponent {
	Vector2df position; //XY
	float rotation;		//Degree
	Vector2df scale;	//XY
	Vector2df rightVector;
	Vector2df upVector;

	TransformComponent(Vector2df _position = { 0.0f, 0.0f }, float _rotation = 0.0f, Vector2df _scale = { 1.0f, 1.0f }) 
		: position(_position), rotation(_rotation), scale(_scale) {
		rightVector = { std::cos(rotation), std::sin(rotation) };
		upVector = { -std::sin(rotation), std::cos(rotation) };
	}
};