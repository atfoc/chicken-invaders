#ifndef TIMER_HPP_PNHFTA7N
#define TIMER_HPP_PNHFTA7N

#include <SDL2/SDL_timer.h>
#include "engine/id.hpp"

namespace rg
{
namespace engine
{
	struct timer_info
	{
		bool cont;
		uuid scene_id;
		uuid obj_id;
		uuid timer_id;
		Uint32 interval;
	};

	class timer
	{
		public:
			timer(const uuid& scene_id, const uuid& obj_id, Uint32 delay, bool continues);
			timer(timer&& t);
			timer(const timer& t);

		
			void start(void);
			void stop(void);
			void pause(void);

			bool started(void) const;
			
			const uuid& id(void);

			~timer(void);

		private:
			uuid scene_id_;
			uuid obj_id_;
			SDL_TimerID sdl_timer_id_;
			uuid timer_id_;
			bool started_;
			bool continues_;
			Uint32 delay_;
			time_t time_started_;
			bool paused_;
			time_t passed_;
			timer_info ti_;
			
			
	};
}
}

#endif /* end of include guard: TIMER_HPP_PNHFTA7N */
