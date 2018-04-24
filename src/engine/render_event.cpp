#include "engine/render_event.hpp"
#include "engine/id.hpp"

namespace rg
{
namespace engine
{
	render_event::render_event(int w_id)
		:	user_event(uuids::null_id),
			w_id_{w_id}
	{}

	SDL_Event render_event::sdl_event(void) const
	{
		SDL_Event e;

		e.type = SDL_USEREVENT;
		e.user.code = code();
		e.user.data1 = new render_event(*this);

		return e;
	}

	int render_event::w_id(void)
	{
		return w_id_;
	}

	Uint32 render_event::code(void) const
	{
		return user_event_code<render_event>::value;
	}
}
}

