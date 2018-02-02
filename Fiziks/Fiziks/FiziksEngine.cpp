#include "FiziksEngine.h"

FiziksEngine::FiziksEngine()
{
	m_timer = new sf::Clock();
	new_entity();
}

FiziksEngine::~FiziksEngine()
{
	for (int i = 0; i < m_entities.size(); i++) {
		delete m_entities[i];
		m_entities[i] = nullptr;
	}

	delete m_timer;
	m_timer = nullptr;
}

void FiziksEngine::update()
{
	sf::Time* delta_time = &m_timer->restart();

	for (Entity* e : m_entities) {
		e->update(delta_time);
	}
}

void FiziksEngine::draw(sf::RenderWindow* window)
{
	for (Entity* e : m_entities) {
		e->draw(window);
	}
}

void FiziksEngine::new_entity()
{
	m_entities.push_back(new Entity());
}