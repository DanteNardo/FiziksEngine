// Author: Dante Nardo
// Last Modified: 3/2/2018
// Purpose: A circular fiziks entity.

#ifndef CIRCLE_H
#define CIRCLE_H

#include "entity.h"
#include "kinematics.h"

class circle : public entity
{
public:
	circle(fiziks_engine* fiziks, integration i, float radius, float size);
	~circle();

	void update();
	void draw(sf::RenderWindow* window);
	sf::CircleShape* get_shape();
	v2f get_pos();

private:
	kinematics* m_kinematics;
	rigidbody* m_rb;
	sf::CircleShape* m_shape;
};

#endif // !CIRCLE_H