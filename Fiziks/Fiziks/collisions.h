// Author: Dante Nardo
// Last Modified: 3/3/2018
// Purpose: Performs collision checking operations based on collider types.

// Source: https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "entity.h"

class collisions
{
public:
	collisions();
	~collisions();
	static collisions* get_instance();

	bool check(entity& a, entity& b);

private:
	static collisions* s_instance;

	// Collision checking
	bool OBB(entity& a, entity& b); // Oriented Bounding Box
	bool SAT(entity& a, entity& b); // Separating Axis Theorem

	// Collision resolution
	void resolve(entity& a, entity& b);
	void fix_penetration(entity& a, entity& b);
};

#endif // !COLLISIONS_H