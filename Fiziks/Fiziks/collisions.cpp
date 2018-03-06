#include "collisions.h"

// Declare static instance
collisions* collisions::s_instance = nullptr;

collisions::collisions()
{
}

collisions::~collisions()
{
	safe_delete(s_instance);
}

collisions* collisions::get_instance()
{
	if (s_instance == nullptr) {
		s_instance = new collisions();
		return s_instance;
	}
	return s_instance;
}

bool collisions::check(entity& a, entity& b)
{
	// First, check shape's axis realigned bounding box (least precise)
    if (ARBB(a, b)) {

		// Second, call specific shape collision checks ie CirclevRect
		if (collisions::*shape_check[a.type()][b.type()](a, b)) {

			// Lastly, call complicated SAT check
			if (SAT(a, b)) {

				// Generate collision data (manifold) and resolve collision
				manifold m = gen_manifold(a, b);
				resolve(m);
				fix_pen(m);
				return true;
			}
		}
    }

    return false;
}

/*
Axis Realigned Bounding Box
This is an Axis Aligned Bounding Box for a rotated object. This means that the
AABB is much larger than normal to accommodate every 
*/
bool collisions::ARBB(entity& a, entity& b)
{
	return a.bounds().intersects(b.bounds());
}

/*
Separating Axis Theorem
An algorithm that asserts two objects are not colliding if a plane can be drawn
between them. It works by comparing the minimum and maximum projections from
each entity and if an entity's minimum projection is greater than another's
maximum projection then a plane cannot be created between them.
*/
bool collisions::SAT(entity& a, entity& b)
{
    #pragma region Define Object Vertices
	v2f a_points[4];
	v2f b_points[4];
	sf::FloatRect ab = a.shape()->getLocalBounds(); // For readability
	sf::FloatRect bb = b.shape()->getLocalBounds(); // For readability
	const float* a_matrix = a.shape()->getTransform().getMatrix();
	const float* b_matrix = b.shape()->getTransform().getMatrix();

	a_points[0] = v2f(ab.left, ab.top);
	a_points[1] = v2f(ab.left + ab.width, ab.top);
	a_points[2] = v2f(ab.left, ab.top + ab.height);
	a_points[3] = v2f(ab.left + ab.width, ab.top + ab.height);

	b_points[0] = v2f(bb.left, bb.top);
	b_points[1] = v2f(bb.left + bb.width, bb.top);
	b_points[2] = v2f(bb.left, bb.top + bb.height);
	b_points[3] = v2f(bb.left + bb.width, bb.top + bb.height);

	// Multiply every point by matrix values
	for (int i = 0; i < 4; i++) {
		a_points[i] = v2f(a_points[i].x * a_matrix[4 * i],
						  a_points[i].y * a_matrix[1 + (4 * i)]);
		b_points[i] = v2f(b_points[i].x * b_matrix[4 * i],
						  b_points[i].y * b_matrix[1 + (4 * i)]);
	}
	#pragma endregion

	#pragma region Calculate Normals
	std::vector<v2f> a_normals = std::vector<v2f>();
	std::vector<v2f> b_normals = std::vector<v2f>();
	a_normals.push_back(normalize(v2f(a_matrix[0], a_matrix[1])));
	a_normals.push_back(normalize(v2f(a_matrix[4], a_matrix[5])));
	a_normals.push_back(normalize(v2f(a_matrix[8], a_matrix[9])));
	b_normals.push_back(normalize(v2f(b_matrix[0], b_matrix[1])));
	b_normals.push_back(normalize(v2f(b_matrix[4], b_matrix[5])));
	b_normals.push_back(normalize(v2f(b_matrix[8], b_matrix[9])));
	#pragma endregion

	#pragma region SAT - A Normals
	for (int i = 0; i < a_normals.size(); i++) {

		// Stores the projection to save memory
		float projection;

		// Projections for A - Instantiate a_min and a_max
		float a_min = dot(a_points[0], a_normals[i]);
		float a_max = a_min;
		for (int j = 1; j < 8; j++) {
			projection = dot(a_points[j], a_normals[i]);
			a_min = (a_min > projection) ? projection : a_min;
			a_max = (a_max < projection) ? projection : a_max;
		}

		// Projections for B - Instantiate b_min and b_max
		float b_min = dot(b_points[0], a_normals[i]);
		float b_max = b_min;
		for (int k = 1; k < 8; k++) {
			projection = dot(b_points[k], a_normals[i]);
			b_min = (b_min > projection) ? projection : b_min;
			b_max = (b_max < projection) ? projection : b_max;
		}
		
		// Check for separation
		if (a_max < b_min || a_min > b_max) {
			return true;
		}
	}
	#pragma endregion

	#pragma region SAT - B Normals
	for (int i = 0; i < b_normals.size(); i++) {

		// Minimum and maximum projections
		// A = (this object) B = (a_pOther)
		float projection;

		// Projections for A - Instantiate a_min and a_max
		float a_min = dot(a_points[0], b_normals[i]);
		float a_max = a_min;
		for (int j = 1; j < 8; j++) {
			projection = dot(a_points[j], b_normals[i]);
			a_min = (a_min > projection) ? projection : a_min;
			a_max = (a_max < projection) ? projection : a_max;
		}

		// Projections for B - Instantiate b_min and b_max
		float b_min = dot(b_points[0], b_normals[i]);
		float b_max = b_min;
		for (int k = 1; k < 8; k++) {
			projection = dot(b_points[k], b_normals[i]);
			b_min = (b_min > projection) ? projection : b_min;
			b_max = (b_max < projection) ? projection : b_max;
		}

		// Check for separation
		if (a_max < b_min || a_min > b_max) {
			return true;
		}
	}
	#pragma endregion

	// DEFAULT RETURN
	return false;
}

