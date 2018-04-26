#ifndef RESUME_EVENT_HPP_1NZDU0VE
#define RESUME_EVENT_HPP_1NZDU0VE

#include "engine/user_event.hpp"
#include "engine/id.hpp"

namespace rg
{
namespace engine
{
	class resume_event : public user_event
	{
		public:
			resume_event(const uuid& scene_id);	
			resume_event(const resume_event& o) = default;
			
				
			SDL_Event sdl_event(void) const;
			Uint32 code(void) const;

			~resume_event(void) = default;
	};
}
}

#endif /* end of include guard: RESUME_EVENT_HPP_1NZDU0VE */
