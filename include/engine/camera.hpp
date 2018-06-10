#ifndef CAMERA_HPP_KG6WEMLM
#define CAMERA_HPP_KG6WEMLM

#include "engine/id.hpp"

namespace rg
{
namespace engine
{
	class camera
	{
		public:
			camera(void);
			camera(const camera& c);
			
			
			/**
			 * @brief	this function is called from window when you want to
			 *			set up camera	and apply it so it can render
			 *
			 * @param w	width of viewport
			 * @param h	height of viewport
			 */
			virtual void apply(int w, int h) = 0;

			
			/**
			 * @brief copies camera overload this if you want to copy camera polymorphicly
			 *
			 * @return	copy of the camera
			 */
			virtual camera* copy(void) = 0;
			virtual ~camera(void) = default;

			
			/**
			 * @brief gets camera uuid
			 *
			 * @return cameras id
			 */
			inline uuid id(void);
		private:
			uuid id_;
	};

	inline uuid camera::id(void)
	{
		return id_;
	}
}
}

#endif /* end of include guard: CAMERA_HPP_KG6WEMLM */
