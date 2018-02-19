// Author: Dante Nardo
// Last Modified: 2/19/2018
// Purpose: Implements spatial partitioning of a 2D screen.

#ifndef QUAD_NODE_H
#define QUAD_NODE_H

#include "fiziks_engine.h"
#include "collisions.h"

class quad_node
{
public:
	quad_node();
	quad_node(sf::FloatRect* bound);
	quad_node(sf::FloatRect* bound, int depth);
	~quad_node();

	sf::FloatRect* get_rect();
	void set_final_depth(int final_depth);
	void add_observers(std::vector<entity*>* entities);
	void add_observer(entity* e);
	void check_collisions(std::vector<entity*> a, std::vector<entity*> b);
	void check_subdivision_collisions();
	std::vector<entity*>* get_lower();
	std::vector<entity*>* get_lower(std::vector<entity*>* previous);

private:
	int m_depth;
	static int m_final_depth;
	static collisions m_collisions;
	sf::FloatRect* m_rect;

	std::vector<quad_node*>* m_subdivisions;
	std::vector<entity*>* m_entities;

	void partition();
	void create_subdivisions();
	bool add_to_subdivision(entity* observer_to_add);
	bool not_leaf();
};

// Declare static variables
int quad_node::m_final_depth;
collisions quad_node::m_collisions;

#endif // !QUAD_NODE_H