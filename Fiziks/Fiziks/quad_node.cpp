#include "quad_node.h"

// Declare static depth
int quad_node::m_final_depth;

// Only called on Root quad_node
quad_node::quad_node(sf::RenderWindow* window)
{
	m_rect = new sf::FloatRect(v2f(0, 0), (v2f)window->getSize());
    m_subdivisions = new std::vector<quad_node*>();
    m_entities = new std::vector<entity*>();
    partition();
}

quad_node::quad_node(sf::FloatRect* rect)
{
    m_depth = 0;
    m_rect = rect;
    m_subdivisions = new std::vector<quad_node*>();
    m_entities = new std::vector<entity*>();
}

quad_node::quad_node(sf::FloatRect* rect, int depth)
{
    m_depth = depth;
    m_rect = rect;
    m_subdivisions = new std::vector<quad_node*>();
    m_entities = new std::vector<entity*>();
}

quad_node::~quad_node()
{
    safe_delete(m_rect);
    safe_delete(m_subdivisions);
    safe_delete(m_entities);
}

sf::FloatRect* quad_node::get_rect()
{
    return m_rect;
}

void quad_node::set_final_depth(int final_depth)
{
    m_final_depth = final_depth;
    partition();
}

/*
Recursive function that distributes all observers among entire quad tree.
*/
void quad_node::add_entities(std::vector<entity*>* entities)
{
    // Copy observers over to quad tree
    for (auto e : *entities) {
        add_entity(e);
    }

    // Move observers to children and remove from parent
    for (int i = 0; i < m_entities->size(); i++) {
        if (add_to_subdivision((*m_entities)[i])) {
            m_entities->erase(m_entities->begin()+i);
            i--;
        }
    }

    // Add observers from children to grandchildren
    if (m_depth + 1 <= m_final_depth) {
        for (auto q : *m_subdivisions) {
            q->add_entities(m_entities);
        }
    }
}

void quad_node::add_entity(entity* e)
{
    m_entities->push_back(e);
}

void quad_node::clear_entities()
{
    m_entities->clear();
    for (auto s : *m_subdivisions) {
        s->clear_entities();
    }
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
Adds four children to the current Xquad node and subdivides the bounds of the
parent node by 4. Called an amount of times equal to m_final_depth^2.
*/
void quad_node::create_subdivisions()
{
    // Split partition into four quads
    quad_node* q1 = new quad_node(top_left(*m_rect), m_depth + 1);
    quad_node* q2 = new quad_node(top_right(*m_rect), m_depth + 1);
    quad_node* q3 = new quad_node(bottom_left(*m_rect), m_depth + 1);
    quad_node* q4 = new quad_node(bottom_right(*m_rect), m_depth + 1);

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
bool quad_node::add_to_subdivision(entity* entity_to_add)
{
    for (auto q : *m_subdivisions) {
        if (q->get_rect()->intersects(entity_to_add->bounds())) {
            q->add_entity(entity_to_add);
            return true;
        }
    }

	return false;
}

/*
Checks collisions with two lists of entities and perform physics response.
*/
void quad_node::check_collisions(std::vector<entity*> A, std::vector<entity*> B)
{
    for (auto a : A) {
        for (auto b : B) {
            if (a != b) {
                collisions::get_instance()->check(*a, *b);
            }
        }
    }
}

void quad_node::check_subdivision_collisions()
{
    // There are observers in this node so we have to check their collisions
    // with all possible lower observers.
    if (m_entities->size() > 0) {
        std::vector<entity*>* lowers = get_lower();
        if (lowers->size() > 0) {
            check_collisions(*m_entities, *lowers);
        }
        check_collisions(*m_entities, *m_entities);
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
std::vector<entity*>* quad_node::get_lower()
{
    // Initializes the vector pointer to store all lower observers
    std::vector<entity*>* lows = new std::vector<entity*>();
    
    // Call overloaded get_lower(...) recursively
    for (auto s : *m_subdivisions) {
        s->get_lower(lows);
    }

    // Return vector filled with all lower observers
    return lows;
}

/*
Recursive function that gets all of the entities in the lower branches.
*/
std::vector<entity*>* quad_node::get_lower(std::vector<entity*>* previous)
{
    // Push all observers into lowers list if there are observers at this level
    for (auto o : *m_entities) {
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

void quad_node::draw_tree(sf::RenderWindow* window)
{
    sf::RectangleShape r = sf::RectangleShape(v2f(m_rect->width, m_rect->height));
	v2f pos = v2f(m_rect->left, m_rect->top);
    r.setPosition(pos.x, pos.y);
	if (m_entities->size() > 0) {
		r.setOutlineColor(sf::Color::White);
	}
	else {
		r.setOutlineColor(sf::Color::Transparent);
	}
    r.setOutlineThickness(1);
    r.setFillColor(sf::Color::Transparent);
    window->draw(r);

    for (auto s : *m_subdivisions) {
        s->draw_tree(window);
    }
}