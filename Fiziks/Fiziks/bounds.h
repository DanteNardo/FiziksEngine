// Author: Dante Nardo
// Last Modified: 2/13/2018
// Purpose: Represents any rectangle with an x, y, width, and height.

#pragma once
#include "math.h"

class bounds
{
public:
	bounds();
	bounds(v2f pos, int width, int height);
	~bounds();

	bool contains(bounds* bound);
	bounds top_left();
	bounds top_right();
	bounds bottom_left();
	bounds bottom_right();

	v2f get_pos();
	int get_width();
	int get_height();
	
private:
	v2f m_pos;
	int m_width;
	int m_height;
};