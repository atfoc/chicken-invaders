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
			
			virtual void apply(int w, int h) = 0;

			virtual ~camera(void) = default;
	};
}
}

#endif /* end of include guard: CAMERA_HPP_KG6WEMLM */
