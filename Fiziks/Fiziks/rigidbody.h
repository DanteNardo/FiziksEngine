// Author: Dante Nardo
// Last Modified: 3/2/2018
// Purpose: Performs collision checking operations based on collider types.

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "math.h"

class rigidbody
{
public:
	rigidbody();
	rigidbody(v2f pos, v2f vel, v2f acc, int theta, float m);
	~rigidbody();

    // Getters
    v2f& ip();
    v2f& iv();
    v2f& p();
    v2f& v();
    v2f& a();
    int t();
    float im();

    // Setters
    void p(v2f const& p);
    void v(v2f const& v);
    void a(v2f const& a);
    void t(int const& t);
    void im(float const& im);
    
private:
    v2f m_ip;	// Initial position
	v2f m_iv;	// Initial velocity
	v2f m_p;	// Position
	v2f m_v;	// Velocity
	v2f m_a;	// Acceleration
	int m_t;	// Theta
    float m_im; // Inverse of Mass: Easier use
};

#endif // !RIGIDBODY_H