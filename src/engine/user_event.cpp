#include "engine/user_event.hpp"

namespace rg
{
namespace engine
{
	user_event::user_event(const uuid& scene_id) 
		:	scene_id_(scene_id)
	{}


	

	Uint32 user_event::type(void) const
	{
		return SDL_USEREVENT;
	}




	
}
}
