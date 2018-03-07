#include "fiziks_engine.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

fiziks_engine::fiziks_engine(sf::RenderWindow* window)
{
	m_q_root = new quad_node(window);
	m_q_root->set_final_depth(2);
	m_views = std::vector<Iobserver*>();
	m_timer = new sf::Clock();
	m_delta_timer = new sf::Clock();

	// TODO: No longer hardcode this
	circle* c = new circle(this, ExplicitEuler, 20);
	rectangle* r = new rectangle(this, ExplicitEuler, v2f(50, 50));
	//triangle* t = new triangle(this, ExplicitEuler, 20, 20);

	std::vector<entity*> es = std::vector<entity*>();
	for (auto o : m_views) {
		es.push_back(static_cast<entity*>(o));
	}
	m_q_root->add_entities(&es);
}

fiziks_engine::~fiziks_engine()
{
	for (int i = 0; i < m_views.size(); i++) {
		safe_delete(m_views[i]);
	}

	safe_delete(m_q_root);
	safe_delete(m_timer);
	safe_delete(m_delta_timer);
}

void fiziks_engine::update()
{
	// Save the delta time every frame
	m_delta_time = m_delta_timer->restart().asSeconds();

	for (auto o : m_views) {
		o->update();
	}

	// Update quadtree
	m_q_root->clear_entities();
	std::vector<entity*> es = std::vector<entity*>();
	for (auto o : m_views) {
		es.push_back(static_cast<entity*>(o));
	}
	m_q_root->add_entities(&es);
	m_q_root->check_subdivision_collisions();
}

void fiziks_engine::draw(sf::RenderWindow* window)
{
	m_q_root->draw_tree(window);

	for (auto o : m_views) {
		o->draw(window);
	}
}

void fiziks_engine::attach(Iobserver* view)
{
	m_views.push_back(view);
}

void fiziks_engine::notify()
{
	for (auto view : m_views) {
		view->update();
	}
}

float fiziks_engine::get_time()
{
	return m_timer->getElapsedTime().asSeconds();
}

float fiziks_engine::get_delta_time()
{
	return m_delta_time;
}