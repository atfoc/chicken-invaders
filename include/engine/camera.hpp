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
			
			virtual void apply(int w, int h) = 0;

			virtual camera* copy(void) = 0;
			virtual ~camera(void) = default;

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
