#include "rectangle.h"

rectangle::rectangle(fiziks_engine* fiziks, integration i, v2f size) :
entity(fiziks)
{
	m_type = Rect;
	m_shape = make_rect(size);
	m_shape->setPosition(v2f(250, 300));
	m_shape->setFillColor(sf::Color::Green);
	//m_shape->setOrigin(size.x / 2, size.y / 2);
	m_rb = new rigidbody();
	m_kinematics = new kinematics(i, m_rb);
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
	m_shape->setPosition(m_rb->p());
	//m_shape->setRotation(rad(m_rb->o()));
}

void rectangle::draw(sf::RenderWindow* window)
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

sf::ConvexShape* rectangle::make_rect(v2f size)
{
	// Initialize rectangle data
	sf::ConvexShape* r = new sf::ConvexShape(4);

	// Create all rectangle points (bottom left -> clockwise)
	r->setPoint(0, v2f(0, 0));
	r->setPoint(1, v2f(0, size.y));
	r->setPoint(2, v2f(size.x, size.y));
	r->setPoint(3, v2f(size.x, 0));

	return r;
}