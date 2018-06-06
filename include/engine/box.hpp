#ifndef BOX_HPP_EJWMLSGU
#define BOX_HPP_EJWMLSGU

#include <glm/vec4.hpp>
#include <glm/matrix.hpp>

namespace rg
{
namespace engine
{
	class box
	{
		public:
			box(float w = 0, float h = 0, const glm::vec3& pos = {0,0,0});
			box(const box& b) = default;
			box(box&& b) = default;

			inline float width(void);
			inline float height(void);
			inline glm::vec3 top_left(void);
			inline glm::vec3 top_right(void);
			inline glm::vec3 bottom_left(void);
			inline glm::vec3 bottom_right(void);


			box& operator=(const box& b) = default;
			box& operator=(box&& b) = default;
		private:
			glm::vec3 pos_;
			float w_, h_;
	};


	inline float box::width(void)
	{
		return w_;
	}

	inline float box::height(void)
	{
		return h_;
	}

	inline glm::vec3 box::top_left(void)
	{
		glm::vec3 p(pos_);
		p.x -= w_/2;
		p.z += h_/2;
		return p;
	}

	inline glm::vec3 box::top_right(void)
	{
		glm::vec3 p(pos_);
		p.x += w_/2;
		p.z += h_/2;
		return p;
	}

	inline glm::vec3 box::bottom_left(void)
	{
		glm::vec3 p(pos_);
		p.x -= w_/2;
		p.z -= h_/2;
		return p;
	}

	inline glm::vec3 box::bottom_right(void)
	{
		glm::vec3 p(pos_);
		p.x += w_/2;
		p.z -= h_/2;
		return p;

	}


	

}

}

#endif /* end of include guard: BOX_HPP_EJWMLSGU */
