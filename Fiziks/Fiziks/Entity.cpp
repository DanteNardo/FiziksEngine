#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

// TODO: Implement this correctly
v2f Entity::world_to_screen(const v2f& position)
{
	return v2f(position.x, 768 - position.y);
}
