#ifndef LIGHT_HPP_BMZ3QNFP
#define LIGHT_HPP_BMZ3QNFP

#include <GL/gl.h>
#include <array>
#include <glm/vec4.hpp>
#include "engine/color.hpp"

namespace rg 
{
namespace engine
{
	class light
	{
		public:
			light(	const glm::vec4& pos, const rg::engine::color& ambient = rg::engine::color(0.3f, 0.3f, 0.3f), 
					const rg::engine::color& diffuse = rg::engine::color(0.6f, 0.6f, 0.6f), 
					const rg::engine::color& spectar = rg::engine::color(0.9f, 0.9f, 0.9f));
			light(const light& l);

			inline const glm::vec4& position(void);
			inline void position(const glm::vec4& pos);

			inline const std::array<rg::engine::color, 3>& color(void);
			inline void color(int id, const rg::engine::color& c);

			void turn_on(int id);
			void turn_off(int id);
			void apply(int id);
		private:
			const static std::array<GLenum, 8> lights_id_;
			glm::vec4 pos_;
			std::array<rg::engine::color, 3> colors_;
	};

	inline const glm::vec4& light::position(void)
	{
		return pos_;
	}

	inline void light::position(const glm::vec4& pos)
	{
		pos_ = pos;
	}

	inline const std::array<rg::engine::color,3>& light::color(void)
	{
		return colors_;

	}

	inline void light::color(int id, const rg::engine::color& c)
	{
		if(0 < id || id > 2)
			return ;
		colors_[id] = c;
	}
}
}

#endif /* end of include guard: LIGHT_HPP_BMZ3QNFP */
