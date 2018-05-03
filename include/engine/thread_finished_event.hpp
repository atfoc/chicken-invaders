#ifndef THREAD_FINISHED_EVENT_HPP_98LZSOPD
#define THREAD_FINISHED_EVENT_HPP_98LZSOPD

#include "engine/user_event.hpp"


namespace rg
{
namespace engine
{
	class thread_finished_event : public user_event
	{
	
		public:
			thread_finished_event(const uuid& scene_id, const uuid& th_id);
			thread_finished_event(const thread_finished_event& e) = default;


			SDL_Event sdl_event(void) const;
			Uint32 code(void) const;

			const uuid& th_id(void) const;
			~thread_finished_event(void) = default;
		private:
			uuid th_id_;
	};

}
}

#endif /* end of include guard: THREAD_FINISHED_EVENT_HPP_98LZSOPD */
