// Author: Dante Nardo
// Last Modified: 3/6/2018
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

private:
	const int SUBDIVISIONS = 21;
	sf::ConvexShape* make_rect(float size);
};

#endif // !RECTANGLE_H