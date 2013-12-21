#include "vector.hpp"

#include "../log.hpp"
#include <cmath>

namespace library
{
	static const double MIN_V2 = 1e-7;
	
	// vec2 utility
	
	vec2& vec2::rotate(vector_t angle)
	{
		vector_t x = this->x;
		this->x = cos(angle) * x - sin(angle) * this->y;
		this->y = sin(angle) * x + cos(angle) * this->y;
		return *this;
	}
	vec2 vec2::rotated(vector_t angle) const
	{
		return vec2(
			cos(angle) * this->x - sin(angle) * this->y,
			sin(angle) * this->x + cos(angle) * this->y);
	}
	
	vec2::vector_t vec2::length() const
	{
		vector_t L = x * x + y * y;
		return sqrtf(L);
	}
	
	vec2 vec2::normalized() const
	{
		return vec2(*this).normalize();
	}
	
	vec2& vec2::normalize()
	{
		vector_t L = length();
		if (L == 0) return *this;
		// normalize to unit length vector
		L = 1.0 / L;
		x *= L; y *= L;
		return *this;
	}
	
	vec2::vector_t vec2::dot(const vec2& v) const
	{
		return x * v.x + y * v.y;
	}
	vec2::vector_t vec2::determinant(const vec2& v) const
	{
		return x * v.y - y * v.x;
	}
	vec2 vec2::frac() const
	{
		// FIXME: does not work for negative numbers
		return vec2(x - (int)x, y - (int)y);
	}
	vec2 vec2::reflect(const vec2& normal) const
	{
		// http://stackoverflow.com/questions/5454661/reflection-how-do-i-do-it
		return *this - 2 * dot(normal) * normal;
	}
	
	// exponentiation
	vec2& vec2::pow(double e)
	{
		this->x = powf(this->x, e);
		this->y = powf(this->y, e);
		return *this;
	}
	vec2& vec2::pow(const vec2& v)
	{
		this->x = powf(this->x, v.x);
		this->y = powf(this->y, v.y);
		return *this;
	}
	
	
	// unary - (negate)
	vec2 vec2::operator - () const
	{
		return vec2(-this->x, -this->y);
	}
	
	// arithmetic operators
	vec2& vec2::operator += (const vec2& v)
	{
		this->x += v.x; this->y += v.y;
		return *this;
	}
	vec2& vec2::operator -= (const vec2& v)
	{
		this->x -= v.x; this->y -= v.y;
		return *this;
	}
	vec2& vec2::operator *= (const vec2& v)
	{
		this->x *= v.x; this->y *= v.y;
		return *this;
	}
	vec2& vec2::operator /= (const vec2& v)
	{
		this->x /= v.x; this->y /= v.y;
		return *this;
	}
	
	vec2 vec2::operator + (const vec2& v) const
	{
		return vec2(this->x + v.x, this->y + v.y);
	}
	vec2 vec2::operator - (const vec2& v) const
	{
		return vec2(this->x - v.x, this->y - v.y);
	}
	vec2 vec2::operator * (const vec2& v) const
	{
		return vec2(this->x * v.x, this->y * v.y);
	}
	vec2 vec2::operator / (const vec2& v) const
	{
		return vec2(this->x / v.x, this->y / v.y);
	}
	
	vec2& vec2::operator +=(const vector_t f)
	{
		this->x += f; this->y += f;
		return *this;
	}
	vec2& vec2::operator -=(const vector_t f)
	{
		this->x -= f; this->y -= f;
		return *this;
	}
	vec2& vec2::operator *=(const vector_t f)
	{
		this->x *= f; this->y *= f;
		return *this;
	}
	vec2& vec2::operator /=(const vector_t f)
	{
		this->x /= f; this->y /= f;
		return *this;
	}
	
	vec2  vec2::operator + (const vector_t f) const
	{
		return vec2(this->x + f, this->y + f);
	}
	vec2  vec2::operator - (const vector_t f) const
	{
		return vec2(this->x - f, this->y - f);
	}
	vec2  vec2::operator * (const vector_t f) const
	{
		return vec2(this->x * f, this->y * f);
	}
	vec2  vec2::operator / (const vector_t f) const
	{
		return vec2(this->x / f, this->y / f);
	}
	
