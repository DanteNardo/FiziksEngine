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
	sf::FloatRect ab = a.get_sprite()->getLocalBounds(); // For readability
	sf::FloatRect bb = b.get_sprite()->getLocalBounds(); // For readability
	const float* a_matrix = a.get_sprite()->getTransform().getMatrix();
	const float* b_matrix = b.get_sprite()->getTransform().getMatrix();

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