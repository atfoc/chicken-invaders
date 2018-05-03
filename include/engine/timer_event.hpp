#ifndef TIMER_EVENT_HPP_ULWA2IYQ
#define TIMER_EVENT_HPP_ULWA2IYQ


#include "engine/target_event.hpp"

namespace rg
{
namespace engine
{
	class timer_event : public target_event
	{
		public:
			timer_event(const uuid& scene_id, const uuid& object_id, const uuid& timer_id);
			timer_event(const timer_event& o) = default;


			SDL_Event sdl_event(void) const;
			Uint32 code(void) const;

			const uuid& timer_id(void) const;

			~timer_event(void) = default;
		private:
			uuid timer_id_;
	};
}
}

#endif /* end of include guard: TIMER_EVENT_HPP_ULWA2IYQ */
