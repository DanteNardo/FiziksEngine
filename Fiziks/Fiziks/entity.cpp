#include "entity.h"

entity::entity(fiziks_engine* fiziks) :
Iobserver(fiziks)
{
}

entity::~entity()
{
	safe_delete(m_shape);
}

sf::ConvexShape* entity::shape()
{
	return m_shape;
}

sf::FloatRect entity::bounds()
{
	return m_shape->getGlobalBounds();
}

v2f entity::center()
{
	return m_rb->p();
}

rigidbody* entity::rb()
{
	return m_rb;
}

e_type entity::type()
{
	return m_type;
}
