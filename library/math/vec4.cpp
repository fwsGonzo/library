#include <library/math/vector.hpp>

#include <library/log.hpp>
#include <cmath>

namespace library
{
	// 4-vector operators
	
	
	// log output functions
	
	// write vector-4 to log using format (x, y, z, w)
	Log& operator<< (Log& out, const vec4& v)
	{
		return out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	}
	
}

// write vector-4 to cout using format (x, y, z, w)
std::ostream& operator<< (std::ostream& out, const library::vec4& v)
{
	return out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}
