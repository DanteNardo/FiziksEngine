// Dante Nardo
// Last Modified: 2/2/2018
// Purpose: An entity that undergoes kinematics simulation.

#pragma once
#include "Entity.h"
#include "Kinematics.h"

class KinematicsEntity : public Entity
{
public:
	KinematicsEntity(IntegrationType integration);
	~KinematicsEntity();

	void update(sf::Time* tt, sf::Time* dt);
	void draw(sf::RenderWindow* window);
	v2f get_pos();

private:
	sf::RectangleShape* m_shape;
	Kinematics* m_kinematics;
};

