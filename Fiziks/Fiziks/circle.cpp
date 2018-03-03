#include "circle.h"

circle::circle(fiziks_engine* fiziks, integration i, float radius, float size) :
entity(fiziks)
{
	m_shape = new sf::CircleShape(radius, size);
	m_shape->setPosition(v2f(200, 200));
	m_shape->setFillColor(sf::Color::Green);
	m_rb = new rigidbody(v2f(0, 0), v2f(150, 150), v2f(0, GRAVITY), 45);
	m_kinematics = new kinematics(i, m_rb);
}

circle::~circle()
{
	safe_delete(m_shape);
	safe_delete(m_rb);
	safe_delete(m_kinematics);
}

void circle::update()
{
	m_kinematics->update(get_engine()->get_delta_time(), 
						 get_engine()->get_time());
	m_shape->setPosition(get_engine()->world_to_screen(
						 m_kinematics->get_rigidbody()->p()));
}

void circle::draw(sf::RenderWindow * window)
{
	window->draw(*m_shape);
}

sf::CircleShape* circle::get_shape()
{
	return m_shape;
}

v2f circle::get_pos()
{
	return m_kinematics->get_rigidbody()->p();
}