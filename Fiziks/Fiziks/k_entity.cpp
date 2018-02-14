#include "k_entity.h"

k_entity::k_entity(fiziks_engine* fiziks, integration integration) :
Iobserver(fiziks)
{
	m_shape = new sf::RectangleShape();
	m_shape->setSize(v2f(25.0f, 25.0f));
	m_shape->setPosition(v2f(0, 0));
	m_shape->setFillColor(sf::Color::Red);
	m_shape->setOutlineColor(sf::Color::Green);
	m_shape->setOutlineThickness(2);
	k_point* point = new k_point(v2f(), v2f(100, 100), v2f(0, GRAVITY), 45);
	m_kinematics = new kinematics(integration, point);
}

k_entity::~k_entity()
{
	safe_delete(m_bounds);
	safe_delete(m_shape);
	safe_delete(m_kinematics);
}

void k_entity::update()
{
	m_kinematics->update(&get_engine()->get_delta_time(), 
						 &get_engine()->get_time());
	m_shape->setPosition(get_engine()->world_to_screen(
						 m_kinematics->get_k_point()->m_pos));
}

void k_entity::draw(sf::RenderWindow* window)
{
	window->draw(*m_shape);
}

v2f k_entity::get_pos()
{
	return m_kinematics->get_k_point()->m_pos;
}