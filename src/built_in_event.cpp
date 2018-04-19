#include <utility>
#include "engine/built_in_event.hpp"


namespace rg
{
namespace engine
{
	built_in_event::built_in_event(const SDL_Event& e)
		:	e_(e)
	{}


	inline built_in_event& built_in_event::operator=(const built_in_event& e)
	{


	}

	inline built_in_event& built_in_event::operator=(built_in_event&& e)
	{

	}


	SDL_EventType type(void)
	{

	}

	SDL_Event get_sdl_event(void)
	{

	}

}
}
