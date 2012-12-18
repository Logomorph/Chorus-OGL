#include "Camera2D.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace Chorus
{
	Camera2D::Camera2D(const Camera2D& camera) : Transform(camera)
	{

	}

	Camera2D::Camera2D() : Transform()
	{


	}

	void Camera2D::ApplyMatrix()
	{
		//glPushMatrix();
		glScalef(scale.x,scale.y,1.0f);
		glTranslatef((position).x,(position * -1.0f).y,0.0f);
		glRotatef(rotation, 0, 0, 1);
		//glPopMatrix();
	}
}