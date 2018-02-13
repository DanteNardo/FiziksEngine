// Author: Dante Nardo
// Last Modified: 2/13/2018
// Purpose: Represents any rectangle with an x, y, width, and height.

#pragma once
class bounds
{
public:
	bounds();
	~bounds();

	bool contains(bounds* bound);
	int get_x();
	int get_y();
	int get_width();
	int get_height();
	
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

