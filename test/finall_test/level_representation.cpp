#include <glm/gtc/matrix_transform.hpp>
#include "level_representation.hpp"
#include "cube.hpp"

level_representation::level_representation(bool rotate, bool color)	
	:	rotate_{rotate},
		color_{color},
		c_("#ff0000"),
		selected_{false}
{

}
level_representation::level_representation(const level_representation& l)
	:	game_object(l),
		rotate_{l.rotate_},
		color_{l.color_},
		c_(l.c_),
		selected_{l.selected_}
{
}

void level_representation::render(void)
{
	cube c(1,1,1,c_);

	c.frame(selected_);
	c.render();

}

rg::engine::game_object* level_representation::copy(void)
{
	return new level_representation(*this);	
}

rg::engine::box level_representation::box_mash(void)
{
	return rg::engine::box();
}


rg::engine::color gen_random_color(void);

void level_representation::on_tick(void)
{
	if(color_)
	{
		c_ = gen_random_color();		
	}
	if(rotate_)
	{
		transform(glm::rotate(glm::mat4(1), 0.1f, glm::vec3{0,1, 0}));
	}
}



void level_representation::selected(bool val)
{
	selected_ = val;
}


