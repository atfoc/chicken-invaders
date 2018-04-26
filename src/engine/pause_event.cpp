
#include "engine/pause_event.hpp"

namespace rg
{
namespace engine
{
	pause_event::pause_event(const uuid& scene_id)	
		:	user_event(scene_id)
	{}
		
			
	SDL_Event pause_event::sdl_event(void) const
	{
		SDL_Event e;
		e.type = SDL_USEREVENT;
		e.user.data1 = new pause_event(*this);

		return e;
	}
	
	Uint32 pause_event::code(void) const
	{
		return user_event_code<pause_event>::value;	
	}

}
}
