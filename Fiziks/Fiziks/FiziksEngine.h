// Dante Nardo
// Last Modified: 2/2/2018
// Purpose: Runs the physics simulation.

#include <SFML/Graphics.hpp>
#include <vector>
#include "KinematicsEntity.h"

class FiziksEngine
{
public:
    FiziksEngine();
    ~FiziksEngine();

    void update();
    void draw(sf::RenderWindow* window);

private:
	sf::Clock* m_timer;
	sf::Clock* m_delta_timer;
	std::vector<Entity*> m_entities;
};