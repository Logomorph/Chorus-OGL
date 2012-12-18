#pragma once
#include "vec2d.h"

namespace Chorus {
	typedef struct Rectangle2D
	{
		Rectangle2D() : origin(Vec2D()), width(0), height(0) {}

		Rectangle2D(float32 x,float32 y, float32 w, float32 h) : origin(Vec2D(x,y)), width(w), height(h) {}

		Vec2D origin;
		float32 width,height;
	}Rectangle2D;
}