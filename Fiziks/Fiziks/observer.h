// Dante Nardo
// Last Modified: 2/13/2018
// Purpose: Observes all physics simulations.

#ifndef OBSERVER_H
#define OBSERVER_H

#include "fiziks_engine.h"

class fiziks_engine;
class observer
{
public:
	observer(fiziks_engine* engine); 
	~observer() { safe_delete(m_bounds); }

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
	bounds* get_bounds() { return m_bounds; }

protected:
	bounds* m_bounds;
	fiziks_engine* get_engine() { return m_engine; }

private:
	fiziks_engine* m_engine;
};

#endif // !OBSERVER_H
