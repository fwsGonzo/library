#include <math/vector.hpp>
#include <math/quaternion.hpp>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace library;

const double PI = 4 * atan(1);

void test_maths()
{
	/// --- Vectors --- ///
	
	vec2 v2(0, 0);
	assert(v2 == vec2(0, 0));
	assert(v2.length() == 0);
	
	v2 += 1.0;
	assert(v2 == vec2(1, 1));
	v2 *= 1.0;
	v2 /= 1.0;
	assert(v2 == vec2(1, 1));
	
	v2.y -= 1;
	assert(v2.length() == 1);
	
	// v2 = (1, 0)
	v2.rotate(PI / 2);
	assert(v2 == vec2(0, 1));
	
	// v3 = (1, 1, 1)
	vec3 v3(1, 1, 1);
	// verify normalized length is (almost) 1
	assert(v3.normalized().length() > 0.99999992);
	
	// validate cross product
	vec3 v3c = vec3(1, 0, 0).cross(vec3(0, 1, 0));
	assert(v3c == vec3(0, 0, 1));
	
	/// --- Quaternions --- ///
	
	Quaternion q(1.0, vec3(0, 0, 0));
	assert(q == Quaternion());
	
	q = Quaternion(vec3(0, 1, 0));
	
	vec3  ax;
	float angle;
	q.toAxisAngle(ax, angle);
	
	Quaternion Q = Quaternion(ax, angle);
	assert(q == Q);
	
	std::cout << "Math tests: OK" << std::endl;
}
