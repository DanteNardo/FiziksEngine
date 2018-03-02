// Author: Dante Nardo
// Last Modified: 3/1/2018
// Purpose: A generic fiziks entity.

#ifndef ENTITY_H
#define ENTITY_H

#include "fiziks_engine.h"

enum entity_type
{
	Square,
	Circle,
	Triangle
};

class entity : public Iobserver
{
public:
	entity(fiziks_engine* fiziks);
	//entity(fiziks_engine* fiziks, const v2f& size);
	//entity(fiziks_engine* fiziks, const float radius, const float count);
	//entity(fiziks_engine* fiziks, const float size);
	~entity();

	void update();
	void draw(sf::RenderWindow* window);
	sf::Shape* get_shape();

protected:
	sf::Shape* m_shape;
};

#endif // !ENTITY_H