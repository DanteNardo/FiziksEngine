#include "Kinematics.h"

Kinematics::Kinematics()
{
	m_integration = SemiImplicitEuler;
	m_pos = v2f(0, 0);
	m_vel = v2f(0, 0);
	m_acc = v2f(0, 0);
}

Kinematics::Kinematics(IntegrationType integration, v2f pos, v2f vel, v2f acc)
{
	m_integration = SemiImplicitEuler;
	m_pos = pos;
	m_vel = vel;
	m_acc = acc;
}

Kinematics::~Kinematics()
{

}

void Kinematics::update(sf::Time* dt)
{
	// Perform kinematics calculations based on Integration type
	switch (m_integration)
	{
	case ExplicitEuler:
		explicit_euler_integration(dt);
		break;
	case SemiImplicitEuler:
		semi_implicit_euler_integration(dt);
		break;
	case RungeKutta4:
		runge_kutta_4_integration(dt);
		break;
	}
}

v2f Kinematics::get_pos()
{
	return m_pos;
}

/*
First Order Integration
Benefits: Fast calculation, relative accuracy with small time steps.
Drawbacks: Damping and undulating acceleration can cause large gains in
energy over time and a small time-step is necessary for accuracy.
*/
void Kinematics::explicit_euler_integration(sf::Time* dt)
{
	// Update position, then velocity
	m_pos += m_vel * dt->asSeconds();
	m_vel += m_acc * dt->asSeconds();
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
void Kinematics::semi_implicit_euler_integration(sf::Time* dt)
{
	// Update velocity, then position
	m_vel += m_acc * dt->asSeconds();
	m_pos += m_vel * dt->asSeconds();
}

/*
Fourth Order Integration
Benefits: Very, very accurate (error introduced in fourth derivative).
Drawbacks: Expensive calculations and energy loss.
*/
void Kinematics::runge_kutta_4_integration(sf::Time* dt)
{

}