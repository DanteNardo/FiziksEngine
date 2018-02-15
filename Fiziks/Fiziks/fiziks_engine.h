// Dante Nardo
// Last Modified: 2/14/2018
// Purpose: Runs the physics simulation.

#ifndef FIZIKS_ENGINE_H
#define FIZIKS_ENGINE_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "bounds.h"

/*
Observer Design Pattern
This is the subject in the observer design pattern. All classes that implement
the Iobserver interface have a reference to this subject and are notified by
the subject when the values change.
*/
class fiziks_engine
{
public:
    fiziks_engine();
    ~fiziks_engine();

    void update();
    void draw(sf::RenderWindow* window);

	void attach(class Iobserver* view);
	void notify();

	sf::Time get_time();
	sf::Time get_delta_time();
	v2f world_to_screen(const v2f& position);

private:
	std::vector<Iobserver*> m_views;

	sf::Clock* m_timer;
	sf::Clock* m_delta_timer;
	sf::Time m_delta_time;
};

/*
Observer Design Pattern
This is the observer interface in the observer design pattern. All classes that
implement this interface automatically update their values when the attached
subject calls the "notify" function.
*/
class Iobserver
{
public:
	Iobserver(fiziks_engine* engine) {
		if (m_engine == NULL) {
			m_engine = engine;
		}
		m_engine->attach(this);
	}
	~Iobserver() { }

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
	aa_bounds* get_bounds() { return m_bounds; }

protected:
	aa_bounds* m_bounds;
	fiziks_engine* get_engine() { return m_engine; }

private:
	fiziks_engine* m_engine;
};

// Included after Iobserver to avoid building from an incomplete type
#include "k_entity.h"

#endif // !FIZIKS_ENGINE_H