// Dante Nardo
// Last Modified: 2/14/2018
// Purpose: A kinematic entity that undergoes kinematics simulation.

#ifndef K_ENTITY_H
#define K_ENTITY_H

#include "kinematics.h"
#include "fiziks_engine.h"

class k_entity : public Iobserver
{
public:
	k_entity(fiziks_engine* fiziks, integration integration);
	~k_entity();

	void update();
	void draw(sf::RenderWindow* window);
	v2f get_pos();

private:
	sf::RectangleShape* m_shape;
	kinematics* m_kinematics;
};

#endif // !K_ENTITY_H