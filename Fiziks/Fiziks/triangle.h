// Author: Dante Nardo
// Last Modified: 3/2/2018
// Purpose: A circular fiziks entity.

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "entity.h"
#include "kinematics.h"

class triangle : public entity
{
public:
	triangle(fiziks_engine* fiziks, integration i, float w, float h);
	~triangle();

	void update();
	void draw(sf::RenderWindow* window);
	sf::ConvexShape* shape();
	v2f get_pos();

private:
	kinematics* m_kinematics;
	rigidbody* m_rb;
	sf::ConvexShape* m_shape;

	sf::ConvexShape* create_tri(float w, float h);
};

#endif // !TRIANGLE_H