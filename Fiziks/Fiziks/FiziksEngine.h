#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

class FiziksEngine
{
private:
    std::vector<Entity*> e_list;

public:
    FiziksEngine();
    ~FiziksEngine();

    void update();
    void draw(sf::RenderWindow* window);
}