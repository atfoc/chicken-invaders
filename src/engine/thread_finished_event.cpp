
#include "engine/thread_finished_event.hpp"

namespace rg
{
namespace engine
{
	thread_finished_event::thread_finished_event(const uuid& scene_id, const uuid& th_id)
		:	user_event(scene_id),
			th_id_(th_id)
	{}

	SDL_Event thread_finished_event::sdl_event(void) const
	{
		SDL_Event e;
		e.type = SDL_USEREVENT;
		e.user.data1 = new thread_finished_event(*this);
		return e;
	}

	Uint32 thread_finished_event::code(void) const 
	{
		return user_event_code<thread_finished_event>::value;
	}

	const uuid& thread_finished_event::th_id(void) const
	{
		return th_id_;
	}

}
}
