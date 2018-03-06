#include "rectangle.h"

rectangle::rectangle(fiziks_engine* fiziks, integration i, v2f size) :
entity(fiziks)
{
	m_shape = make_rect(size);
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

sf::ConvexShape* rectangle::make_rect(float size)
{
	// Initialize circle data
	sf::ConvexShape* c = new sf::ConvexShape(SUBDIVISIONS);
	float angle = 0;
	int angleMod = 360 / SUBDIVISIONS;

	// Create all circle points
	for (int i = 0; i < SUBDIVISIONS; i++) {
		c->setPoint(i, v2f(cos(rad(angle)), sin(rad(angle))));
		angle += angleMod;
	}

	return c;
}