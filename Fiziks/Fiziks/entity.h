// Author: Dante Nardo
// Last Modified: 3/8/2018
// Purpose: A generic fiziks entity.

#ifndef ENTITY_H
#define ENTITY_H

#include "math.h"
#include "fiziks_engine.h"
#include "kinematics.h"

#define NUM_ETYPE 3;

enum e_type
{
	Rect,
	Circ,
	Tria
};

class entity : public Iobserver
{
public:
	entity(fiziks_engine* fiziks);
	~entity();

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* window) = 0;

	v2f center();
	v2f global_vertex(int i);
	sf::ConvexShape* shape();
	sf::FloatRect bounds();
	rigidbody* rb();
	e_type type();

protected:
	sf::ConvexShape* m_shape;
	kinematics* m_kinematics;
	rigidbody* m_rb;
	e_type m_type;
};

#endif // !ENTITY_H