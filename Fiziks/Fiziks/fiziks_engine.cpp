#include "fiziks_engine.h"

fiziks_engine::fiziks_engine()
{
	m_timer = new sf::Clock();
	m_delta_timer = new sf::Clock();

	// TODO: No longer hardcode this
	k_entity* exp_euler_entity = new k_entity(ExplicitEuler);
	k_entity* imp_euler_entity = new k_entity(SemiImplicitEuler);
	k_entity* uni_entity = new k_entity(UniformAcceleration);
	k_entity* proj_entity = new k_entity(ProjectileMotion);

	attach(exp_euler_entity);
	attach(imp_euler_entity);
	attach(uni_entity);
	attach(proj_entity);
}

fiziks_engine::~fiziks_engine()
{
	for (int i = 0; i < m_views.size(); i++) {
		delete m_views[i];
		m_views[i] = nullptr;
	}

	delete m_timer;
	m_timer = nullptr;
	delete m_delta_timer;
	m_delta_timer = nullptr;
}

void fiziks_engine::update()
{
	// Record total time passed in simulation and time since last frame
	sf::Time* total_time = &m_timer->getElapsedTime();
	sf::Time* delta_time = &m_delta_timer->restart();

	for (observer* o : m_views) {
		o->update(total_time, delta_time);
	}
}

void fiziks_engine::draw(sf::RenderWindow* window)
{
	for (observer* o : m_views) {
		o->draw(window);
	}
}

void fiziks_engine::attach(observer* view)
{
	m_views.push_back(view);
}

// TODO: Implement this correctly
v2f fiziks_engine::world_to_screen(const v2f& position)
{
	return v2f(position.x, 768 - position.y);
}