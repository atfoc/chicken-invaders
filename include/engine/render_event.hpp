#ifndef RENDER_EVENT_HPP_8I3N0A7C
#define RENDER_EVENT_HPP_8I3N0A7C

#include "engine/user_event.hpp"

namespace rg
{
namespace engine
{
	class render_event : public user_event
	{
		public:
			render_event(int w_id);
			render_event(const render_event& r) = default;
			
			SDL_Event sdl_event(void) const;
			Uint32 code(void) const;

			int w_id(void);
			~render_event(void) = default;
		private:
			int w_id_;
	};
}
}

#endif /* end of include guard: RENDER_EVENT_HPP_8I3N0A7C */
