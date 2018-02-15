#include "collisions.h"

collisions::collisions()
{
}

collisions::~collisions()
{
}

bool collisions::check(entity& a, entity& b)
{
    if (OBB(a, b)) {
        if (SAT(a, b)) {
            return true;
        }
    }

    return false;
}

bool collisions::OBB(entity& a, entity& b)
{
	return a.get_sprite()->getGlobalBounds().intersects(
		   b.get_sprite()->getGlobalBounds());
}

bool collisions::SAT(entity& a, entity& b)
{
    // TODO: REMOVE THIS
    return false;

	// TODO: GET CORRECT BOUNDS
    // Get the vertex points for computation
	v2f a_points[4];
	v2f b_points[4];
	sf::FloatRect ab = a.get_sprite()->getGlobalBounds(); // For readability
	sf::FloatRect bb = b.get_sprite()->getGlobalBounds(); // For readability

	a_points[0] = v2f(ab.left, ab.top);
	a_points[1] = v2f(ab.left + ab.width, ab.top);
	a_points[2] = v2f(ab.left, ab.top + ab.height);
	a_points[3] = v2f(ab.left + ab.width, ab.top + ab.height);

	b_points[0] = v2f(bb.left, bb.top);
	b_points[1] = v2f(bb.left + bb.width, bb.top);
	b_points[2] = v2f(bb.left, bb.top + bb.height);
	b_points[3] = v2f(bb.left + bb.width, bb.top + bb.height);

    // Calculate the normals
	
}