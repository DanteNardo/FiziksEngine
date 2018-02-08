// Dante Nardo
// Last Modified: 2/6/2018
// Purpose: A kinematic entity that undergoes kinematics simulation.

#pragma once
#include "observer.h"
#include "kinematics.h"

class k_entity : public observer
{
public:
	k_entity(integration integration);
	~k_entity();

	void update(sf::Time* tt, sf::Time* dt);
	void draw(sf::RenderWindow* window);
	v2f get_pos();

private:
	sf::RectangleShape* m_shape;
	kinematics* m_kinematics;
};

