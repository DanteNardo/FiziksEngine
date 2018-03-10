// Dante Nardo
// Last Modified: 3/10/2018
// Purpose: Runs the physics simulation.

#ifndef FIZIKS_ENGINE_H
#define FIZIKS_ENGINE_H

#include <sstream>
#include <vector>
#include "math.h"

/*
Observer Design Pattern
This is the subject in the observer design pattern. All classes that implement
the Iobserver interface have a reference to this subject and are notified by
the subject when the values change.
*/
class fiziks_engine
{
public:
    fiziks_engine(sf::RenderWindow* window);
    ~fiziks_engine();

    void update();
    void draw(sf::RenderWindow* window);

	void attach(class Iobserver* view);
	void notify();

	float get_time();
	float get_delta_time();

private:
	class quad_node* m_q_root;
	std::vector<Iobserver*> m_views;

	sf::Clock* m_timer;
	sf::Clock* m_delta_timer;
	float m_delta_time;
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

protected:
	fiziks_engine* get_engine() { return m_engine; }

private:
	fiziks_engine* m_engine;
};

class entity;

#include "quad_node.h"

#endif // !FIZIKS_ENGINE_H