#include <math/vector.hpp>
#include <log.hpp>
#include <cassert>
#include <cmath>

using namespace library;

const double PI = 4 * atan(1);

void test_maths()
{
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
	logger << Log::INFO << v2 << Log::ENDL;
	assert(v2 == vec2(0, 1));
	
}