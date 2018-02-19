// Author: Dante Nardo
// Last Modified: 2/15/2018
// Purpose: A generic fiziks entity.

#ifndef ENTITY_H
#define ENTITY_H

#include "fiziks_engine.h"

class entity : public Iobserver
{
public:
	entity(fiziks_engine* fiziks);
	~entity();

	void update();
	void draw(sf::RenderWindow* window);
	sf::Sprite* get_sprite();
	sf::FloatRect* get_rect();

protected:
	sf::Sprite* m_sprite;
};

#endif // !ENTITY_H