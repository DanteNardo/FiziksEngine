// Dante Nardo
// Last Modified: 2/1/2018
// Purpose: Controls the physics engine and application.

#include <SFML/Graphics.hpp>
#include "FiziksEngine.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

	// Initialize the engine
	FiziksEngine* fiziks_engine = new FiziksEngine();

	// Variables for projectile motion
	sf::Vector2f position = sf::Vector2f(0, 768);
	sf::Vector2f velocity = sf::Vector2f(50, -50);
	sf::Vector2f acceleration = sf::Vector2f(0, 9.8f);

	// Main Application Loop
	while (window.isOpen()) {

		// Poll for events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Update entire physics engine
		fiziks_engine->update();

		// Rendering
		window.clear();
		fiziks_engine->draw(&window);
		window.display();
	}

	// Release dynamic memory
	delete fiziks_engine;

	return 0;
}