#pragma region Shape Checking
bool collisions::c_rr(entity& a, entity& b)
{
	return false;
}

bool collisions::c_rc(entity& a, entity& b)
{
	return false;
}

bool collisions::c_rt(entity& a, entity& b)
{
	return false;
}

bool collisions::c_cr(entity& a, entity& b)
{
	return false;
}

bool collisions::c_cc(entity& a, entity& b)
{
	float dist = pow(b.rb()->p().x - a.rb()->p().x, 2) + 
				 pow(b.rb()->p().y - a.rb()->p().y, 2);

bool collisions::c_ct(entity& a, entity& b)
{
	return false;
}

bool collisions::c_tr(entity& a, entity& b)
{
	return false;
}

bool collisions::c_tc(entity& a, entity& b)
{
	return false;
}

bool collisions::c_tt(entity& a, entity& b)
{
	return false;
}
#pragma endregion

manifold collisions::gen_manifold(entity& a, entity& b)
{
	return manifold(&a, &b, pen(a, b), norm(a, b));
}

v2f collisions::norm(const entity& a, const entity& b)
{

}

float collisions::tot_mass(entity& a, entity& b)
{
	return a.rb()->im() + b.rb()->im();
}

float collisions::pen(entity& a, entity& b)
{
	
}

void collisions::resolve(const manifold& m)
{
	// Save pointers for cleaner code
	entity* a = m.m_a;
	entity* b = m.m_b;

	// Compute the normalized relative velocity of both objects
	v2f rel_v = b->rb()->v() - a->rb()->v();
	float n_vel = dot(rel_v, m.m_norm);

	// If there is a collision but objects are moving away, don't stop them
	if (n_vel > 0) return;

	// Calculate restitution (bouncyness, elasticity)
	float e = std::min(a->rb()->rest(), b->rb()->rest());

	// Calculate impulse magnitude
	float j = -(1 + e) * n_vel;
	j /= tot_mass(*a, *b);

	// Apply impulse
	v2f impulse = j * m.m_norm;
	a->rb()->v(-1.0f, a->rb()->im() * impulse);
	b->rb()->v(1.0f, b->rb()->im() * impulse);

	// Recalculate relative velocity post impulse
	rel_v = b->rb()->v() - a->rb()->v();

	// Solve for the tangent to the normal (for friction)
	v2f tang = normalize(rel_v - dot(rel_v, m.m_norm) * m.m_norm);

	// Solve for friction magnitude
	float f = -dot(rel_v, tang);
	f = f / tot_mass(*a, *b);

	// Approximate mu given both object's static coefficients
	float mu = pythag(a->rb()->sf(), b->rb()->sf());

	// Coulomb's Law:
	// Force of Friction <= friction coefficient * normal force
	// This prevents friction from being greater than the normal force
	v2f f_impulse;

	// Static friction
	if (abs(f) < j * mu) {
		f_impulse = f * tang;
	}
	// Kinetic friction
	// Recompute mu using kinetic coefficients instead of static
	else {
		mu = pythag(a->rb()->kf(), b->rb()->kf());
		f_impulse = mu * -j * tang;
	}

	// Apply friction impulse
	a->rb()->v(-1.0f, a->rb()->im() * f_impulse);
	b->rb()->v(1.0f, b->rb()->im() * f_impulse);
}

void collisions::fix_pen(const manifold& m)
{
	/*
	Percent (p) determines the incremental movement we make to an object in
	order to get it to move so that it's no longer penetrating.
	Slop (s) is the value at which we ignore the miniscule penetration. This is
	necessary so that objects don't "jitter" when they are touching each other.
	*/
	const float p = 0.2;
	const float s = 0.01;

	// Calculate correction amount, move a away and b away in opposite direction
	v2f correct = std::max(m.m_pen - s, 0.0f) / tot_mass(*m.m_a, *m.m_b) * p * m.m_norm;
	m.m_a->rb()->p(-1, m.m_a->rb()->im() * correct);
	m.m_b->rb()->p(1, m.m_b->rb()->im() * correct);
}