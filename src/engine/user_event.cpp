#include "engine/user_event.hpp"

namespace rg
{
namespace engine
{
	user_event::user_event(const uuid& scene_id)
		:	scene_id_(scene_id)
	{}


	

	Uint32 type(void)
	{
		return SDL_USEREVENT;
	}




	
}
}
