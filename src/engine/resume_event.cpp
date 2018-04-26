#include "engine/resume_event.hpp"

namespace rg
{
namespace engine
{
	resume_event::resume_event(const uuid& scene_id)	
		:	user_event(scene_id)
	{}
		
			
	SDL_Event resume_event::sdl_event(void) const
	{
		SDL_Event e;
		e.type = SDL_USEREVENT;
		e.user.data1 = new resume_event(*this);

		return e;
	}
	
	Uint32 resume_event::code(void) const
	{
		return user_event_code<resume_event>::value;	
	}

}
}
