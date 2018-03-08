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

v2f entity::global_vertex(int i)
{
	return m_shape->getTransform().transformPoint(m_shape->getPoint(i));
}

rigidbody* entity::rb()
{
	return m_rb;
}

e_type entity::type()
{
	return m_type;
}
