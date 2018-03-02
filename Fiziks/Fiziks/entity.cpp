#include "entity.h"

entity::entity(fiziks_engine* fiziks) :
Iobserver(fiziks)
{
	//m_shape = new sf::ConvexShape(3);
	//m_shape->setPoint();
}

//entity::entity(fiziks_engine* fiziks, const v2f& size) :
//Iobserver(fiziks)
//{
//	m_shape = new sf::RectangleShape(size);
//}
//
//entity::entity(fiziks_engine* fiziks, const float radius, const float count) :
//Iobserver(fiziks)
//{
//	m_shape = new sf::CircleShape(radius, count);
//}
//
//entity::entity(fiziks_engine* fiziks, const float size) :
//	Iobserver(fiziks)
//{
//	m_shape = new sf::ConvexShape(3);
//	m_shape->setPoint()
//}

entity::~entity()
{
	safe_delete(m_shape);
}

void entity::update()
{

}

void entity::draw(sf::RenderWindow* window)
{
	window->draw(*m_shape);
}

sf::Shape* entity::get_shape()
{
	return m_shape;
}