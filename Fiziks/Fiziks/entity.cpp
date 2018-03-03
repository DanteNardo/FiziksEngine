#include "entity.h"

entity::entity(fiziks_engine* fiziks) :
Iobserver(fiziks)
{
}

entity::~entity()
{
	safe_delete(m_shape);
}

sf::Shape* entity::get_shape()
{
	return m_shape;
}

sf::FloatRect entity::get_bounds()
{
	return m_shape->getGlobalBounds();
}
