#include <library/math/vector.hpp>
#include <library/math/quaternion.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <xmmintrin.h>

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
	
	std::cout << v2 << std::endl;
	
	// v3 = (1, 1, 1)
	vec3 v3(1, 1, 1);
	// verify normalized length is (almost) 1
	assert(v3.normalized().length() > 0.99999992);
	
	// validate cross product
	vec3 v3c = vec3(1, 0, 0).cross(vec3(0, 1, 0));
	assert(v3c == vec3(0, 0, 1));
	
	std::cout << v3 << std::endl;
	
	/// --- Quaternions --- ///
	
	Quaternion q(1.0, vec3(0, 0, 0));
	assert(q == Quaternion());
	
	q = Quaternion(vec3(0, 1, 0));
	
	vec3  axis;
	float angle;
	q.toAxisAngle(axis, angle);
	
	Quaternion Q(axis, angle);
	assert(q == Q);
	
	std::cout << "Math tests: OK" << std::endl;
	
	#define SSE __attribute__((aligned (16)))
	float X = 5.0;
	float Y = 4.0;
	
	__m128 tX = _mm_load1_ps(&X);
	__m128 tY = _mm_load1_ps(&Y);
	__m128 tZ = _mm_setr_ps(1, 2, 3, 4);
	
	tX = _mm_add_ps(tX, tY);
	
	std::cout << *(float*) &tX << std::endl;
	
	vec4 ssev((float*) &tX);
	
	std::cout << ssev << std::endl;
	
	tX = _mm_sqrt_ps(tX);
	
	ssev = vec4((float*) &tX);
	std::cout << ssev << std::endl;
	
	tX = _mm_add_ps(tX, tZ);
	
	ssev = vec4((float*) &tX);
	std::cout << ssev << std::endl;
}
