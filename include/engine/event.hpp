#ifndef EVENT_HPP_EMNJSY8Q
#define EVENT_HPP_EMNJSY8Q


#include <SDL2/SDL_events.h>

namespace rg
{
namespace engine
{
	class event
	{
		public:
			event(void) = default;
			event(const event& e) = default;
			
			virtual Uint32 type(void) const= 0;
			virtual SDL_Event sdl_event(void) const = 0;

			virtual ~event(void) = default;
	};
}

}

#endif /* end of include guard: EVENT_HPP_EMNJSY8Q */
