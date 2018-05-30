#include <iostream>
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include "engine/support/coordinates.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"

namespace rg
{
namespace engine
{
	glm::dmat4 model_view_matrix(void)
	{
		double mat[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, mat);
		
		return glm::make_mat4(mat);
	}

	glm::dmat4 projection_matrix(void)
	{
		double mat[16];
		glGetDoublev(GL_PROJECTION_MATRIX, mat);

		return glm::make_mat4(mat);
	}

	glm::vec3 ndc_to_world(const glm::vec3& ndc_vec)
	{
		glm::dmat4 mv(model_view_matrix());
		glm::dmat4 pr(projection_matrix());
		
		/*mv  and pr have dont have inverse idk why determinant is 0*/
		mv = glm::inverse(mv);
		pr = glm::inverse(pr);
		return mv*pr*glm::vec4{ndc_vec.x, ndc_vec.y, ndc_vec.z, 1};
	}
}
}
