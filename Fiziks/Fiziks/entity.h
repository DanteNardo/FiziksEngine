// Author: Dante Nardo
// Last Modified: 3/3/2018
// Purpose: A generic fiziks entity.

#ifndef ENTITY_H
#define ENTITY_H

#include "fiziks_engine.h"
#include "kinematics.h"

class entity : public Iobserver
{
public:
	entity(fiziks_engine* fiziks);
	~entity();

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual sf::Shape* shape();
	sf::FloatRect bounds();
	rigidbody* rb();

protected:
	sf::Shape* m_shape;
	kinematics* m_kinematics;
	rigidbody* m_rb;
};

#endif // !ENTITY_H