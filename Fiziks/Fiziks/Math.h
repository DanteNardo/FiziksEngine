// Dante Nardo
// Last Modified: 2/28/2018
// Purpose: Defines constants and implements important universal functions.

#ifndef MATH_H
#define MATH_H

#include <SFML\Graphics.hpp>
#include <math.h>
#include <algorithm>

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

inline float rad(const float theta)
{
	return theta * PI / 180;
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

inline sf::FloatRect top_left(const sf::FloatRect& rect)
{
	return sf::FloatRect(rect.left,
						 rect.top,
						 rect.width/2,
						 rect.height/2);
}

inline sf::FloatRect top_right(const sf::FloatRect& rect)
{
	return sf::FloatRect(rect.left + rect.width/2,
						 rect.top,
						 rect.width/2,
						 rect.height/2);
}

inline sf::FloatRect bottom_left(const sf::FloatRect& rect)
{
	return sf::FloatRect(rect.left,
						 rect.top + rect.height/2,
						 rect.width/2,
						 rect.height/2);
}

inline sf::FloatRect bottom_right(const sf::FloatRect& rect)
{
	return sf::FloatRect(rect.left + rect.width/2,
						 rect.top + rect.height/2,
						 rect.width/2,
						 rect.height/2);
}

#endif // !MATH_H