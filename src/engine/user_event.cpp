#include "engine/user_event.hpp"

namespace rg
{
namespace engine
{
	user_event::user_event(const uuid& scene_id)
		:	scene_id_(scene_id)
	{}


	inline user_event& user_event::operator=(const user_event& e)
	{
		scene_id_ = e.scene_id_;

		return *this;
	}

	inline user_event& user_event::operator=(user_event&& e)
	{
		scene_id_ = std::move(e.scene_id_);

		/*test if e.scene_id_ is set to null*/
		return *this;
	}


	Uint32 type(void)
	{
		return SDL_USEREVENT;
	}




	inline Uint32 user_event::regiser_event(void)
	{
		return SDL_RegisterEvents(1);
	}

	inline const uuid& user_event::scene_id(void)
	{
		return scene_id_;
	}
}
}
