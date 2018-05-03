#include "engine/camera.hpp"
namespace rg
{
namespace engine
{
	camera::camera(void)
		:	id_(uuids::random_id())
	{
	}
	
	camera::camera(const camera& c)
		:	id_(uuids::random_id())
	{
		static_cast<void>(c);	
	}
}
}

