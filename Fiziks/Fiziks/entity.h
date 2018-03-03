// Author: Dante Nardo
// Last Modified: 3/2/2018
// Purpose: A generic fiziks entity.

#ifndef ENTITY_H
#define ENTITY_H

#include "fiziks_engine.h"

class entity : public Iobserver
{
public:
	entity(fiziks_engine* fiziks);
	~entity();

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual sf::Shape* get_shape();
	sf::FloatRect get_bounds();

protected:
	sf::Shape* m_shape;
};

#endif // !ENTITY_H