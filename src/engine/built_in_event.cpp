#include "engine/built_in_event.hpp"


namespace rg
{
namespace engine
{
	built_in_event::built_in_event(const SDL_Event& e)
		:	e_(e)
	{}



	Uint32 built_in_event::type(void)
	{

		return e_.type;
	}

	SDL_Event built_in_event::sdl_event(void)
	{
		return e_;
	}
}
}

