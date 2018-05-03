#include "engine/removed_event.hpp"

namespace rg
{
namespace engine
{

	removed_event::removed_event(const uuid& scene_id, const uuid& removed_obj)
		:	user_event(scene_id),
			removed_object_(removed_obj)	
	{

	}

	SDL_Event removed_event::sdl_event(void) const
	{
		SDL_Event e;
		e.type = SDL_USEREVENT;
		e.user.data1 = new removed_event(*this);
		return e;
	}

	Uint32 removed_event::code(void) const
	{
		return user_event_code<removed_event>::value;
	}
}
}
