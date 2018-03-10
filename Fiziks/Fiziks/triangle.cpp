#include "triangle.h"

triangle::triangle(fiziks_engine* fiziks, integration i, float w, float h) :
entity(fiziks)
{
	m_type = Tria;
	m_shape = create_tri(w, h);
	m_shape->setPosition(v2f(0, 0));
	m_shape->setFillColor(sf::Color::Green);
	v2f center = v2f(
		(m_shape->getPoint(0).x + m_shape->getPoint(1).x + m_shape->getPoint(2).x) / 3, 
		(m_shape->getPoint(0).y + m_shape->getPoint(1).y + m_shape->getPoint(2).y) / 3);
	m_shape->setOrigin(center);
	m_rb = new rigidbody();
	m_kinematics = new kinematics(i, m_rb);
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
	m_shape->setPosition(world_to_screen(m_rb->p()));
}

void triangle::draw(sf::RenderWindow * window)
{
	window->draw(*m_shape);
}

sf::ConvexShape* triangle::create_tri(float w, float h)
{
	sf::ConvexShape* tri = new sf::ConvexShape(3);
	tri->setPoint(0, v2f(0, 0));
	tri->setPoint(1, v2f(w * 0.5f, h));
	tri->setPoint(2, v2f(w, 0));

	return tri;
}
