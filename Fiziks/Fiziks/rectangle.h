// Author: Dante Nardo
// Last Modified: 3/2/2018
// Purpose: A circular fiziks entity.

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "entity.h"
#include "kinematics.h"

class rectangle : public entity
{
public:
	rectangle(fiziks_engine* fiziks, integration i, v2f size);
	~rectangle();

	void update();
	void draw(sf::RenderWindow* window);
	sf::RectangleShape* get_shape();
	v2f get_pos();

private:
	kinematics * m_kinematics;
	rigidbody* m_rb;
	sf::RectangleShape* m_shape;
};

#endif // !RECTANGLE_H