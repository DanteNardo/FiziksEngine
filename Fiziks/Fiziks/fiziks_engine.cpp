#include "fiziks_engine.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

fiziks_engine::fiziks_engine()
{
	m_views = std::vector<Iobserver*>();
	m_timer = new sf::Clock();
	m_delta_timer = new sf::Clock();

	// TODO: No longer hardcode this
	circle* c = new circle(this, ExplicitEuler, 5, 21);
	rectangle* r = new rectangle(this, ExplicitEuler, v2f(5, 5));
	triangle* t = new triangle(this, ExplicitEuler, 5, 5);
}

fiziks_engine::~fiziks_engine()
{
	for (int i = 0; i < m_views.size(); i++) {
		safe_delete(m_views[i]);
	}

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
}

void fiziks_engine::draw(sf::RenderWindow* window)
{
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

// TODO: Implement this correctly
v2f fiziks_engine::world_to_screen(const v2f& position)
{
	return v2f(position.x, 768 - position.y);
}