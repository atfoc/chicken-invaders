#ifndef USER_EVENT_HPP_OR4XR3IL
#define USER_EVENT_HPP_OR4XR3IL

#include "event.hpp"
#include "id.hpp"

namespace rg
{
namespace engine
{
	class user_event : public event
	{

		public:
			user_event(const uuid& scene_id);
			user_event(const user_event& e) = default;
			user_event(user_event&& e) = default;


			inline user_event& operator=(const user_event& e);
			inline user_event& operator=(user_event&& e);


			Uint32 type(void);	
			inline const uuid& scene_id(void);	

			virtual SDL_Event sdl_event(void) = 0;
			virtual Uint32 code(void) = 0;

			virtual ~user_event(void) = default;


			inline static Uint32 regiser_event(void);

		private:
			uuid scene_id_;

	};
}
}

#endif /* end of include guard: USER_EVENT_HPP_OR4XR3IL */
