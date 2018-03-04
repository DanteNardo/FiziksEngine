// Author: Dante Nardo
// Last Modified: 3/3/2018
// Purpose: Performs collision checking operations based on collider types.

// Source: https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "entity.h"

// Stores collision data between two objects.
struct manifold
{
	entity* a;
	entity* b;
	float pen;
	v2f norm;
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
	bool c_rr(entity& a, entity& b); // Rectangle-Rectangle Check
	bool c_rc(entity& a, entity& b); // Rectangle-Circle Check
	bool c_rt(entity& a, entity& b); // Rectangle-Triangle Check
	bool c_cr(entity& a, entity& b); // Circle-Rectangle Check
	bool c_cc(entity& a, entity& b); // Circle-Circle Check
	bool c_ct(entity& a, entity& b); // Circle-Triangle Check
	bool c_tr(entity& a, entity& b); // Triangle-Rectangle Check
	bool c_tc(entity& a, entity& b); // Triangle-Circle Check
	bool c_tt(entity& a, entity& b); // Triangle-Triangle Check

	// Collision resolution
	manifold gen_manifold(entity& a, entity& b);
	float tot_mass(entity& a, entity& b);
	float pen(entity& a, entity& b);
	void resolve(const manifold& m);
	void fix_pen(const manifold& m);

	/*
	2D SHAPE CHECK JUMP TABLE:
	The purpose of this Jump Table is to pass two entities into it and call the
	correct collision checking function based off of the type of a and b. This
	works well with the polymorphic functionality of the circle, rectangle, and
	triangle classes. Uses function pointers.
	// Jump Tables: https://barrgroup.com/Embedded-Systems/How-To/C-Function-Pointers
	*/
	bool(collisions::*shape_check[3][3])(entity&, entity&) = {
		{ &collisions::c_rr, &collisions::c_rc, &collisions::c_rt },
		{ &collisions::c_cr, &collisions::c_cc, &collisions::c_ct },
		{ &collisions::c_tr, &collisions::c_tc, &collisions::c_tt }
	};
};

#endif // !COLLISIONS_H