// Dante Nardo
// Last Modified: 3/8/2018
// Purpose: Defines constants and implements important universal functions.

#ifndef MATH_H
#define MATH_H

#include <SFML\Graphics.hpp>
#include <math.h>
#include <algorithm>
#include <vector>

/*
================================================================================
All type definitions used in the Fiziks Engine.
================================================================================
*/
typedef sf::Vector2f v2f;
typedef sf::Vector3f v3f;
typedef std::vector<v2f> v2fs;
typedef std::vector<v3f> v3fs;

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

// TODO: Don't hardcode this
inline v2f world_to_screen(const v2f& position)
{
	return v2f(position.x, 768 - position.y);
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

inline float cross(const v2f& a, const v2f& b)
{
	return a.x * b.y - a.y * b.x;
}

inline v2f cross(const v2f& a, float s)
{
	return v2f(s * a.y, -s * a.x);
}

inline v2f cross(float s, const v2f& a)
{
	return v2f(-s * a.y, s * a.x);
}

inline float pythag(float a, float b)
{
	// Pythagorean theorem: A^2 + B^2 = C^2
	return sqrt(pow(a, 2) + pow(b, 2));
}

inline sf::FloatRect* top_left(const sf::FloatRect& rect)
{
	return new sf::FloatRect(rect.left,
							 rect.top,
							 rect.width/2,
							 rect.height/2);
}

inline sf::FloatRect* top_right(const sf::FloatRect& rect)
{
	return new sf::FloatRect(rect.left + rect.width/2,
							 rect.top,
							 rect.width/2,
							 rect.height/2);
}

inline sf::FloatRect* bottom_left(const sf::FloatRect& rect)
{
	return new sf::FloatRect(rect.left,
							 rect.top + rect.height/2,
							 rect.width/2,
							 rect.height/2);
}

inline sf::FloatRect* bottom_right(const sf::FloatRect& rect)
{
	return new sf::FloatRect(rect.left + rect.width/2,
							 rect.top + rect.height/2,
							 rect.width/2,
							 rect.height/2);
}

#endif // !MATH_H