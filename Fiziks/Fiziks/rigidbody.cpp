#include "rigidbody.h"

rigidbody::rigidbody()
{
    m_ip = v2f(0, 0);
    m_iv = v2f(0, 0);
    m_p = v2f(0, 0);
    m_v = v2f(0, 0);
    m_a = v2f(0, 0);
    m_t = 0;
}

rigidbody::rigidbody(v2f pos, v2f vel, v2f acc, int theta)
{
    m_ip = pos;
    m_iv = vel;
    m_p = pos;
    m_v = vel;
    m_a = acc;
    m_t = theta;

	// Apply angle to initial velocity
	m_v.x *= (float)(cos(rad(m_t)));
	m_v.y *= (float)(sin(rad(m_t)));
}

rigidbody::~rigidbody()
{
}

// Getters
v2f& rigidbody::ip() { return m_ip; }
v2f& rigidbody::iv() { return m_iv; }
v2f& rigidbody::p()  { return m_p; }
v2f& rigidbody::v() { return m_v; }
v2f& rigidbody::a() { return m_a; }
int rigidbody::t() { return m_t; }

// Setters
void rigidbody::p(v2f const& p) { m_p = p; }
void rigidbody::v(v2f const& v) { m_v = v; }
void rigidbody::a(v2f const& a) { m_a = a; }
void rigidbody::t(int const& t) { m_t = t; }