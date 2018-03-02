// Author: Dante Nardo
// Last Modified: 3/1/2018
// Purpose: Performs collision checking operations based on collider types.

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

	bool OBB(entity& a, entity& b); // Oriented Bounding Box
	bool SAT(entity& a, entity& b); // Separating Axis Theorem
};

#endif // !COLLISIONS_H