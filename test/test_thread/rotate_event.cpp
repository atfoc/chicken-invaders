#include "rotate_event.hpp"

rotate_event::rotate_event(const rg::engine::uuid& scene_id)
	:	target_event(scene_id, rg::engine::uuids::null_id)
{}



SDL_Event rotate_event::sdl_event(void) const
{
	SDL_Event e;
	e.type = SDL_USEREVENT;
	e.user.data1 = new rotate_event(*this);

	return e;
}

Uint32 rotate_event::code(void) const
{
	return rg::engine::user_event_code<rotate_event>::value;
}

