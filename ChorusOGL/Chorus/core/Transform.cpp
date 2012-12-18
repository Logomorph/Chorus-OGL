#include "Transform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


namespace Chorus
{
	Transform::Transform()
		: position(Vec2D(0,0)), rotation(0.0f), scale(Vec2D(1,1))
	{
	}

	Transform::Transform(const Transform &transform)
		: position(transform.position), rotation(transform.rotation), scale(transform.scale)
	{
	}


	void Transform::LerpTransform(Transform *prev, Transform *next, float percent)
	{
		position = next->position*percent + prev->position*(1.0f - percent);
		rotation = next->rotation*percent + prev->rotation*(1.0f - percent);
		scale = next->scale*percent + prev->scale*(1.0f-percent);
	}
}
