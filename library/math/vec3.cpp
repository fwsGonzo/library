#include <library/math/vector.hpp>

#include <library/log.hpp>
#include <cmath>

namespace library
{
	static const double PI = 4 * std::atan(1);
	static const double MIN_V3 = 1e-7;
	
	// vec3 swizzles
	vec2 vec3::xx() const
	{
		return vec2(x, x);
	}
	vec2 vec3::yy() const
	{
		return vec2(y, y);
	}
	vec2 vec3::zz() const
	{
		return vec2(z, z);
	}
	vec2 vec3::xy() const
	{
		return vec2(x, y);
	}
	vec2 vec3::yz() const
	{
		return vec2(y, z);
	}
	vec2 vec3::xz() const
	{
		return vec2(x, z);
	}
	
	// vec3 utility
	vec3::vector_t vec3::length() const
	{
		return std::sqrt(length_squared());
	}
	
	vec3& vec3::normalize()
	{
		vector_t L = length();
		if (L == 0) return *this;
		// normalize to unit length vector
		L = 1.0 / L;
		return *this *= L;
	}
	vec3 vec3::normalized() const
	{
		return vec3(*this).normalize();
	}
	
	vec3::vector_t vec3::dot(const vec3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	
	vec3 vec3::cross(const vec3& v) const
	{
		return vec3
		(
			(y * v.z) - (v.y * z),
			(z * v.x) - (v.z * x),
			(x * v.y) - (v.x * y)
		);
	}
	
	vec3 vec3::frac() const
	{
		// FIXME: does not work for negative numbers
		return vec3( x - (int)x, y - (int)y, z - (int)z );
	}
	
	vec3 vec3::reflect(const vec3& normal) const
	{
		// incident - 2.0 * dot(normal, incident) * normal
		return *this - vec3(normal) * 2.0f * dot(normal);
	}
	
	vec3 vec3::axis(const vec3& v) const
	{
		return -(cross(v).cross(v)).normalize();
	}
	
	vec3 vec3::project(const vec3& v) const
	{
		return v * (*this * v) / (v * v);
	}
	
	// linear interpolation
	vec3 vec3::mix(const vec3& v, vector_t mixlevel) const
	{
		return vec3(
			this->x * (1.0 - mixlevel) + v.x * mixlevel,
			this->y * (1.0 - mixlevel) + v.y * mixlevel,
			this->z * (1.0 - mixlevel) + v.z * mixlevel
		);
	}
	
	// rotate vector around axis angle - axis vector, angle is theta (in radians),
	// 'this' is the vector we are going to rotate
	vec3 vec3::rotateOnAxis(const vec3& axis, vector_t angle) const
	{
		// formula: vector * cos a + dot(vector, axis) * axis * (1 - cos a) + cross(axis, vector) * sin a
		return
			*this * std::cos(angle) + 
			this->dot(axis) * axis * (1.0 - std::cos(angle)) + 
			axis.cross(*this) * std::sin(angle);
	}
	
	vec2 vec3::toPitchYaw() const
	{
		vector_t xzdist = xz().length();
		// pitch
		vector_t pitch = -atan2(y, xzdist);
		
		// yaw
		float yaw = atan2(x, -z);
		if (yaw < 0) yaw += PI * 2;
		
		return vec2(pitch, yaw);
	}
	
	// unary - (negate)
	vec3 vec3::operator - () const
	{
		return vec3(-x, -y, -z);
	}
	
	// arithmetic vector-vector operators
	vec3 vec3::operator+ (const vec3& v) const
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}
	vec3 vec3::operator- (const vec3& v) const
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}
	vec3 vec3::operator* (const vec3& v) const
	{
		return vec3(x * v.x, y * v.y, z * v.z);
	}
	vec3 vec3::operator/ (const vec3& v) const
	{
		return vec3(x / v.x, y / v.y, z / v.z);
	}
	
	vec3& vec3::operator += (const vec3& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}
	vec3& vec3::operator -= (const vec3& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}
	vec3& vec3::operator *= (const vec3& v)
	{
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
		return *this;
	}
	vec3& vec3::operator /= (const vec3& v)
	{
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
		return *this;
	}
	
	// vector arithmetic literal operators
	vec3 vec3::operator+ (const vector_t v) const
	{
		return vec3(x + v, y + v, z + v);
	}
	vec3 vec3::operator- (const vector_t v) const
	{
		return vec3(x - v, y - v, z - v);
	}
	vec3 vec3::operator* (const vector_t v) const
	{
		return vec3(x * v, y * v, z * v);
	}
	vec3 vec3::operator/ (const vector_t v) const
	{
		return vec3(x / v, y / v, z / v);
	}
	
	// vector compound operators
	vec3& vec3::operator +=(const vector_t v)
	{
		x += v; y += v; z += v;
		return *this;
	}
	vec3& vec3::operator -=(const vector_t v)
	{
		x -= v; y -= v; z -= v;
		return *this;
	}
	vec3& vec3::operator *=(const vector_t v)
	{
		x *= v; y *= v; z *= v;
		return *this;
	}
	vec3& vec3::operator /=(const vector_t v)
	{
		x /= v; y /= v; z /= v;
		return *this;
	}
	
	// exponentiate "operator"
	vec3& vec3::pow(vector_t e)
	{
		x = std::pow(x, e);
		y = std::pow(y, e);
		z = std::pow(z, e);
		return *this;
	}
	vec3& vec3::pow(const vec3& v)
	{
		x = std::pow(x, v.x);
		y = std::pow(y, v.y);
		z = std::pow(z, v.z);
		return *this;
	}
	
	// boolean equality operator
	bool vec3::operator == (const vec3& v) const
	{
		return
			std::abs(x - v.x) < MIN_V3 && 
			std::abs(y - v.y) < MIN_V3 && 
			std::abs(z - v.z) < MIN_V3;
	}
	
	// boolean inequality operator
	bool vec3::operator != (const vec3& v) const
	{
		return !(*this == v);
	}
	
	//! vec3 language functions
	/*
		http://www.opengl.org/sdk/docs/manglsl/xhtml/reflect.xml
		For a given incident vector I and surface normal N reflect returns the reflection direction calculated as
		R = I - 2.0 * dot(N, I) * N
	*/
	vec3 reflect(const vec3& I, const vec3& N)
	{
		return I - 2.0 * dot(N, I) * N;
	}
	
	/*
		http://www.opengl.org/sdk/docs/manglsl/xhtml/refract.xml
		For a given incident vector I, surface normal N and ratio of indices of refraction, eta, refract returns the refraction vector, R.
		R is calculated as:
		k = 1.0 - eta * eta * (1.0 - dot(N, I) * dot(N, I));
		if (k < 0.0)
			R = genType(0.0);       // or genDType(0.0)
		else
			R = eta * I - (eta * dot(N, I) + sqrt(k)) * N;
	*/
	vec3 refract(const vec3& I, const vec3& N, const vec3::vector_t eta)
	{
		// incident vector I, normal vector N (both normalized)
		vec3::vector_t dotNI = dot(N, I);
		
		vec3::vector_t k = 1.0 - eta * eta * (1.0 - dotNI * dotNI);
		
		if (k < 0.0) return (vec3::vector_t)0.0;
		
		return eta * I - (eta * dotNI + sqrtf(k)) * N;
	}
	
	// transforms this vector into a rotation expressed by two angles (rotX, rotY)
	vec3 lookVector(const vec2& rot)
	{
		return vec3( std::sin(rot.y) * std::cos(rot.x),
									  -std::sin(rot.x),
					-std::cos(rot.y) * std::cos(rot.x));
	}
	
	// log output functions
	
	// write vector-3 to log using format (x, y, z)
	Log& operator<< (Log& out, const vec3& v)
	{
		return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	}
	
}

// write vector-3 to cout using format (x, y, z)
std::ostream& operator<< (std::ostream& out, const library::vec3& v)
{
	return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
