#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
#include "game/level/level_representation.hpp"

level_representation::level_representation(unsigned model, unsigned texture)	
	:	model_{model},
		texutre_{texture}
{
}

void level_representation::render(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texutre_);
	glCallList(model_);
	glDisable(GL_TEXTURE_2D);
}

rg::engine::game_object* level_representation::copy(void)
{
	return new level_representation(*this);	
}

rg::engine::box level_representation::box_mash(void)
{
	return rg::engine::box();
}

void level_representation::on_tick(void)
{
	transform(glm::rotate(glm::mat4(1), 0.1f, glm::vec3{0,1, 0}));
}
