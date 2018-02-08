// Dante Nardo
// Last Modified: 2/6/2018
// Purpose: Runs the physics simulation.

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "k_entity.h"

class fiziks_engine
{
public:
    fiziks_engine();
    ~fiziks_engine();

    void update();
    void draw(sf::RenderWindow* window);

	void attach(observer* view);

private:
	sf::Clock* m_timer;
	sf::Clock* m_delta_timer;
	std::vector<observer*> m_views;

	v2f world_to_screen(const v2f& position);
};