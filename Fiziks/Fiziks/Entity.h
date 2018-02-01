// Source: https://gafferongames.com/post/integration_basics/

#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
private:
	IntegrationType m_integration;
	sf::Clock* m_timer;
	sf::CircleShape m_shape;
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	sf::Vector2f m_acc;

	void explicit_euler_integration(sf::Time* dt);
	void semi_implicit_euler_integration(sf::Time* dt);
	void runge_kutta_4_integration(sf::Time* dt);

public:
	Entity();
	Entity(IntegrationType integration);
	~Entity();

	void update();
	void draw(sf::RenderWindow* window);
};

enum IntegrationType
{
	ExplicitEuler,
	SemiImplicitEuler,
	RungeKutta4
};