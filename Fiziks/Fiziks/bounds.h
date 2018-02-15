// Author: Dante Nardo
// Last Modified: 2/13/2018
// Purpose: Represents any rectangle with an x, y, width, and height.

#pragma once
#include "math.h"

class aa_bounds
{
public:
	aa_bounds();
	aa_bounds(v2f min, v2f max);
	~aa_bounds();

	bool contains(aa_bounds* bound);
	aa_bounds top_left();
	aa_bounds top_right();
	aa_bounds bottom_left();
	aa_bounds bottom_right();

	v2f get_min();
	v2f get_max();
	v2f get_pos();
	float get_width();
	float get_height();
	
private:
	v2f m_min;
	v2f m_max;
};

class oo_bounds : aa_bounds
{

};