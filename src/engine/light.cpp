#include "engine/light.hpp"

namespace rg
{
namespace engine
{
	const std::array<GLenum, 8> light::lights_id_{{GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7}};

	light::light(	const glm::vec4& pos, const rg::engine::color& ambient, 
					const rg::engine::color& diffuse, 
					const rg::engine::color& spectar)
		:	pos_(pos),
			colors_{{ambient, diffuse, spectar}},
			id_(uuids::random_id()),
			on_{true}
			
	{}


	light::light(const light& l)
		:	pos_(l.pos_),
			colors_(l.colors_),
			id_(uuids::random_id()),
			on_{l.on_}
	{}

	void light::turn_on(void)
	{
		on_ = true;
	}

	void light::turn_off(void)
	{
		on_ = false;
	}

	void light::apply(int id)
	{
		if(id < 0 || id > 7)
			return ;

		float pos[]{pos_[0], pos_[1], pos_[2], pos_[3]};
		float color0[]{colors_[0].red(), colors_[0].green(), colors_[0].blue()};
		float color1[]{colors_[1].red(), colors_[1].green(), colors_[1].blue()};
		float color2[]{colors_[2].red(), colors_[2].green(), colors_[2].blue()};

		glLightfv(lights_id_[id], GL_POSITION, pos);
		glLightfv(lights_id_[id], GL_AMBIENT, color0);
		glLightfv(lights_id_[id], GL_DIFFUSE, color1);
		glLightfv(lights_id_[id], GL_SPECULAR,color2);
	}
}
}
