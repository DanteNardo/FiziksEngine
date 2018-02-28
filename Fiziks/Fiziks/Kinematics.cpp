#include "kinematics.h"

kinematics::kinematics()
{
	m_integration = SemiImplicitEuler;
	m_k_point = new k_point();
}

kinematics::kinematics(integration integration, k_point* k_point)
{
	m_integration = integration;
	m_k_point = k_point;

	// Apply angle to initial velocity
	m_k_point->m_vel.x *= (float)(cos(rad(m_k_point->m_theta)));
	m_k_point->m_vel.y *= (float)(sin(rad(m_k_point->m_theta)));
}

kinematics::~kinematics()
{
	safe_delete(m_k_point);
}

void kinematics::update(const float dt, const float tt)
{
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
	case UniformAcceleration:
		uniform_acceleration(tt);
		break;
	case ProjectileMotion:
		projectile_motion(tt);
		break;
	}
}

k_point* kinematics::get_k_point()
{
	return m_k_point;
}

/*
First Order Integration
Benefits: Fast calculation, relative accuracy with small time steps.
Drawbacks: Damping and undulating acceleration can cause large gains in
energy over time and a small time-step is necessary for accuracy.
*/
void kinematics::explicit_euler_integration(const float dt)
{
	// Update position, then velocity
	m_k_point->m_pos += m_k_point->m_vel * dt;
	m_k_point->m_vel += m_k_point->m_acc * dt;
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
void kinematics::semi_implicit_euler_integration(const float dt)
{
	// Update velocity, then position
	m_k_point->m_vel += m_k_point->m_acc * dt;
	m_k_point->m_pos += m_k_point->m_vel * dt;
}

/*
Fourth Order Integration
Benefits: Very, very accurate (error introduced in fourth derivative).
Drawbacks: Expensive calculations and energy loss over time.
*/
void kinematics::runge_kutta_4_integration(const float dt)
{

}

/*
First Order Integration
Benefits: Provides a highly accurate answer without time step error.
Drawbacks: Can only be used when the acceleration is not changing (0 jerk).
*/
void kinematics::uniform_acceleration(const float tt)
{
	// s = (initial p) + (v initial times t) + (half a times t squared)
	m_k_point->m_pos = 	(m_k_point->m_i_pos) + 
						(m_k_point->m_vel * tt) + 
						(0.5f * m_k_point->m_acc * pow(tt, 2));
}

/*
First Order Integration
Benefits: Can be used to find projectile's exact position based on initial
velocity and the angle at which it was fired.
Drawbacks: Can only be used when the acceleration is not changing (0 jerk)
and it can be more expensive in processing power.
*/
void kinematics::projectile_motion(const float tt)
{
	// x(t) = initial v times cos(theta)
	m_k_point->m_pos.x = m_k_point->m_i_vel.x * cos(rad(m_k_point->m_theta)) * tt;

	// y(t) = 	(initial v times sin(theta) times t) plus 
	// 			(one half of GRAVITY times (time squared))
	m_k_point->m_pos.y = (m_k_point->m_i_vel.y * sin(rad(m_k_point->m_theta)) * tt) + 
						 (0.5f * GRAVITY * (pow(tt, 2)));
}
