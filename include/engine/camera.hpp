#ifndef CAMERA_HPP_KG6WEMLM
#define CAMERA_HPP_KG6WEMLM

namespace rg
{
namespace engine
{
	class camera
	{
		public:
			camera(void) = default;		
			camera(const camera& cam) = default;
			
			virtual void apply(void) = 0;

			virtual ~camera(void) = default;
	};
}
}

#endif /* end of include guard: CAMERA_HPP_KG6WEMLM */
