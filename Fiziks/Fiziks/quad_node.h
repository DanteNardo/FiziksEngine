// Author: Dante Nardo
// Last Modified: 2/13/2018
// Purpose: Implements spatial partitioning of a 2D screen.

#pragma once
#include <vector>
#include "observer.h"

class quad_node
{
public:
	quad_node();
	quad_node(int screen_width, int screen_height);
	~quad_node();

	int MAX_OBSERVERS = 3;

	void add_observers(std::vector<observer*>* observers);

private:
	int m_width;
	int m_height;

	std::vector<quad_node*>* m_subdivisions;
	std::vector<observer*>* m_observers;

	void partition();
	void create_subdivisions();
	void add_to_subdivision(observer* observer_to_add);
};

