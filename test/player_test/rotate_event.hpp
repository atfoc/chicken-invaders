#ifndef ROTATE_EVENT_HPP_AOW8SJYT
#define ROTATE_EVENT_HPP_AOW8SJYT

#include "engine/target_event.hpp"
#include "engine/id.hpp"



class rotate_event : public rg::engine::target_event
{
	public:
	rotate_event(const rg::engine::uuid& scene_id);
	rotate_event(const rotate_event& e) = default;



	SDL_Event sdl_event(void) const;
	Uint32 code(void) const;

	~rotate_event(void) = default;



			


};

#endif /* end of include guard:  */