	// boolean equality operators
	bool vec2::operator == (const vec2& v) const
	{
		return fabs(x - v.x) < MIN_V2 && fabs(y - v.y) < MIN_V2;
	}
	bool vec2::operator != (const vec2& v) const
	{
		return !(*this == v);
	}
	
	
	// simd batch transform mat4 * vec4(vec3, 1.0) --> vec4
	void transform_vec3_simd_vec4(vec3* __restrict src, vec4* __restrict dst, unsigned int numVertices, float* __restrict matrix)
	{
		/*
		__asm intel
		{
			// Calculate the total number of iterations...
			mov ecx, [numVertices];
			shr ecx, 0x02;
			inc ecx; // ecx = totalIterations = (numVertices >> 2) + 1;
			xor esi, esi; // esi = iIter = 0;
			mov eax, [src]; // eax = &src[0];
			mov edx, [dst]; // edx = &dst[0];
			mov edi, [matrix]; // edi = &matrix[0];
	 
	_LoopStart:
			// Matrix column 0 is being loaded 2 times.
			// Matrix column 1 is being loaded 2 times.
			// Matrix column 2 is being loaded 1 time.
			// Matrix column 3 is being loaded 1 time.
			// Other that the above extra memory loads, each vector is loaded once, 
			// and there aren't any intermediate stores.
			prefetcht0 [eax + 0x100];
			movaps xmm0, [eax];            // xmm0 = (x0, y0, z0, x1)
			movaps xmm1, [edi];            // xmm1 = (m0, m1, m2, m3) << Matrix.Column[0]
			movaps xmm2, xmm0;             // xmm2 = (x0, y0, z0, x1)
			movaps xmm3, xmm0;             // xmm3 = (x0, y0, z0, x1)
			shufps xmm2, xmm2, 0x00;       // xmm2 = (x0, x0, x0, x0)
			prefetcht0 [edx + 0x80];
			shufps xmm3, xmm3, 0xFF;       // xmm3 = (x1, x1, x1, x1)
			mulps xmm2, xmm1;              // xmm2 = (x0 * m0, x0 * m1, x0 * m2, x0 * m3)
			mulps xmm3, xmm1;              // xmm3 = (x1 * m0, x1 * m1, x1 * m2, x1 * m3)
			movaps xmm4, xmm0;             // xmm4 = (x0, y0, z0, x1)
			movaps xmm1, [edi + 0x10];     // xmm1 = (m4, m5, m6, m7) << Matrix.Column[1]
			shufps xmm4, xmm4, 0x55;       // xmm4 = (y0, y0, y0, y0)
			shufps xmm0, xmm0, 0xAA;       // xmm0 = (z0, z0, z0, z0)
			mulps xmm4, xmm1;              // xmm4 = (y0 * m4, y0 * m5, y0 * m6, y0 * m7)
			movaps xmm5, [eax + 0x10];     // xmm5 = (y1, z1, x2, y2)
			addps xmm2, xmm4;              // xmm2 = (x0 * m0 + y0 * m4, x0 * m1 + y0 * m5, x0 * m2 + y0 * m6, x0 * m3 + y0 * m7)
			movaps xmm6, xmm5;             // xmm6 = (y1, z1, x2, y2)
			movaps xmm4, [edi + 0x20];     // xmm4 = (m8, m9, m10, m11) << Matrix.Column[2]
			shufps xmm6, xmm6, 0x00;       // xmm6 = (y1, y1, y1, y1)
			mulps xmm0, xmm4;              // xmm0 = (z0 * m8, z0 * m9, z0 * m10, z0 * m11)
			mulps xmm6, xmm1;              // xmm6 = (y1 * m4, y1 * m5, y1 * m6, y1 * m7)
			addps xmm0, xmm2;              // xmm0 = (x0 * m0 + y0 * m4 + z0 * m8, x0 * m1 + y0 * m5 + z0 * m9, x0 * m2 + y0 * m6 + z0 * m10, x0 * m3 + y0 * m7 + z0 * m11)
			addps xmm3, xmm6;              // xmm3 = (x1 * m0 + y1 * m4, x1 * m1 + y1 * m5, x1 * m2 + y1 * m6, x1 * m3 + y1 * m7)
			movaps xmm2, xmm5;             // xmm2 = (y1, z1, x2, y2)
			movaps xmm6, xmm5;             // xmm6 = (y1, z1, x2, y2)
			shufps xmm2, xmm2, 0x55;       // xmm2 = (z1, z1, z1, z1)
			shufps xmm6, xmm6, 0xFF;       // xmm6 = (y2, y2, y2, y2)
			mulps xmm2, xmm4;              // xmm2 = (z1 * m8, z1 * m9, z1 * m10, z1 * m11)
			mulps xmm6, xmm1;              // xmm6 = (y2 * m4, y2 * m5, y2 * m6, y2 * m7)
			addps xmm2, xmm3;              // xmm2 = (x1 * m0 + y1 * m4 + z1 * m8, x1 * m1 + y1 * m5 + z1 * m9, x1 * m2 + y1 * m6 + z1 * m10, x1 * m3 + y1 * m7 + z1 * m11)
			movaps xmm1, [edi];            // xmm1 = (m0, m1, m2, m3) << Matrix.Column[0]
			shufps xmm5, xmm5, 0xAA;       // xmm5 = (x2, x2, x2, x2)
			movaps xmm3, [eax + 0x20];     // xmm3 = (z2, x3, y3, z3)
			mulps xmm5, xmm1;              // xmm5 = (x2 * m0, x2 * m1, x2 * m2, x2 * m3)
			movaps xmm7, xmm3;             // xmm7 = (z2, x3, y3, z3)
			addps xmm6, xmm5;              // xmm6 = (x2 * m0 + y2 * m4, x2 * m1 + y2 * m5, x2 * m2 + y2 * m6, x2 * m3 + y2 * m7)
			shufps xmm7, xmm7, 0x00;       // xmm7 = (z2, z2, z2, z2)
			movaps xmm5, xmm3;             // xmm5 = (z2, x3, y3, z3)
			mulps xmm7, xmm4;              // xmm7 = (z2 * m8, z2 * m9, z2 * m10, z2 * m11)
			shufps xmm5, xmm5, 0x55;       // xmm5 = (x3, x3, x3, x3)
			addps xmm6, xmm7;              // xmm6 = (x2 * m0 + y2 * m4 + z2 * m8, x2 * m1 + y2 * m5 + z1 * m9, x2 * m2 + y2 * m6 + z2 * m10, x2 * m3 + y2 * m7 + z2 * m11)
			mulps xmm5, xmm1;              // xmm5 = (x3 * m0, x3 * m1, x3 * m2, x3 * m3)
			movaps xmm7, [edi + 0x30];     // xmm7 = (m12, m13, m14, m15) << Matrix.Column[3]
			movaps xmm1, [edi + 0x10];     // xmm1 = (m4, m5, m6, m7) << Matrix.Column[1]
			add eax, 0x30;
			addps xmm0, xmm7;              // xmm0 = d0
			addps xmm2, xmm7;              // xmm2 = d1
			addps xmm6, xmm7;              // xmm6 = d2
			addps xmm5, xmm7;              // xmm5 = (x3 * m0 + m12, x3 * m1 + m13, x3 * m2 + m14, x3 * m3 + m15)
			movaps [edx], xmm0;            // dst[i] = xmm0
			movaps xmm7, xmm3;             // xmm7 = (z2, x3, y3, z3)
			movaps [edx + 0x10], xmm2;     // dst[i + 1] = xmm2
			shufps xmm7, xmm7, 0xAA;       // xmm7 = (y3, y3, y3, y3)
			shufps xmm3, xmm3, 0xFF;       // xmm3 = (z3, z3, z3, z3)
			mulps xmm7, xmm1;              // xmm7 = (y3 * m4, y3 * m5, y3 * m6, y3 * m7)
			mulps xmm3, xmm4;              // xmm3 = (z3 * m8, z3 * m9, z3 * m10, z3 * m11)
			addps xmm5, xmm7;              // xmm5 = (x3 * m0 + y3 * m4 + m12, x3 * m1 + y3 * m5 + m13, x3 * m2 + y3 * m6 + m14, x3 * m3 + y3 * m7 + m15)
			movaps [edx + 0x20], xmm6;     // dst[i + 2] = xmm6
			addps xmm5, xmm3;              // xmm5 = d3
			add edx, 0x40;
			inc esi;
			cmp esi, ecx;
			movaps [edx - 0x10], xmm5;     // dst[i + 3] = xmm5
			jb _LoopStart;
		} // asm
		*/
	}
	
	// log output functions
	
	// write vector-2 to log using format (x, y)
	Log& operator<< (Log& out, const vec2& v)
	{
		return out << "(" << v.x << ", " << v.y << ")";
	}
	
	// write vector-2 to cout using format (x, y)
	std::ostream& operator<< (std::ostream& out, const vec2& v)
	{
		return out << "(" << v.x << ", " << v.y << ")";
	}
	
}
