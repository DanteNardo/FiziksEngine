#include "Kinematics.h"

Kinematics::Kinematics()
{
	m_integration = SemiImplicitEuler;
	m_i_pos = v2f(0, 0);
	m_v_pos = v2f(0, 0);
	m_pos = v2f(0, 0);
	m_vel = v2f(0, 0);
	m_acc = v2f(0, 0);
}

Kinematics::Kinematics(IntegrationType integration, v2f pos, v2f vel, v2f acc, int theta)
{
	m_integration = integration;
	m_i_pos = pos;
	m_v_pos = vel;
	m_pos = pos;
	m_vel = vel;
	m_acc = acc;
	m_theta = theta;
}

Kinematics::Kinematics(v2f pos, v2f vel, int theta)
{
	m_integration = ProjectileMotion;
	m_i_pos = pos;
	m_v_pos = vel;
	m_pos = pos;
	m_vel = vel;
	m_acc = v2f(0, GRAVITY);
	m_theta = theta;
}

Kinematics::~Kinematics()
{

}

void Kinematics::update(sf::Time* tt, sf::Time* dt)
{
	switch (m_integration)
	{
	case ExplicitEuler:
		explicit_euler_integration(dt->asSeconds());
		break;
	case SemiImplicitEuler:
		semi_implicit_euler_integration(dt->asSeconds());
		break;
	case RungeKutta4:
		runge_kutta_4_integration(dt->asSeconds());
		break;
	case UniformAcceleration:
		uniform_acceleration(tt->asSeconds());
		break;
	case ProjectileMotion:
		projectile_motion(tt->asSeconds());
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
void Kinematics::explicit_euler_integration(const float dt)
{
	// Update position, then velocity
	m_pos += m_vel * dt;
	m_vel += m_acc * dt;
}

/*
Symplectic: Explicit methods calculate the state of a system at a later
time from the state of the system at the current time, while implicit methods
find a solution by solving an equation involving both the current state and
later state of the system.
*/
/*
First Order Integration
Benefits: Fast calculation, relative accuracy with small time steps.
Drawbacks: Same order as explicit euler, but it is symplectic which
generates a better result.
*/
void Kinematics::semi_implicit_euler_integration(const float dt)
{
	// Update velocity, then position
	m_vel += m_acc * dt;
	m_pos += m_vel * dt;
}

/*
Fourth Order Integration
Benefits: Very, very accurate (error introduced in fourth derivative).
Drawbacks: Expensive calculations and energy loss over time.
*/
void Kinematics::runge_kutta_4_integration(const float dt)
{

}

/*
First Order Integration
Benefits: Provides a highly accurate answer without time step error.
Drawbacks: Can only be used when the acceleration is not changing (0 jerk).
*/
void Kinematics::uniform_acceleration(const float tt)
{
	// s = (initial p) + (v initial times t) + (half a times t squared)
	m_pos = (m_i_pos) + (m_vel * tt) + (0.5f * m_acc * pow(tt, 2));
}

/*
First Order Integration
Benefits: Can be used to find projectile's exact position based on initial
velocity and the angle at which it was fired.
Drawbacks: Can only be used when the acceleration is not changing (0 jerk)
and it can be more expensive in processing power.
*/
void Kinematics::projectile_motion(const float tt)
{
	// x(t) = initial v times cos(theta)
	float x = m_vel.x * cos(m_theta * PI / 180) * tt;

	// y(t) = ((initial v times sin(theta)) times t) minus (one half of GRAVITY times (time squared))
	float y = (m_vel.y * sin(m_theta * PI / 180) * tt) + (0.5f * GRAVITY * (pow(tt, 2)));

	m_pos.x = x;
	m_pos.y = y;
}
