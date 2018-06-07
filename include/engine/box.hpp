#ifndef BOX_HPP_EJWMLSGU
#define BOX_HPP_EJWMLSGU

#include <glm/vec4.hpp>
#include <glm/matrix.hpp>

namespace rg
{
namespace engine
{
	/**
	 * @brief	class that helps with collision detection
	 *			it is called box but it actually is a rect
	*/
	class box
	{
		public:
			/**
			 * @brief	constructor 
			 *
			 * @param w	width of a box 
			 * @param h	hight of a box
			 * @param pos	position of box
			 */
			box(float w = 0, float h = 0, const glm::vec3& pos = {0,0,0});

			/**
			 * @brief copy constructor
			 *
			 * @param b box to be copied
			 */
			box(const box& b) = default;

			/**
			 * @brief	move constructor
			 *
			 * @param b	box to be moved
			 */
			box(box&& b) = default;

			/**
			 * @brief function to get width box
			 *
			 * @return width of a box
			 */
			inline float width(void);

			/**
			 * @brief function to get height of a box
			 *
			 * @return height of a box
			 */
			inline float height(void);

			/**
			 * @brief function to get top left point of a box
			 *
			 * @return	coordinates of top left corner of a box
			 */
			inline glm::vec3 top_left(void);

			/**
			 * @brief function to get top right point of a box
			 *
			 * @return coordinates of top right corner of a box
			 */
			inline glm::vec3 top_right(void);

			/**
			 * @brief function to get bottom left point of a box
			 *
			 * @return coordinates of bottom left corner of a box
			 */
			inline glm::vec3 bottom_left(void);

			/**
			 * @brief function to get bottom right point of a box
			 *
			 * @return	coordinates of bottom right corner of a box
			 */
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
