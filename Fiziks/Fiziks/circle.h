// Author: Dante Nardo
// Last Modified: 3/6/2018
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

private:
	const int SUBDIVISIONS = 21;
	sf::ConvexShape* make_circ(float radius, float size);
};

#endif // !CIRCLE_H