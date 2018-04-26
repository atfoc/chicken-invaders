#include <GL/gl.h>
#include <GL/glu.h>
#include "engine/perspective_camera.hpp"


namespace rg
{
namespace engine
{
	
	perspective_camera::perspective_camera(	const glm::vec3& eye, const glm::vec3& point,
											float fovy, float aspect, float near, float far)
		:	eye_(eye), point_(point),
			fovy_{fovy}, aspect_{aspect}, near_{near}, far_{far}
	{}
	
	void perspective_camera::apply(int w, int h)
	{
		aspect_ = static_cast<float>(w) / h;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fovy_, aspect_, near_, far_);
		glMatrixMode(GL_MODELVIEW);
		gluLookAt(	eye_[0], eye_[1], eye_[2],
					point_[0], point_[1], point_[2],
					0, 1, 0);
	}

	camera* perspective_camera::copy(void)
	{
		return new perspective_camera(*this);
	}
}
}
