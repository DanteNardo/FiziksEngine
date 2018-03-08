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
	// Check shape's axis realigned bounding box (least precise)
    if (ARBB(a, b)) {

		// Call complicated SAT check (most precise and intensive)
		if (SAT(a, b)) {

			// TODO: Remove when not debugging
			a.shape()->setFillColor(sf::Color::Red);
			b.shape()->setFillColor(sf::Color::Red);

			// Generate collision data (manifold) and resolve collision
			manifold m = gen_manifold(a, b);
			resolve(m);
			//fix_pen(m);
			return true;
		}
    }

	// TODO: Remove when not debugging
	a.shape()->setFillColor(sf::Color::Green);
	b.shape()->setFillColor(sf::Color::Green);

    return false;
}

/*
Generates all of the normals for an entity's shape.
*/
std::vector<v2f> collisions::gen_norms(entity& e)
{
	// Define variables
	std::vector<v2f> normals;
	sf::Transform t = sf::Transform();
	t.rotate(e.shape()->getRotation());

	// Iterate through all of the convex shape's points
	for (int i = 0; i < e.shape()->getPointCount(); i++) {

		// Find next index
		int next = i + 1 < e.shape()->getPointCount() ? i + 1 : 0;

		// Two vertices form an edge
		v2f u = v2f(e.shape()->getPoint(i));
		v2f v = v2f(e.shape()->getPoint(next));
		v2f edge = v - u;

		// Create normal
		v2f n = v2f(edge.y, -edge.x);

		// Push final result to array
		v2f n1 = normalize(n);
		normals.push_back(normalize(e.shape()->getTransform().transformPoint(normalize(n))));

		// DEBUGGING
		const float* m = t.getMatrix();
		for (int j = 0; j < 16; j++) {
			float test1 = m[j];
		}
	}

	return normals;
}

/*
Gets the minimum and maximum projection of an entity's points on an axis.
*/
v2f collisions::projection(v2fs& points, v2f axis)
{
	// Initialize values
	float projection;
	float a_min = dot(points[0], axis);
	float a_max = a_min;

	// Iterate through all points for the axis
	for (int j = 1; j < points.size(); j++) {

		// Find the largest and small projection
		projection = dot(points[j], axis);
		a_min = (a_min > projection) ? projection : a_min;
		a_max = (a_max < projection) ? projection : a_max;
	}

	return v2f(a_min, a_max);
}

/*
Axis Realigned Bounding Box
This is an Axis Aligned Bounding Box for a rotated object. This means that the
AABB is much larger than normal to accommodate every point after the rotation.
This is a simple and fast collision checking method, but imprecise.
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
    #pragma region Setup Points and Normals
	v2fs a_points = v2fs();
	v2fs b_points = v2fs();

	for (int i = 0; i < a.shape()->getPointCount(); i++) {
		a_points.push_back(a.shape()->getPoint(i));
	}
	for (int j = 0; j < b.shape()->getPointCount(); j++) {
		b_points.push_back(b.shape()->getPoint(j));
	}

	v2fs a_normals = gen_norms(a);
	v2fs b_normals = gen_norms(b);
	#pragma endregion

	#pragma region SAT - A Normals
	for (int i = 0; i < a_normals.size(); i++) {

		v2f a_proj = projection(a_points, a_normals[i]); // x = min, y =  max
		v2f b_proj = projection(b_points, a_normals[i]); // x = min, y =  max
		
		// Check for separation
		if (a_proj.y < b_proj.x || a_proj.x > b_proj.y) {
			return true;
		}
	}
	#pragma endregion

	#pragma region SAT - B Normals
	for (int i = 0; i < b_normals.size(); i++) {

		v2f a_proj = projection(a_points, b_normals[i]); // x = min, y =  max
		v2f b_proj = projection(b_points, b_normals[i]); // x = min, y =  max

		// Check for separation
		if (a_proj.y < b_proj.x || a_proj.x > b_proj.y) {
			return true;
		}
	}
	#pragma endregion

	// DEFAULT RETURN
	return false;
}

manifold collisions::gen_manifold(entity& a, entity& b)
{
	v2f n = norm(a, b);
	return manifold(&a, &b, pen(n), normalize(n));
}

/*
Finds the closest vertex point a has to b's center.
*/
v2f collisions::closest(entity& a, entity& b)
{
	v2f dist;
	v2f low = v2f(0,0);
	int index = 0;
	for (int i = 0; i < a.shape()->getPointCount(); i++) {
		dist = a.shape()->getPoint(i) - b.center();
		if (low.x == 0 && low.y == 0) {
			low = dist;
			index = i;
		}
		else if (pythag(low.x, low.y) > pythag(dist.x, dist.y)) {
			low = dist;
			index = i;
		}
	}

	return a.shape()->getPoint(index);
}

/*
Finds the collision normal.
*/
v2f collisions::norm(entity& a, entity& b)
{
	return a.center() - closest(a, b);
}

/*
Calculates the total mass.
*/
float collisions::t_m(entity& a, entity& b)
{
	return a.rb()->im() + b.rb()->im();
}

/*
Calculates the penetration depth.
*/
float collisions::pen(v2f norm)
{
	return pythag(norm.x, norm.y);
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
	j /= t_m(*a, *b);

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
	f = f / t_m(*a, *b);

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
	//a->rb()->v(-1.0f, a->rb()->im() * f_impulse);
	//b->rb()->v(1.0f, b->rb()->im() * f_impulse);
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
	v2f c = std::max(m.m_pen - s, 0.0f) / t_m(*m.m_a, *m.m_b)* p * m.m_norm;
	m.m_a->rb()->p(-1, m.m_a->rb()->im() * c);
	m.m_b->rb()->p(1, m.m_b->rb()->im() * c);
}