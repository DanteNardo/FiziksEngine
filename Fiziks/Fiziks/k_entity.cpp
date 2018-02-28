#include "k_entity.h"

k_entity::k_entity(fiziks_engine* fiziks, integration integration) :
entity(fiziks)
{
	m_sprite = new sf::Sprite();
	m_sprite->setPosition(v2f(0, 0));
	k_point* point = new k_point(v2f(100,100), v2f(20, 20), v2f(0, GRAVITY), 45);
	m_kinematics = new kinematics(integration, point);

	//TODO: Remove this texture loading
	sf::Texture texture;
	if (texture.loadFromFile("C:/Users/dante/Source/Repos/FiziksEngine/Fiziks/Fiziks/textures/test_tex.png")) {
		m_sprite->setTexture(texture);
	}
}

k_entity::~k_entity()
{
	safe_delete(m_sprite);
	safe_delete(m_kinematics);
}

void k_entity::update()
{
	m_kinematics->update(get_engine()->get_delta_time(), 
						 get_engine()->get_time());
	m_sprite->setPosition(get_engine()->world_to_screen(
						 m_kinematics->get_k_point()->m_pos));
}

v2f k_entity::get_pos()
{
	return m_kinematics->get_k_point()->m_pos;
}