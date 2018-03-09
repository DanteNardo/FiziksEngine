#include "kinematics.h"

kinematics::kinematics()
{
	m_integration = SemiImplicitEuler;
	m_rb = new rigidbody();
}

kinematics::kinematics(integration integration, rigidbody* rb)
{
	m_integration = integration;
	m_rb = rb;

	// Apply angle to initial velocity
	m_rb->v().x *= (float)(cos(rad(m_rb->t())));
	m_rb->v().y *= (float)(sin(rad(m_rb->t())));
}

kinematics::~kinematics()
{
	safe_delete(m_rb);
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

rigidbody* kinematics::rb()
{
	return m_rb;
}

void kinematics::rb(rigidbody* r)
{
	m_rb = r;
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
	m_rb->p(m_rb->p() + m_rb->v() * dt);
	m_rb->v(m_rb->v() + m_rb->a() * dt);
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
	m_rb->v(m_rb->v() + m_rb->a() * dt);
	m_rb->p(m_rb->p() + m_rb->v() * dt);
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
	m_rb->p((m_rb->ip()) + (m_rb->v() * tt) + (0.5f * m_rb->a() * pow(tt, 2)));
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
	m_rb->p().x = m_rb->iv().x * cos(rad(m_rb->t())) * tt;

	// y(t) = 	(initial v times sin(theta) times t) plus 
	// 			(one half of GRAVITY times (time squared))
	m_rb->p().y = (m_rb->iv().y * sin(rad(m_rb->t())) * tt) + 
				  (0.5f * GRAVITY * (pow(tt, 2)));
}
