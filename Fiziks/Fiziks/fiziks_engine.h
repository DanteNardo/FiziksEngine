// Dante Nardo
// Last Modified: 2/13/2018
// Purpose: Runs the physics simulation.

#ifndef FIZIKS_ENGINE_H
#define FIZIKS_ENGINE_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "bounds.h"
#include "observer.h"

class observer;
class fiziks_engine
{
public:
    fiziks_engine();
    ~fiziks_engine();

    void update();
    void draw(sf::RenderWindow* window);

	void attach(observer* view);
	sf::Time get_time();
	sf::Time get_delta_time();
	v2f world_to_screen(const v2f& position);

private:
	sf::Clock* m_timer;
	sf::Clock* m_delta_timer;
	sf::Time m_delta_time;
	std::vector<observer*> m_views;
};

#endif // !FIZIKS_ENGINE_H