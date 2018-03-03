#include "entity.h"

entity::entity(fiziks_engine* fiziks) :
Iobserver(fiziks)
{
}

entity::~entity()
{
	safe_delete(m_shape);
}

sf::Shape* entity::shape()
{
	return m_shape;
}

sf::FloatRect entity::bounds()
{
	return m_shape->getGlobalBounds();
}

rigidbody* entity::rb()
{
	return m_rb;
}
