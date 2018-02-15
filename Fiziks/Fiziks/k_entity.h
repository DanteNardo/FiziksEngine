// Dante Nardo
// Last Modified: 2/15/2018
// Purpose: A kinematic entity that undergoes kinematics simulation.

#ifndef K_ENTITY_H
#define K_ENTITY_H

#include "kinematics.h"
#include "entity.h"

class k_entity : public entity
{
public:
	k_entity(fiziks_engine* fiziks, integration integration);
	~k_entity();

	void update();
	v2f get_pos();

private:
	kinematics* m_kinematics;
};

#endif // !K_ENTITY_H