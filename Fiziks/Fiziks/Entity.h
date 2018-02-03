// Dante Nardo
// Last Modified: 2/2/2018
// Purpose: An entity that undergoes physics in the simulation.

// Source: https://gafferongames.com/post/integration_basics/

#pragma once
#include "Math.h"

class Entity
{
public:
	Entity();
	~Entity();

	virtual void update(sf::Time* tt, sf::Time* dt) = 0;
	virtual void draw(sf::RenderWindow* window) = 0;

protected:
	v2f world_to_screen(const v2f& position);
};