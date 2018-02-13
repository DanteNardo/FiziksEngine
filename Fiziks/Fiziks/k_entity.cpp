#include "k_entity.h"

k_entity::k_entity(integration integration)
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
	delete m_shape;
	m_shape = nullptr;
	delete m_kinematics;
	m_kinematics = nullptr;
}

void k_entity::update(sf::Time* tt, sf::Time* dt)
{
	m_kinematics->update(tt, dt);
	m_shape->setPosition(world_to_screen(m_kinematics->get_k_point()->m_pos));
}

void k_entity::draw(sf::RenderWindow* window)
{
	window->draw(*m_shape);
}

v2f k_entity::get_pos()
{
	return m_kinematics->get_k_point()->m_pos;
}