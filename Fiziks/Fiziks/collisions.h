// Author: Dante Nardo
// Last Modified: 2/13/2018
// Purpose: Performs collision checking operations based on collider types.

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "bounds.h"

class collisions
{
public:
	collisions();
	~collisions();

	template <typename T1, typename T2>
	void check(const T1& a, const T2& b);
};

#endif // !COLLISIONS_H