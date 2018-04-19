#ifndef BUILT_IN_EVENT_HPP_J7RKDI5Q
#define BUILT_IN_EVENT_HPP_J7RKDI5Q

#include "event.hpp"


namespace rg
{
namespace engine
{
	class built_in_event : public event
	{

		public:
			built_in_event(const SDL_Event& e);
			built_in_event(const built_in_event& e) = default;
			built_in_event(built_in_event&& e) = default;


			inline built_in_event& operator=(const built_in_event& e);
			inline built_in_event& operator=(built_in_event&& e);


			Uint32 type(void);
			SDL_Event sdl_event(void);

			virtual ~built_in_event(void) = default;


		private:
			SDL_Event e_;
	};
}
}

#endif /* end of include guard: BUILT_IN_EVENT_HPP_J7RKDI5Q */

