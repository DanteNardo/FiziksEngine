// Author: Dante Nardo
// Last Modified: 3/6/2018
// Purpose: Implements spatial partitioning of a 2D screen.

#ifndef QUAD_NODE_H
#define QUAD_NODE_H

#include "collisions.h"

class quad_node
{
public:
	quad_node(sf::RenderWindow* window);
	quad_node(sf::FloatRect* rect);
	quad_node(sf::FloatRect* rect, int depth);
	~quad_node();

	sf::FloatRect* get_rect();
	void set_final_depth(int final_depth);
	void add_entities(std::vector<entity*>* entities);
	void add_entity(entity* e);
	void clear_entities();
	void check_collisions(std::vector<entity*> a, std::vector<entity*> b);
	void check_subdivision_collisions();
	std::vector<entity*>* get_lower();
	std::vector<entity*>* get_lower(std::vector<entity*>* previous);
	void draw_tree(sf::RenderWindow* window);

private:
	int m_depth;
	static int m_final_depth;
	sf::FloatRect* m_rect;

	std::vector<quad_node*>* m_subdivisions;
	std::vector<entity*>* m_entities;

	void partition();
	void create_subdivisions();
	bool add_to_subdivision(entity* observer_to_add);
	bool not_leaf();
};

#endif // !QUAD_NODE_H