#pragma once
#include "Vec2d.h"

namespace Chorus {
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
}