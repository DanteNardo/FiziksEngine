#include "quad_node.h"

quad_node::quad_node()
{
	m_bounds = new bounds(v2f(0, 0), 640, 480);
    m_subdivisions = new std::vector<quad_node*>();
    m_observers = new std::vector<observer*>();
}

quad_node::quad_node(bounds* bound)
{
    m_bounds = bound;
    m_subdivisions = new std::vector<quad_node*>();
    m_observers = new std::vector<observer*>();
}

quad_node::quad_node(bounds* bound, int depth)
{
    m_depth = depth;
    m_bounds = bound;
    m_subdivisions = new std::vector<quad_node*>();
    m_observers = new std::vector<observer*>();
}

quad_node::~quad_node()
{
    delete m_bounds;
    delete m_subdivisions;
    delete m_observers;
}

void quad_node::set_final_depth(int final_depth)
{
    m_final_depth = final_depth;
}

/*
This function creates the entire quad tree.
After adding all of the observers, the quad tree partitions itself and continues
to subdivide until each quad_node has no more than MAX_OBSERVERS inside it.
*/
void quad_node::add_observers(std::vector<observer*>* observers)
{
    for (auto o : *observers) {
        m_observers->push_back(o);
    }
    partition();
}

void quad_node::add_observer(observer* observe)
{
    m_observers->push_back(observe);
}

bounds* quad_node::get_bounds()
{
    return m_bounds;
}

void quad_node::partition()
{
    if (m_depth < m_final_depth) {
        
        // Distribute observers among four new quads
        create_subdivisions();
        for (int i = 0; i < m_observers->size(); i++) {

            // Move observers to children and remove from parent
            if (add_to_subdivision((*m_observers)[i])) {
                m_observers->erase(m_observers->begin()+i);
                i--;
            }
        }
    }
}

/*
Adds four children to the current quad node and subdivides the bounds of the
parent node so that 
*/
void quad_node::create_subdivisions()
{
    // Split partition into four quads
    quad_node* q1 = new quad_node(&m_bounds->top_left());
    quad_node* q2 = new quad_node(&m_bounds->top_right());
    quad_node* q3 = new quad_node(&m_bounds->bottom_left());
    quad_node* q4 = new quad_node(&m_bounds->bottom_right());

    // Create branches
    m_subdivisions->push_back(q1);
    m_subdivisions->push_back(q2);
    m_subdivisions->push_back(q3);
    m_subdivisions->push_back(q4);
}

bool quad_node::add_to_subdivision(observer* observer_to_add)
{
    for (auto q : *m_subdivisions) {
        if (q->get_bounds()->contains(observer_to_add->get_bounds())) {
            q->add_observer(observer_to_add);
            return true;
        }
    }

	return false;
}