// Author: Dante Nardo
// Last Modified: 2/13/2018
// Purpose: Implements spatial partitioning of a 2D screen.

#ifndef QUAD_NODE_H
#define QUAD_NODE_H

#include <vector>
#include "fiziks_engine.h"

class quad_node
{
public:
	quad_node();
	quad_node(aa_bounds* bound);
	quad_node(aa_bounds* bound, int depth);
	~quad_node();

	aa_bounds* get_bounds();
	void set_final_depth(int final_depth);
	void add_observers(std::vector<Iobserver*>* observers);
	void add_observer(Iobserver* observe);
	void check_collisions(std::vector<Iobserver*> a, std::vector<Iobserver*> b);
	void check_subdivision_collisions();
	std::vector<Iobserver*>* get_lower();
	std::vector<Iobserver*>* get_lower(std::vector<Iobserver*>* previous);

private:
	int m_depth;
	static int m_final_depth;
	aa_bounds* m_bounds;

	std::vector<quad_node*>* m_subdivisions;
	std::vector<Iobserver*>* m_observers;

	void partition();
	void create_subdivisions();
	bool add_to_subdivision(Iobserver* observer_to_add);
	bool not_leaf();
};

int quad_node::m_final_depth;

#endif // !QUAD_NODE_H