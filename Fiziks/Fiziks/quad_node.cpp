#include "quad_node.h"

quad_node::quad_node()
{
    m_width = 640;
    m_height = 480;
    m_subdivisions = new std::vector<quad_node*>();
    m_observers = new std::vector<observer*>();
}

quad_node::quad_node(int width, int height)
{
    m_width = width;
    m_height = height;
    m_subdivisions = new std::vector<quad_node*>();
    m_observers = new std::vector<observer*>();
}

quad_node::~quad_node()
{
    delete m_subdivisions;
    delete m_observers;
}

/*
This function creates the entire quad tree.
After adding all of the observers, the quad tree partitions itself and continues
to subdivide until each quad_node has no more than MAX_OBSERVERS inside it.
*/
void quad_node::add_observers(std::vector<observer*>* observers)
{
    for (auto o : observers) {
        m_observers->push_back(o);
    }
    partition();
}

void quad_node::partition()
{
    if (m_observers->size() > MAX_OBSERVERS) {
        
        // Distribute observers among four new quads
        create_subdivisions();
        for (auto o : m_observers) {
            add_to_subdivision(o);
        }
    }
}

void quad_node::create_subdivisions()
{
    // Split partition into four quads
    quad_node* q1 = new quad_node(m_width/2, m_height/2);
    quad_node* q2 = new quad_node(m_width/2 + m_width, m_height/2);
    quad_node* q3 = new quad_node(m_width/2, m_height/2 + m_height);
    quad_node* q4 = new quad_node(m_width/2 + m_width, m_height/2 + m_height);

    // Create branches
    m_subdivisions->push_back(q1);
    m_subdivisions->push_back(q2);
    m_subdivisions->push_back(q3);
    m_subdivisions->push_back(q4);
}

void quad_node::add_to_subdivision(observer* observer_to_add)
{
    
}