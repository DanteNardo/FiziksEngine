#include "quad_node.h"

quad_node::quad_node()
{
	m_bounds = new aa_bounds(v2f(0, 0), 640, 480);
    m_subdivisions = new std::vector<quad_node*>();
    m_observers = new std::vector<Iobserver*>();

    partition();
}

quad_node::quad_node(aa_bounds* bound)
{
    m_depth = 0;
    m_bounds = bound;
    m_subdivisions = new std::vector<quad_node*>();
    m_observers = new std::vector<Iobserver*>();
}

quad_node::quad_node(aa_bounds* bound, int depth)
{
    m_depth = depth;
    m_bounds = bound;
    m_subdivisions = new std::vector<quad_node*>();
    m_observers = new std::vector<Iobserver*>();
}

quad_node::~quad_node()
{
    safe_delete(m_bounds);
    safe_delete(m_subdivisions);
    safe_delete(m_observers);
}

aa_bounds* quad_node::get_bounds()
{
    return m_bounds;
}

void quad_node::set_final_depth(int final_depth)
{
    m_final_depth = final_depth;
    partition();
}

/*
Recursive function that distributes all observers among entire quad tree.
*/
void quad_node::add_observers(std::vector<Iobserver*>* observers)
{
    // Copy observers over to quad tree
    for (auto o : *observers) {
        m_observers->push_back(o);
    }

    // Move observers to children and remove from parent
    for (int i = 0; i < m_observers->size(); i++) {
        if (add_to_subdivision((*m_observers)[i])) {
            m_observers->erase(m_observers->begin()+i);
            i--;
        }
    }

    // Add observers from children to grandchildren
    if (m_depth + 1 <= m_final_depth) {
        for (auto q : *m_subdivisions) {
            q->add_observers(m_observers);
        }
    }
}

void quad_node::add_observer(Iobserver* observe)
{
    m_observers->push_back(observe);
}

/*
Recursive function that partitions subdivisions until final depth is reached.
Called when final depth is set for the quad tree. Partitions to a set depth
then adds observers to respective subdivisions.
*/
void quad_node::partition()
{
    if (m_depth < m_final_depth) {
        create_subdivisions();
        for (auto sub : *m_subdivisions) {
            sub->partition();
        }
    }
}

/*
Adds four children to the current quad node and subdivides the bounds of the
parent node by 4. Called an amount of times equal to m_final_depth^2.
*/
void quad_node::create_subdivisions()
{
    // Split partition into four quads
    quad_node* q1 = new quad_node(&m_bounds->top_left(), m_depth + 1);
    quad_node* q2 = new quad_node(&m_bounds->top_right(), m_depth + 1);
    quad_node* q3 = new quad_node(&m_bounds->bottom_left(), m_depth + 1);
    quad_node* q4 = new quad_node(&m_bounds->bottom_right(), m_depth + 1);

    // Create branches
    m_subdivisions->push_back(q1);
    m_subdivisions->push_back(q2);
    m_subdivisions->push_back(q3);
    m_subdivisions->push_back(q4);
}

/*
Determines which subdivision this observer should be added to, if it should be
added. Returns true if added to a subdivision, else false.
*/
bool quad_node::add_to_subdivision(Iobserver* observer_to_add)
{
    for (auto q : *m_subdivisions) {
        if (q->get_bounds()->contains(observer_to_add->get_bounds())) {
            q->add_observer(observer_to_add);
            return true;
        }
    }

	return false;
}

void check_collisions(std::vector<Iobserver*> A, std::vector<Iobserver*> B)
{
    // Iterate through two vectors that contain the collision objects
    for (auto a : A) {
        for (auto b : B) {
            m_collisions->check(a, b);
        }
    }
}

void quad_node::check_subdivision_collisions()
{
    // There are observers in this node so we have to check their collisions
    // with all possible lower observers.
    if (m_observers->size() > 0) {
        std::vector<Iobserver*>* lowers = get_lower();
        check_collisions(*m_observers, *lowers);
        safe_delete(lowers);
    }

    // Check collisions in all subdivisions
    for (auto q : *m_subdivisions) {
        q->check_subdivision_collisions();
    }
}

/*
Initializes the vector of all lower observers from this quad_node. Calls an
overloaded version of itself that sends all of the data back to this function.
*/
std::vector<Iobserver*>* quad_node::get_lower()
{
    // Initializes the vector pointer to store all lower observers
    std::vector<Iobserver*>* lows = new std::vector<Iobserver*>();
    
    // Call overloaded get_lower(...) recursively
    for (auto s : *m_subdivisions) {
        s->get_lower(lows);
    }

    // Return vector filled with all lower observers
    return lows;
}

/*
Recursive function that 
*/
std::vector<Iobserver*>* quad_node::get_lower(std::vector<Iobserver*>* previous)
{
    // Push all observers into lowers list if there are observers at this level
    for (auto o : *m_observers) {
        previous->push_back(o);
    }

    // Call overloaded get_lower(...) recursively if there are more subdivisions
    for (auto s : *m_subdivisions) {
        s->get_lower(previous);
    }

    // Send vector back up call stack to the top
    return previous;
}

bool quad_node::not_leaf()
{
    return m_depth != m_final_depth;
}