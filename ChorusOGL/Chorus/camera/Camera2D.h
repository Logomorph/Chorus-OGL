#pragma once
#include "../core/ChorusCore.h"
#include "../Chorus.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

namespace Chorus
{
	class Camera2D : public Transform
	{
	public:
		Camera2D();
		Camera2D(const Camera2D& camera);

		void ApplyMatrix();
	};
}
