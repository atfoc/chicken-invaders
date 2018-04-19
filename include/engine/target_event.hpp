#ifndef TARGET_EVENT_HPP_YQ3D6MZH
#define TARGET_EVENT_HPP_YQ3D6MZH

#include "user_event.hpp"

namespace rg
{
namespace engine
{
	class target_event : public user_event 
	{

		public:
			target_event(const uuid& scene_id, const uuid& object_id);
			target_event(const target_event& e) = default;
			target_event(target_event&& e) = default;


			inline target_event& operator=(const target_event& e);
			inline target_event& operator=(target_event&& e);


			inline const uuid& object_id(void);	

			virtual SDL_Event sdl_event(void) = 0;
			virtual Uint32 code(void) = 0;

			virtual ~target_event(void) = default;


			inline static Uint32 regiser_event(void);

		private:
			uuid scene_id_;
			uuid object_id_;
			
	};
}
}

#endif /* end of include guard: TARGET_EVENT_HPP_YQ3D6MZH */
