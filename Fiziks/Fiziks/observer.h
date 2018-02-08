// Dante Nardo
// Last Modified: 2/6/2018
// Purpose: A physics engine observer that simulates calculations.
// Source: https://gafferongames.com/post/integration_basics/

#pragma once
#include "math.h"
#include "fiziks_engine.h"

class observer
{
public:
	observer(fiziks_engine* engine);
	~observer();

	virtual void update(sf::Time* tt, sf::Time* dt) = 0;
	virtual void draw(sf::RenderWindow* window) = 0;

private:
	fiziks_engine* m_engine;
};