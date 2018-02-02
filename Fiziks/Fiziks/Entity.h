// Dante Nardo
// Last Modified: 2/1/2018
// Purpose: An entity that undergoes physics in the simulation.

// Source: https://gafferongames.com/post/integration_basics/

#pragma once
#include <SFML/Graphics.hpp>
#include "Kinematics.h"

class Entity
{
private:
	sf::CircleShape* m_shape;
	Kinematics* m_kinematics;

public:
	Entity();
	~Entity();

	void update(sf::Time* dt);
	void draw(sf::RenderWindow* window);
};