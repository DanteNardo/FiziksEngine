// Author: Dante Nardo
// Last Modified: 3/10/2018
// Purpose: A triangular fiziks entity.

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "entity.h"

class triangle : public entity
{
public:
	triangle(fiziks_engine* fiziks, integration i, float w, float h);
	~triangle();

	void update();
	void draw(sf::RenderWindow* window);

private:
	sf::ConvexShape* create_tri(float w, float h);
};

#endif // !TRIANGLE_H