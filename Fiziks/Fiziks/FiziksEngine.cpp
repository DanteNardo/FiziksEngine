#include "FiziksEngine.h"

FiziksEngine::FiziksEngine()
{
}

FiziksEngine::~FiziksEngine()
{
}

void FiziksEngine::update()
{
	for (Entity* e : e_list) {
		e->update();
	}
}

void FiziksEngine::draw(sf::RenderWindow* window)
{
	for (Entity* e : e_list) {
		e->draw(window);
	}
}