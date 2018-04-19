#include "engine/target_event.hpp"

namespace rg
{
namespace engine
{

	target_event::target_event(const uuid& scene_id, const uuid& object_id)
		:	user_event(scene_id),
			object_id_(object_id)
	{}


	inline target_event& target_event::operator=(const target_event& e)
	{
		scene_id_ = e.scene_id_;
		object_id_ = e.object_id_;
	}

	inline target_event& target_event::operator=(target_event&& e)
	{
		scene_id_ = std::move(e.scene_id_);
		object_id_ = std::move( e.object_id_);
		
	}


	inline const uuid& target_event::object_id(void)
	{
		return object_id_;
	}


}
}
