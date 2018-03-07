// Author: Dante Nardo
// Last Modified: 3/7/2018
// Purpose: Performs collision checking operations based on collider types.

// Source: https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "entity.h"

// Stores collision data between two objects.
struct manifold
{
	entity* m_a;
	entity* m_b;
	float m_pen;
	v2f m_norm;

	manifold(entity* a, entity* b, float pen, v2f norm)
	{
		m_a = a;
		m_b = b;
		m_pen = pen;
		m_norm = norm;
	}
};

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
	bool ARBB(entity& a, entity& b); // Axis Realigned Bounding Box
	bool SAT(entity& a, entity& b);  // Separating Axis Theorem

	// Collision resolution
	float t_m(entity& a, entity& b);			 // Total mass
	manifold gen_manifold(entity& a, entity& b); // Creates collision struct
	v2f closest(entity& a, entity& b);			 // Finds the closest point
	v2f norm(entity& a, entity& b);  			 // Finds the collision normal
	float pen(v2f norm);						 // Finds the penetration
	void resolve(const manifold& m);			 // Resolves collisions
	void fix_pen(const manifold& m);			 // Fixes object penetration
};

#endif // !COLLISIONS_H