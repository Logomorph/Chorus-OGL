#pragma once
#include "ChorusCore.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

namespace Chorus
{
	class Transform
	{
	public:
		Transform(void);
		Transform(const Transform &transform);

		void LerpTransform(Transform *prev, Transform *next, float percent);

		Vec2D position;
		float rotation;
		Vec2D scale;
	};
}
