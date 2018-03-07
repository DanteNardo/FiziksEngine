// Dante Nardo
// Last Modified: 3/6/2018
// Purpose: Controls the physics engine and application.

#include "fiziks_engine.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

	// Initialize the engine
	fiziks_engine* fiziks = new fiziks_engine(&window);

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
		fiziks->draw(&window);
		window.display();
	}

	// Release dynamic memory
	delete fiziks;

	return 0;
}