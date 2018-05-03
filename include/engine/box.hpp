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
			box(float w = 0, float h = 0, float d = 0);
			box(const box& b) = default;
			box(box&& b) = default;

			inline const glm::vec4& front_lower_left(void) const;
			inline const glm::vec4& front_lower_right(void) const;
			inline const glm::vec4& front_upper_left(void) const;
			inline const glm::vec4& front_upper_right(void) const;
			inline const glm::vec4& back_lower_left(void) const;
			inline const glm::vec4& back_lower_right(void) const;
			inline const glm::vec4& back_upper_left(void) const;
			inline const glm::vec4& back_upper_right(void) const;

		private:
			glm::vec4 front_lower_left_;
			glm::vec4 front_lower_right_;
			glm::vec4 front_upper_left_;
			glm::vec4 front_upper_right_;
			glm::vec4 back_lower_left_;
			glm::vec4 back_lower_right_;
			glm::vec4 back_upper_left_;
			glm::vec4 back_upper_right_;
			
	};

	inline const glm::vec4& box::front_lower_left(void) const
	{
		return front_lower_left_;
	}

	inline const glm::vec4& box::front_lower_right(void) const
	{
		return front_lower_right_;
	}

	inline const glm::vec4& box::front_upper_left(void) const
	{
		return front_upper_left_;
	}

	inline const glm::vec4& box::front_upper_right(void) const
	{
		return front_upper_right_;
	}

	inline const glm::vec4& box::back_lower_left(void) const
	{
		return back_lower_left_;
	}

	inline const glm::vec4& box::back_lower_right(void) const
	{
		return back_lower_right_;
	}

	inline const glm::vec4& box::back_upper_left(void) const
	{
		return back_upper_left_;
	}
	
	inline const glm::vec4& box::back_upper_right(void) const
	{
		return back_upper_right_;
	}

}

}

#endif /* end of include guard: BOX_HPP_EJWMLSGU */
