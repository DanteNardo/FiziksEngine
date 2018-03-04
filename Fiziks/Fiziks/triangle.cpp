#include "triangle.h"

triangle::triangle(fiziks_engine* fiziks, integration i, float w, float h) :
entity(fiziks)
{
	m_shape = create_tri(w, h);
	m_shape->setPosition(v2f(0, 0));
	m_shape->setFillColor(sf::Color::Green);
	//m_rb = new rigidbody(v2f(0, 0), v2f(150, 150), v2f(0, GRAVITY), 45);
	//m_kinematics = new kinematics(i, m_rb);
	m_type = Tria;
}

triangle::~triangle()
{
	safe_delete(m_shape);
	safe_delete(m_rb);
	safe_delete(m_kinematics);
}

void triangle::update()
{
	m_kinematics->update(get_engine()->get_delta_time(), 
						 get_engine()->get_time());
	m_shape->setPosition(get_engine()->world_to_screen(
						 m_kinematics->get_rigidbody()->p()));
}

void triangle::draw(sf::RenderWindow * window)
{
	window->draw(*m_shape);
}

v2f triangle::get_pos()
{
	return m_kinematics->get_rigidbody()->p();
}

sf::ConvexShape* triangle::get_shape()
{
	return m_shape;
}

sf::ConvexShape* triangle::create_tri(float w, float h)
{
	sf::ConvexShape* tri = new sf::ConvexShape(3);
	tri->setPoint(0, v2f(0, 0));
	tri->setPoint(1, v2f(w, 0));
	tri->setPoint(2, v2f(w * 0.5f, h));

	return tri;
}
