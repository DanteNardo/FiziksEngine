#include "circle.h"

circle::circle(fiziks_engine* fiziks, integration i, float radius) :
entity(fiziks)
{
	m_type = Circ;
	m_shape = make_circ(radius);
	m_shape->setPosition(v2f(0, 0));
	m_shape->setFillColor(sf::Color::Green);
	//m_shape->setOrigin(radius, radius);
	m_rb = new rigidbody();
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
	// TODO: Remove when not debugging
	m_shape->setFillColor(sf::Color::Green);

	m_kinematics->update(get_engine()->get_delta_time(), 
						 get_engine()->get_time());
	m_shape->setPosition(m_rb->p());
	m_shape->setRotation(rad(m_rb->o()));
}

void circle::draw(sf::RenderWindow * window)
{
	window->draw(*m_shape);

	// DEBUGGING: ARBB
	sf::RectangleShape r = sf::RectangleShape(v2f(m_shape->getGlobalBounds().width, m_shape->getGlobalBounds().height));
	r.setPosition(v2f(m_shape->getGlobalBounds().left, m_shape->getGlobalBounds().top));
	r.setFillColor(sf::Color::Transparent);
	r.setOutlineColor(sf::Color::Blue);
	r.setOutlineThickness(1);
	//window->draw(r);
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