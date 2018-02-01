// Dante Nardo
// Last Modified: 1/21/2018
// Purpose: Runs the physics simulation and rendering.

#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024,768), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// Variables for projectile motion
	sf::Vector2f position = sf::Vector2f(0,768);
	sf::Vector2f velocity = sf::Vector2f(50,-50);
	sf::Vector2f acceleration = sf::Vector2f(0,9.8f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Update position, velocity, and acceleration
		velocity += acceleration;
		position += velocity;
		shape.setPosition(position);

		// Rendering
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}