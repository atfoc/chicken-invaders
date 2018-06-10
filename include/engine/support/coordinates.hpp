#ifndef COORDINATES_HPP_GIBYLZQR
#define COORDINATES_HPP_GIBYLZQR
#include <glm/matrix.hpp>

/*XXX failed test of tranformation ndc to world coordinates*/
namespace rg
{
namespace engine
{
	glm::dmat4 model_view_matrix(void);
	glm::dmat4 projection_matrix(void);
	glm::vec3 ndc_to_world(const glm::vec3& ndc_vec);
}
}
#endif /* end of include guard: COORDINATES_HPP_GIBYLZQR */
