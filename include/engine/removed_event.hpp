#ifndef REMOVED_EVENT_HPP_RUMTFEE1
#define REMOVED_EVENT_HPP_RUMTFEE1



#include "engine/user_event.hpp"
#include "engine/id.hpp"

namespace rg
{
namespace engine
{
	class removed_event : public user_event 
	{

		public:
			removed_event(const uuid& scene_id, const uuid& removed_obj);
			removed_event(const removed_event& e) = default;

			SDL_Event sdl_event(void) const;
			Uint32 code(void) const;
			uuid removed_object(void) const;

			~removed_event(void) = default;



			

		private:
			uuid removed_object_;

	};

}
}
#endif /* end of include guard: REMOVED_EVENT_HPP_RUMTFEE1 */
