// Author: Dante Nardo
// Last Modified: 3/3/2018
// Purpose: A circular fiziks entity.

#ifndef CIRCLE_H
#define CIRCLE_H

#include "entity.h"

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
	sf::CircleShape* m_shape;
};

#endif // !CIRCLE_H