// Author: Dante Nardo
// Last Modified: 3/10/2018
// Purpose: A circular fiziks entity.

#ifndef CIRCLE_H
#define CIRCLE_H

#include "entity.h"

class circle : public entity
{
public:
	circle(fiziks_engine* fiziks, integration i, float radius);
	~circle();

	void update();
	void draw(sf::RenderWindow* window);

private:
	const int SUBDIVISIONS = 21;
	sf::ConvexShape* make_circ(float radius);
};

#endif // !CIRCLE_H