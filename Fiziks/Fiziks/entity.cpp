#include "entity.h"

entity::entity(fiziks_engine* fiziks) :
Iobserver(fiziks)
{
	m_sprite = new sf::Sprite();
}

entity::~entity()
{
	safe_delete(m_sprite);
}

void entity::update()
{

}

void entity::draw(sf::RenderWindow* window)
{
	window->draw(*m_sprite);
}

sf::Sprite* entity::get_sprite()
{
	return m_sprite;
}
