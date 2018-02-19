// Dante Nardo
// Last Modified: 2/19/2018
// Purpose: Defines constants and implements important universal functions.

#ifndef MATH_H
#define MATH_H

#include <SFML\Graphics.hpp>
#include <math.h>

/*
================================================================================
All type definitions used in the Fiziks Engine.
================================================================================
*/
typedef sf::Vector2f v2f;
typedef sf::Vector3f v3f;

/*
================================================================================
Physics-based constants 
================================================================================
*/
#define PI 3.14159265
#define GRAVITY -9.81

/*
================================================================================
All function definitions that are necessary for the entire Fiziks Engine.
================================================================================
*/
inline void safe_delete(void* pointer)
{
	delete pointer;
	pointer = nullptr;
}

inline v2f normalize(const v2f& v)
{
	float length = sqrtf((pow(v.x, 2) + pow(v.y, 2)));
	if (length != 0) {
		return v2f(v.x / length, v.y / length);
	}
	return v;
}

inline v3f normalize(const v3f& v)
{
	float length = sqrtf((pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
	if (length != 0) {
		return v3f(v.x / length, v.y / length, v.z / length);
	}
	return v;
}

inline float dot(const v2f& v1, const v2f& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

inline float dot(const v3f& v1, const v3f& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

#endif // !MATH_H