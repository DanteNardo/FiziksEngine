#include "Entity.h"

// Default Constructor
Entity::Entity()
{
	m_integration = SemiImplicitEuler;
	m_timer = new sf::Clock();
	m_shape = sf::CircleShape(100.f);
	m_shape.setFillColor(sf::Color::Green);
	m_pos = sf::Vector2f(0, 768);
	m_vel = sf::Vector2f(50, -50);
	m_acc = sf::Vector2f(0, 9.8f);
}

// Custom Constructor
Entity::Entity(IntegrationType integration)
{
	m_integration = integration;
	m_timer = new sf::Clock();
	m_shape = sf::CircleShape(100.f);
	m_shape.setFillColor(sf::Color::Green);
	m_pos = sf::Vector2f(0, 768);
	m_vel = sf::Vector2f(50, -50);
	m_acc = sf::Vector2f(0, 9.8f);
}

// Deconstructor
Entity::~Entity()
{
	delete m_timer;
}

// Update Physics Simulations
void Entity::update()
{
	sf::Time* delta_time = &m_timer->restart();

	// Perform kinematics calculations based on Integration type
	switch (m_integration)
	{
		case ExplicitEuler:
			explicit_euler_integration(delta_time);
		break;
		case SemiImplicitEuler:
			semi_implicit_euler_integration(delta_time);
		break;
		case RungeKutta4:
			runge_kutta_4_integration(delta_time);
		break;
	}
}

// Draw Physics Simulations
void Entity::draw(sf::RenderWindow* window)
{
	window->draw(m_shape);
}

/*
	First Order Integration
	Benefits: Fast calculation, relative accuracy with small time steps.
	Drawbacks: Damping and undulating acceleration can cause large gains in
	energy over time and a small time-step is necessary for accuracy.
*/
void Entity::explicit_euler_integration(sf::Time* dt)
{
	// Update position, then velocity
	m_pos += m_vel * dt->asSeconds();
	m_vel += m_acc * dt->asSeconds();
	m_shape.setPosition(m_pos);
}

/*
	First Order Integration
	Benefits: Fast calculation, relative accuracy with small time steps.
	Drawbacks: Same order as explicit euler, but it is symplectic which
	generates a better result.
*/
/*
	Symplectic: Explicit methods calculate the state of a system at a later
	time from the state of the system at the current time, while implicit methods
	find a solution by solving an equation involving both the current state and
	later state of the system.
*/
void Entity::semi_implicit_euler_integration(sf::Time* dt)
{
	// Update velocity, then position
	m_vel += m_acc * dt->asSeconds();
	m_pos += m_vel * dt->asSeconds();
	m_shape.setPosition(m_pos);
}

/*
	Fourth Order Integration
	Benefits: Very, very accurate (error introduced in fourth derivative).
	Drawbacks: Expensive calculations and energy loss.
*/
void Entity::runge_kutta_4_integration(sf::Time* dt)
{

}