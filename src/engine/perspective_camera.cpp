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
	
	void perspective_camera::apply(void)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fovy_, aspect_, near_, far_);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(	eye_[0], eye_[1], eye_[3],
					point_[0], point_[1], point_[3],
					0, 1, 0);
	}
}
}
