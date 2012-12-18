#pragma once
#include "types.h"

namespace Chorus {
	/// A 2D column vector with 3 elements.
	typedef struct Vec3D
	{
		/// Default constructor does nothing (for performance).
		Vec3D() : x(0), y(0), z(0) {}

		/// Construct using coordinates.
		Vec3D(float32 x, float32 y, float32 z) : x(x), y(y), z(z) {}

		/// Set this vector to all zeros.
		void SetZero() { x = 0.0f; y = 0.0f; z = 0.0f; }

		/// Set this vector to some specified coordinates.
		void Set(float32 x_, float32 y_, float32 z_) { x = x_; y = y_; z = z_; }

		/// Negate this vector.
		Vec3D operator -() const { Vec3D v; v.Set(-x, -y, -z); return v; }

		/// Add a vector to this vector.
		void operator += (const Vec3D& v)
		{
			x += v.x; y += v.y; z += v.z;
		}

		/// Add a vector to this vector.
		Vec3D operator + (const Vec3D& v)
		{
			return Vec3D(x+v.x,y+v.y,z+v.z);
		}

		/// Subtract a vector from this vector.
		void operator -= (const Vec3D& v)
		{
			x -= v.x; y -= v.y; z -= v.z;
		}

		/// Subtract a vector from this vector.
		Vec3D operator - (const Vec3D& v)
		{
			return Vec3D(x-v.x,y-v.y,z-v.z);
		}

		///Compare with another vector
		bool operator == (const Vec3D& v)
		{
			return (x==v.x && y==v.y && z==v.z);
		}
		/// Multiply this vector by a scalar.
		void operator *= (float32 s)
		{
			x *= s; y *= s; z *= s;
		}

		/// Multiply this vector by a scalar.
		Vec3D operator * (float32 s)
		{
			return Vec3D(x*s,y*s,z*s);
		}

		/// Divide this vector by a scalar.
		Vec3D operator / (float32 s)
		{
			return Vec3D(x/s,y/s,z/s);
		}

		/// Get the length of this vector (the norm).
		float32 Length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		/// Get the length squared. For performance, use this instead of
		/// b2Vec2::Length (if possible).
		float32 LengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		/// Convert this vector into a unit vector. Returns the length.
		float32 Normalize()
		{
			float32 length = Length();
			if (length < chEpsilon)
			{
				return 0.0f;
			}
			float32 invLength = 1.0f / length;
			x *= invLength;
			y *= invLength;
			z *= invLength;

			return length;
		}

		bool isZero()
		{
			if(x==0 && y==0 && z==0)
				return true;
			return false;
		}

		static float dotProduct(const Vec3D &v1,  const Vec3D &v2 )
		{
			return( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z  );
		}

		float32 x, y, z;
	}Vec3D;

}