// Dante Nardo
// Last Modified: 2/13/2018
// Purpose: Performs the calculations for all Kinematics equations.

#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "math.h"

enum integration
{
	ExplicitEuler,
	SemiImplicitEuler,
	RungeKutta4,
	UniformAcceleration,
	ProjectileMotion
};

struct k_point
{
	v2f m_i_pos;
	v2f m_i_vel;
	v2f m_pos;
	v2f m_vel;
	v2f m_acc;
	int m_theta;

	k_point::k_point()
	{
		m_i_pos = v2f(0, 0);
		m_i_vel = v2f(0, 0);
		m_pos = v2f(0, 0);
		m_vel = v2f(0, 0);
		m_acc = v2f(0, 0);
	}

	k_point::k_point(v2f pos, v2f vel, v2f acc, int theta)
	{
		m_i_pos = pos;
		m_i_vel = vel;
		m_pos = pos;
		m_vel = vel;
		m_acc = acc;
		m_theta = theta;
	}
};

class kinematics
{
public:
	kinematics();
	kinematics(integration integration, k_point* k_point);
	~kinematics();

	void update(const sf::Time* tt, const sf::Time* dt);
	k_point* get_k_point();

private:
	integration m_integration;
	k_point* m_k_point;

	void explicit_euler_integration(const float dt);
	void semi_implicit_euler_integration(const float dt);
	void runge_kutta_4_integration(const float dt);
	void uniform_acceleration(const float tt);
	void projectile_motion(const float tt);
};

#endif // !KINEMATICS_H