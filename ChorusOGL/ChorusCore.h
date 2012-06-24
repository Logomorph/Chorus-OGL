#pragma once
#include <cmath>
#include <cfloat>
#include <cstddef>
#include <limits>

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

namespace Chorus
{

	typedef signed char	int8;
	typedef signed short int16;
	typedef signed int int32;
	typedef unsigned char uint8;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef float float32;


#define	chMaxFloat		FLT_MAX
#define	chEpsilon		FLT_EPSILON
#define chPi			3.14159265359f


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

    typedef struct Line2D
    {
      Line2D() : end1(Vec2D()), end2(Vec2D()) {}

      /// Construct using coordinates.
      Line2D(Vec2D e1, Vec2D e2) : end1(e1), end2(e2) {}

      ///Compare with another line
      bool operator == (const Line2D& v)
      {
        return (end1==v.end1 && end2==v.end2);
      }

      Vec2D end1,end2;
    }Line2D;

    typedef struct Line3D
    {
      Line3D() : end1(Vec3D()), end2(Vec3D()) {}

      /// Construct using coordinates.
      Line3D(Vec3D e1, Vec3D e2) : end1(e1), end2(e2) {}

      ///Compare with another line
      bool operator == (const Line3D& v)
      {
        return (end1==v.end1 && end2==v.end2);
      }

      Vec3D end1,end2;
    }Line3D;

    typedef struct Rectangle2D
    {
      Rectangle2D() : origin(Vec2D()), width(0), height(0) {}

      Rectangle2D(float32 x,float32 y, float32 w, float32 h) : origin(Vec2D(x,y)), width(w), height(h) {}

      Vec2D origin;
      float32 width,height;
    }Rectangle2D;

}