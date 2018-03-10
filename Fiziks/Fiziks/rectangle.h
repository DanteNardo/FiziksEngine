// Author: Dante Nardo
// Last Modified: 3/10/2018
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
	sf::ConvexShape* make_rect(v2f size);
};

#endif // !RECTANGLE_H