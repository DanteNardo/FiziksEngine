// Dante Nardo
// Last Modified: 3/8/2018
// Purpose: Performs the calculations for all Kinematics equations.

#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "rigidbody.h"

enum integration
{
	ExplicitEuler,
	SemiImplicitEuler,
	RungeKutta4,
	UniformAcceleration,
	ProjectileMotion
};

class kinematics
{
public:
	kinematics();
	kinematics(integration integration, rigidbody* rb);
	~kinematics();

	void update(const float dt, const float tt);
	rigidbody* rb();
	void rb(rigidbody* r);

private:
	integration m_integration;
	rigidbody* m_rb;

	// Different integration methods
	void explicit_euler_integration(const float dt);
	void semi_implicit_euler_integration(const float dt);
	void runge_kutta_4_integration(const float dt);
	void uniform_acceleration(const float tt);
	void projectile_motion(const float tt);
};

#endif // !KINEMATICS_H