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
	
	circle* c1 = new circle(this, ExplicitEuler, 20);
	safe_delete(c1->rb());
	c1->rb(new rigidbody(v2f(250, 400), v2f(0, -50), v2f(0, 0), 45, 40, 40, Rock));

	//circle* c2 = new circle(this, ExplicitEuler, 20);
	//safe_delete(c2->rb());
	//c2->rb(new rigidbody(v2f(275, 100), v2f(-5, 200), v2f(0, 0), 45, 40, 40, Rock));

	circle* c3 = new circle(this, ExplicitEuler, 20);
	safe_delete(c3->rb());
	c3->rb(new rigidbody(v2f(400, 250), v2f(-50, 0), v2f(0, 0), 45, 40, 40, Rock));

	circle* c4 = new circle(this, ExplicitEuler, 20);
	safe_delete(c4->rb());
	c4->rb(new rigidbody(v2f(500, 50), v2f(-75, 75), v2f(0, 0), 45, 40, 40, Rock));

	rectangle* r1 = new rectangle(this, ExplicitEuler, v2f(40,40));
	safe_delete(r1->rb());
	r1->rb(new rigidbody(v2f(100, 300), v2f(100, 0), v2f(0, 0), 45, 40, 40, Rock));

	rectangle* r2 = new rectangle(this, ExplicitEuler, v2f(40, 40));
	safe_delete(r2->rb());
	r2->rb(new rigidbody(v2f(500, 300), v2f(-50, 0), v2f(0, 0), 45, 40, 40, Rock));

	rectangle* r3 = new rectangle(this, ExplicitEuler, v2f(40, 40));
	safe_delete(r3->rb());
	r3->rb(new rigidbody(v2f(400, 600), v2f(-50, -125), v2f(0, 0), 45, 40, 40, Rock));
	

	//triangle* t1 = new triangle(this, ExplicitEuler, 40, 40);
	//safe_delete(t1->rb());
	//t1->rb(new rigidbody(v2f(450, 500), v2f(-25, -50), v2f(0, 0), 45, 40, 40, Rock));

	//triangle* t2 = new triangle(this, ExplicitEuler, 40, 40);
	//safe_delete(t2->rb());
	//t2->rb(new rigidbody(v2f(300, 250), v2f(25, 25), v2f(0, 0), 45, 40, 40, Rock));

	//triangle* t3 = new triangle(this, ExplicitEuler, 40, 40);
	//safe_delete(t3->rb());
	//t3->rb(new rigidbody(v2f(750, 750), v2f(-25, -25), v2f(0, 0), 45, 40, 40, Rock));

	//triangle* t4 = new triangle(this, ExplicitEuler, 40, 40);
	//safe_delete(t4->rb());
	//t4->rb(new rigidbody(v2f(600, 650), v2f(25, 25), v2f(0, 0), 45, 40, 40, Rock));

	// TODO: FIX THIS STATIC CAST
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
	// TODO: FIX THIS STATIC CAST
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