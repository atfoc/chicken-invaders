#ifndef PAUSE_EVENT_HPP_EMRFUTYZ
#define PAUSE_EVENT_HPP_EMRFUTYZ

#include "engine/user_event.hpp"
#include "engine/id.hpp"

namespace rg
{
namespace engine
{
	class pause_event: public user_event
	{
		public:
			pause_event(const uuid& scene_id);	
			pause_event(const pause_event& o) = default;
			
				
			SDL_Event sdl_event(void) const;
			Uint32 code(void) const;

			~pause_event(void) = default;
	};
}
}
#endif /* end of include guard: PAUSE_EVENT_HPP_EMRFUTYZ */
