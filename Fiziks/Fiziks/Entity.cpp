#include "Entity.h"

// Default Constructor
Entity::Entity()
{
	m_shape = new sf::CircleShape(100.f);
	m_shape->setFillColor(sf::Color::Green);
	m_kinematics = new Kinematics();
}

// Deconstructor
Entity::~Entity()
{
	delete m_shape;
	m_shape = nullptr;
	delete m_kinematics;
	m_kinematics = nullptr;
}

// Update Physics Simulations
void Entity::update(sf::Time* dt)
{
	m_kinematics->update(dt);
	m_shape->setPosition(m_kinematics->get_pos());
}

// Draw Physics Simulations
void Entity::draw(sf::RenderWindow* window)
{
	window->draw(*m_shape);
}