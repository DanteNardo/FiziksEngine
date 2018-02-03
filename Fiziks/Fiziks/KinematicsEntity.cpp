#include "KinematicsEntity.h"

KinematicsEntity::KinematicsEntity(IntegrationType integration)
{
	m_shape = new sf::RectangleShape();
	m_shape->setSize(v2f(25.0f, 25.0f));
	m_shape->setPosition(v2f(0, 0));
	m_shape->setFillColor(sf::Color::Red);
	m_shape->setOutlineColor(sf::Color::Green);
	m_shape->setOutlineThickness(2);
	m_kinematics = new Kinematics(integration, v2f(0, 0), v2f(70, 70), v2f(0, GRAVITY), 45);
}

KinematicsEntity::~KinematicsEntity()
{
	delete m_shape;
	m_shape = nullptr;
	delete m_kinematics;
	m_kinematics = nullptr;
}

void KinematicsEntity::update(sf::Time* tt, sf::Time* dt)
{
	m_kinematics->update(tt, dt);
	m_shape->setPosition(world_to_screen(m_kinematics->get_pos()));
}

void KinematicsEntity::draw(sf::RenderWindow* window)
{
	window->draw(*m_shape);
}