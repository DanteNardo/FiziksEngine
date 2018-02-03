// Dante Nardo
// Last Modified: 2/2/2018
// Purpose: Performs the calculations for all Kinematics equations.

#pragma once
#include "Math.h"

enum IntegrationType
{
	ExplicitEuler,
	SemiImplicitEuler,
	RungeKutta4,
	UniformAcceleration,
	ProjectileMotion
};

class Kinematics
{
public:
	Kinematics();
	Kinematics(IntegrationType integration, v2f pos, v2f vel, v2f acc, int theta);
	Kinematics(v2f pos, v2f vel, int theta);
	~Kinematics();

	void update(sf::Time* tt, sf::Time* dt);
	v2f get_pos();

private:
	IntegrationType m_integration;
	v2f m_i_pos;
	v2f m_v_pos;
	v2f m_pos;
	v2f m_vel;
	v2f m_acc;
	int m_theta;

	void explicit_euler_integration(const float dt);
	void semi_implicit_euler_integration(const float dt);
	void runge_kutta_4_integration(const float dt);
	void uniform_acceleration(const float tt);
	void projectile_motion(const float tt);
};