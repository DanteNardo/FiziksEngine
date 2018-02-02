// Dante Nardo
// Last Modified: 2/1/2018
// Purpose: Runs the physics simulation.

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

class FiziksEngine
{
private:
	sf::Clock* m_timer;
    std::vector<Entity*> m_entities;

public:
    FiziksEngine();
    ~FiziksEngine();

    void update();
    void draw(sf::RenderWindow* window);

	void new_entity();
};