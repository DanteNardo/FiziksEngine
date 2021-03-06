#include "rigidbody.h"

rigidbody::rigidbody()
{
    m_ip = v2f(0, 0);
    m_iv = v2f(0, 0);
    m_p = v2f(0, 0);
    m_v = v2f(0, 0);
    m_a = v2f(0, 0);
    m_o = 0;
	m_mat = new material(Rock);
	// TODO: Fix constructor
    m_mass = new mass_data(*m_mat, 0.0f, 0.0f);
}

rigidbody::rigidbody(v2f po, v2f ve, v2f ac, 
                     int th, float wi, float he, materials m)
{
    m_ip = po;
    m_iv = ve;
    m_p = po;
    m_v = ve;
    m_a = ac;
    m_o = th;
    m_mat = new material(m);
	// TODO: Fix constructor
	m_mass = new mass_data(*m_mat, wi, he);

	// Apply angle to initial velocity
	m_v.x *= (float)(cos(rad(m_o)));
	m_v.y *= (float)(sin(rad(m_o)));
}

rigidbody::rigidbody(v2f po, v2f ve, v2f ac, 
                     int th, float ra, materials m)
{
    m_ip = po;
    m_iv = ve;
    m_p = po;
    m_v = ve;
    m_a = ac;
    m_o = th;
    m_mat = new material(m);
	// TODO: Fix constructor
	m_mass = new mass_data(*m_mat, ra);

	// Apply angle to initial velocity
	m_v.x *= (float)(cos(rad(m_o)));
	m_v.y *= (float)(sin(rad(m_o)));
}

rigidbody::~rigidbody()
{
    safe_delete(m_mass);
    safe_delete(m_mat);
}

#pragma region Default Getters
v2f& rigidbody::ip() { return m_ip; }
v2f& rigidbody::iv() { return m_iv; }
v2f& rigidbody::p()  { return m_p; }
v2f& rigidbody::v() { return m_v; }
v2f& rigidbody::a() { return m_a; }
float rigidbody::w() { return m_w; }
int rigidbody::o() { return m_o; }
float rigidbody::im() { return m_mass->m_im; }
float rigidbody::iin() { return m_mass->m_iin; }
float rigidbody::rest() { return m_mat->m_rest; }
float rigidbody::dens() { return m_mat->m_dens; }
float rigidbody::sf() { return m_mat->m_sf; }
float rigidbody::kf() { return m_mat->m_kf; }
#pragma endregion

#pragma region Default Setters
void rigidbody::p(v2f const& p) { m_p = p; }
void rigidbody::v(v2f const& v) { m_v = v; }
void rigidbody::a(v2f const& a) { m_a = a; }
void rigidbody::w(float const& w) { m_w = w; }
void rigidbody::o(int const& o) { m_o = o; }
void rigidbody::im(float const& m) 
{ 
    m_mass->m_m = m;
    m_mass->m_im = 1 / m; 
}
void rigidbody::iin(float const& in) 
{ 
    m_mass->m_in = in;
    m_mass->m_iin = 1 / in; 
}
void rigidbody::rest(float const& rest) { m_mat->m_rest = rest; }
#pragma endregion

#pragma region Additive and Subtractive Setters
void rigidbody::p(float mod, v2f const& p) { m_p = m_p + (p * mod); }
void rigidbody::v(float mod, v2f const& v) { m_v = m_v + (v * mod); }
void rigidbody::a(float mod, v2f const& a) { m_a = m_a + (a * mod); }
void rigidbody::w(float mod, float const& w) { m_w = m_w + (w * mod); }
void rigidbody::o(float mod, int const& o) { m_o = m_o + (o * mod); }
void rigidbody::im(float mod, float const& im) 
{
    m_mass->m_m += 1 / im;
    m_mass->m_im += im * mod; 
}
void rigidbody::iin(float mod, float const& iin) 
{
    m_mass->m_in += 1 / iin;
    m_mass->m_iin += iin * mod; 
}
void rigidbody::rest(float mod, float const& rest) 
{ 
    m_mat->m_rest += rest * mod; 
}

void rigidbody::apply_impulse(const v2f & impulse, const v2f & contact)
{
	m_v += impulse * m_mass->m_im;
	//m_w += cross(contact, impulse) * m_mass->m_iin;
}
#pragma endregion