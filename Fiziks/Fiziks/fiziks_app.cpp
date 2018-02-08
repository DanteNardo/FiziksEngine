// Dante Nardo
// Last Modified: 2/2/2018
// Purpose: Controls the physics engine and application.

#include <SFML/Graphics.hpp>
#include "fiziks_engine.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

	// Initialize the engine
	fiziks_engine* fiziks = new fiziks_engine();
	sf::CircleShape circle = sf::CircleShape(20);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(512, 384);

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
		fiziks->update();

		// Rendering
		window.clear();
		//window.draw(circle);
		fiziks->draw(&window);
		window.display();
	}

	// Release dynamic memory
	delete fiziks;

	return 0;
}