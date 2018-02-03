#include "FiziksEngine.h"

FiziksEngine::FiziksEngine()
{
	m_timer = new sf::Clock();
	m_delta_timer = new sf::Clock();

	// TODO: No longer hardcode this
	KinematicsEntity* explicit_euler_entity = new KinematicsEntity(ExplicitEuler);
	KinematicsEntity* implicit_euler_entity = new KinematicsEntity(SemiImplicitEuler);
	KinematicsEntity* uniform_entity = new KinematicsEntity(UniformAcceleration);
	KinematicsEntity* projectile_entity = new KinematicsEntity(ProjectileMotion);

	m_entities.push_back(explicit_euler_entity);
	m_entities.push_back(implicit_euler_entity);
	m_entities.push_back(uniform_entity);
	m_entities.push_back(projectile_entity);
}

FiziksEngine::~FiziksEngine()
{
	for (int i = 0; i < m_entities.size(); i++) {
		delete m_entities[i];
		m_entities[i] = nullptr;
	}

	delete m_timer;
	m_timer = nullptr;
	delete m_delta_timer;
	m_delta_timer = nullptr;
}

void FiziksEngine::update()
{
	// Record total time passed in simulation and time since last frame
	sf::Time* total_time = &m_timer->getElapsedTime();
	sf::Time* delta_time = &m_delta_timer->restart();

	for (Entity* e : m_entities) {
		e->update(total_time, delta_time);
	}
}

void FiziksEngine::draw(sf::RenderWindow* window)
{
	for (Entity* e : m_entities) {
		e->draw(window);
	}
}