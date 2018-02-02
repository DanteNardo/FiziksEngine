// Dante Nardo
// Last Modified: 2/1/2018
// Purpose: Performs the calculations for all Kinematics equations.

#pragma once
#include <SFML\Graphics.hpp>

typedef sf::Vector2f v2f;

enum IntegrationType
{
	ExplicitEuler,
	SemiImplicitEuler,
	RungeKutta4
};

class Kinematics
{
private:
	IntegrationType m_integration;
	v2f m_pos;
	v2f m_vel;
	v2f m_acc;

	void explicit_euler_integration(sf::Time* dt);
	void semi_implicit_euler_integration(sf::Time* dt);
	void runge_kutta_4_integration(sf::Time* dt);

public:
	Kinematics();
	Kinematics(IntegrationType integration, v2f pos, v2f vel, v2f acc);
	~Kinematics();

	void update(sf::Time* dt);
	v2f get_pos();
};