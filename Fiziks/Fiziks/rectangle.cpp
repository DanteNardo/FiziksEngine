#include "rectangle.h"

rectangle::rectangle(fiziks_engine* fiziks, integration i, v2f size) :
entity(fiziks)
{
	m_shape = new sf::RectangleShape(size);
	m_shape->setPosition(v2f(0, 0));
	m_shape->setFillColor(sf::Color::Green);
	//m_rb = new rigidbody(v2f(0, 0), v2f(150, 150), v2f(0, GRAVITY), 45);
	//m_kinematics = new kinematics(i, m_rb);
	m_type = Rect;
}

rectangle::~rectangle()
{
	safe_delete(m_shape);
	safe_delete(m_rb);
	safe_delete(m_kinematics);
}

void rectangle::update()
{
	m_kinematics->update(get_engine()->get_delta_time(), 
						 get_engine()->get_time());
	m_shape->setPosition(get_engine()->world_to_screen(
						 m_kinematics->get_rigidbody()->p()));
}

void rectangle::draw(sf::RenderWindow * window)
{
	window->draw(*m_shape);
}

sf::RectangleShape* rectangle::get_shape()
{
	return m_shape;
}

v2f rectangle::get_pos()
{
	return m_kinematics->get_rigidbody()->p();
}