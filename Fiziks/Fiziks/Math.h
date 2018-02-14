// Dante Nardo
// Last Modified: 2/13/2018
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

#endif // !MATH_H