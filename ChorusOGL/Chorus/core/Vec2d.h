#pragma once
#include "Types.h"

namespace Chorus {

	/// A 2D column vector.
	typedef struct Vec2D
	{
		/// Default constructor does nothing (for performance).
		Vec2D() : x(0), y(0) {}

		/// Construct using coordinates.
		Vec2D(float32 x, float32 y) : x(x), y(y) {}

		/// Set this vector to all zeros.
		void SetZero() { x = 0.0f; y = 0.0f; }

		/// Set this vector to some specified coordinates.
		void Set(float32 x_, float32 y_) { x = x_; y = y_; }

		/// Negate this vector.
		Vec2D operator -() const { Vec2D v; v.Set(-x, -y); return v; }

		/// Read from and indexed element.
		float32 operator () (int32 i) const
		{
			return (&x)[i];
		}

		/// Write to an indexed element.
		float32& operator () (int32 i)
		{
			return (&x)[i];
		}

		/// Add a vector to this vector.
		Vec2D operator + (const Vec2D& v)
		{
			return Vec2D(x + v.x,y+ v.y);
		}

		/// Add a vector to this vector.
		void operator += (const Vec2D& v)
		{
			x += v.x; y += v.y;
		}

		/// Subtract a vector from this vector.
		void operator -= (const Vec2D& v)
		{
			x -= v.x; y -= v.y;
		}

		/// Subtract a vector from this vector.
		Vec2D operator - (const Vec2D& v)
		{
			return Vec2D(x - v.x,y - v.y);
		}
		/// Compare with another vector
		bool operator == (const Vec2D& v)
		{
			return (x==v.x && y==v.y);
		}
		/// Multiply this vector by a scalar.
		void operator *= (float32 a)
		{
			x *= a; y *= a;
		}

		/// Multiply this vector by a scalar. right scalar multiplication
		Vec2D operator * (float32 a)
		{
			return Vec2D(x*a,y*a);
		}

		/// Get the length of this vector (the norm).
		float32 Length() const
		{
			return sqrt(x * x + y * y);
		}

		/// Get the length squared. For performance, use this instead of
		/// b2Vec2::Length (if possible).
		float32 LengthSquared() const
		{
			return x * x + y * y;
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

			return length;
		}
		float32 Distance(Vec2D v)
		{
			return sqrt(pow(x-v.x,2)+pow(y-v.y,2));
		}
		float32 DistanceSquared(Vec2D v)
		{
			return pow(x-v.x,2)+pow(y-v.y,2);
		}

		bool isZero()
		{
			if(x==0 && y==0)
				return true;
			return false;
		}

		/// Does this vector contain finite coordinates?
		/*bool IsValid() const
		{
		return b2IsValid(x) && b2IsValid(y);
		}*/

		float32 x, y;
	}Vec2D;
}