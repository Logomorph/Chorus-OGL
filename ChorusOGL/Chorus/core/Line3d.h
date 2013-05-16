#pragma once
#include "Vec3d.h"

namespace Chorus {
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
}