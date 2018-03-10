// Author: Dante Nardo
// Last Modified: 3/10/2018
// Purpose: Performs collision checking operations based on collider types.

// Source: https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "entity.h"

// Enumerator for SAT collision checking results
enum SAT_RESULT 
{
	SAT_A, SAT_B, SAT_NONE
};

// Stores collision data between two objects.
struct manifold
{
	entity* m_a;
	entity* m_b;
	float m_pen;
	v2f m_norm;

	manifold() 
	{
		m_a = nullptr;
		m_b = nullptr;
		m_pen = 0.0f;
		m_norm = v2f(0, 0);
	}

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
	v2fs gen_norms(const v2fs& points); 	// Get an entity's normals
	v2f projection(v2fs& points, v2f axis); // Get an entity's projection
	bool ARBB(entity& a, entity& b); 		// Axis Realigned Bounding Box
	bool SAT(entity& a, entity& b,			// Separating Axis Theorem
			 v2f& an, v2f& bn); 

	// Collision resolution
	manifold gen_manifold(entity& a, 
						  entity& b, v2f n);	 // Creates collision struct
	float t_m(entity& a, entity& b);			 // Total mass
	v2f closest(entity& a, entity& b);			 // Finds the closest point
	v2f norm(entity& a, entity& b);  			 // Finds the collision normal
	float pen(v2f norm);						 // Finds the penetration
	void resolve(const manifold& m);			 // Resolves collisions
	void fix_pen(const manifold& m);			 // Fixes object penetration
};

#endif // !COLLISIONS_H