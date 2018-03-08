#include "circle.h"

circle::circle(fiziks_engine* fiziks, integration i, float radius) :
entity(fiziks)
{
	m_type = Circ;
	m_shape = make_circ(radius);
	m_shape->setPosition(v2f(200, 200));
	m_shape->setFillColor(sf::Color::Green);
	m_shape->setOrigin(v2f(radius, radius));
	m_rb = new rigidbody(v2f(0, 0), v2f(200, 200), v2f(0, GRAVITY), 45, radius, Rock);
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
	m_shape->setPosition(world_to_screen(m_rb->p()));
}

void circle::draw(sf::RenderWindow * window)
{
	window->draw(*m_shape);
}

sf::ConvexShape* circle::make_circ(float radius)
{
	// Initialize circle data
	sf::ConvexShape* c = new sf::ConvexShape(SUBDIVISIONS);
	float angle = 0;
	int angleMod = 360 / SUBDIVISIONS;

	// Create all circle points
	for (int i = 0; i < SUBDIVISIONS; i++) {
		c->setPoint(i, v2f(cos(rad(angle)) * radius, 
						   sin(rad(angle)) * radius));
		angle -= angleMod;
	}

	return c;
}