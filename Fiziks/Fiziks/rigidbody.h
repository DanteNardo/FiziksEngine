// Author: Dante Nardo
// Last Modified: 3/10/2018
// Purpose: Performs collision checking operations based on collider types.

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "math.h"

#pragma region Helper Structs
enum materials
{
    Rock, Wood, Metal, Rubber, Static
};

// Stores data relevant to an object's material type
struct material
{
    float m_rest;   // Restitution (bouncyness)
    float m_dens;   // Density
    float m_sf;     // Coefficient of Static Friction
    float m_kf;     // Coefficient of Kinetic Friction

    material(float rest, float dens, float sf, float kf) 
    { 
        m_rest = rest; 
        m_dens = dens;
        m_sf = sf;
        m_kf = kf;
    }

    material(materials m_type)
    {
        switch (m_type) {
            case Rock:   
                m_dens = 0.6f; m_rest = 0.1f; 
                m_sf = 0.6; m_kf = 0.48; 
                break;
            case Wood:   
                m_dens = 0.3f; m_rest = 0.2f; 
                m_sf = 0.4; m_kf = 0.2; 
                break;
            case Metal:  
                m_dens = 1.2f; m_rest = 0.05f; 
                m_sf = 0.74; m_kf = 0.57; 
                break;
            case Rubber: 
                m_dens = 0.3f; m_rest = 0.8f; 
                m_sf = 1.0; m_kf = 0.8; 
                break;
            case Static: 
                m_dens = 0.0f; m_rest = 0.4f; 
                m_sf = 1.0; m_kf = 1.0; 
                break;
        }
    }
};

// Stores mass, inertia, and their inverses
struct mass_data
{
	float m_m;      // Mass
	float m_im;     // Inverse mass
	float m_in;     // Inertia
	float m_iin;    // Inverse inertia

	// Rectangle & Triangle
	mass_data(material& mat, float width, float height, float mod = 1.0f)
	{
		m_m = mat.m_dens * width * height;
		// TODO: Calculate moment of inertia

		// Calculate inverse mass and inertia, don't divide 0
		m_m != 0 ? m_im = 1 / m_m : m_im = 0;
		m_in != 0 ? m_iin = 1 / m_in : m_iin = 0;
	}

	// Circle
	mass_data(material& mat, float radius)
	{
		m_m = mat.m_dens * PI * pow(radius, 2);
		// TODO: Calculate moment of inertia

		// Calculate inverse mass and inertia, don't divide 0
		m_m != 0 ? m_im = 1 / m_m : m_im = 0;
		m_in != 0 ? m_iin = 1 / m_in : m_iin = 0;
	}
};
#pragma endregion

class rigidbody
{
public:
	rigidbody();
	rigidbody(v2f po, v2f ve, v2f ac, 
              int o, float wi, float he, materials m);
	rigidbody(v2f po, v2f ve, v2f ac, 
              int o, float ra, materials m);
	~rigidbody();

    #pragma region Getters and Setters
    // Getters
    v2f& ip();
    v2f& iv();
    v2f& p();
    v2f& v();
    v2f& a();
    v2f& f();
	float w();
    int o();
    float im();
    float iin();
    float rest();
    float dens();
    float sf();
    float kf();

    // Setters
    void p(v2f const& p);
    void v(v2f const& v);
    void a(v2f const& a);
	void w(float const& w);
    void o(int const& o);
    void im(float const& m);
    void iin(float const& in);
    void rest(float const& rest);

    // Additive and Subtractive Setters
    // Either 1.0f or -1.0f is passed in to clean up code
    void p(float mod, v2f const& p);
    void v(float mod, v2f const& v);
    void a(float mod, v2f const& a);
	void w(float mod, float const& w);
    void o(float mod, int const& o);
    void im(float mod, float const& im);
    void iin(float mod, float const& iin);
    void rest(float mod, float const& rest);
    #pragma endregion

	void apply_impulse(const v2f& impulse, const v2f& contact);
    
private:
    v2f m_ip;	        // Initial position
	v2f m_iv;	        // Initial velocity
	v2f m_p;	        // Position
	v2f m_v;	        // Linear Velocity
	v2f m_a;	        // Acceleration
    v2f m_f;            // Net force
	float m_w;			// Angular Velocity
	v2f m_t;			// Net torque
	int m_o;	        // Theta - orientation
    mass_data* m_mass;  // Mass data: contains mass, inertia, and inverses
    material* m_mat;    // Material: contains density and restitution
};

#endif // !RIGIDBODY_H