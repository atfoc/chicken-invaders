#include "engine/timer_event.hpp"

namespace rg
{
namespace engine
{
	timer_event::timer_event(const uuid& scene_id, const uuid& object_id, const uuid& timer_id)
		:	target_event(scene_id, object_id),
			timer_id_(timer_id)
	{}


	SDL_Event timer_event::sdl_event(void) const
	{
		SDL_Event e;
		e.type = SDL_USEREVENT;
		e.user.data1 = new timer_event(*this);
		return e;
	}

	Uint32 timer_event::code(void) const
	{
		return user_event_code<timer_event>::value;	
	}
	
	const uuid& timer_event::timer_id(void) const
	{
		return timer_id_;	
	}

	
}
}
