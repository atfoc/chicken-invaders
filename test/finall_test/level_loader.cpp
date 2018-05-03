#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "level_loader.hpp"
#include "engine/scene.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/window.hpp"
#include "engine/timer_event.hpp"

namespace engine = rg::engine;
namespace support = rg::engine::support;
namespace app = rg::engine::application;

using log_ = rg::engine::log;

level_loader::level_loader(void)
	:	back_scene_id_(rg::engine::uuids::null_id),
		t_(nullptr)
{

}

level_loader::level_loader(const level_loader& l)
	:	back_scene_id_(l.back_scene_id_),
		t_(nullptr)	
{
}

rg::engine::game_object* level_loader::copy(void)	
{
	return new level_loader(*this);
}

rg::engine::box level_loader::box_mash(void)
{
	return rg::engine::box();
}

bool level_loader::handle_events(const rg::engine::event& e)
{
	if(SDL_USEREVENT == e.type())
	{
		try
		{
			const rg::engine::user_event& e_ = reinterpret_cast<const rg::engine::user_event&>(e);

			if(rg::engine::user_event_code<rg::engine::support::bundle_event<rg::engine::uuid>>::value == e_.code())
			{
				auto be = reinterpret_cast<const rg::engine::support::bundle_event<rg::engine::uuid>&>(e_);
				
				back_scene_id_ = std::get<0>(be);
				(*app::logger()) << log_::priority::info << "Registered back scene with id: " << back_scene_id_ << log_::end_log;
			}
			else if(rg::engine::user_event_code<rg::engine::support::bundle_event<rg::engine::scene*>>::value == e_.code())
			{
				auto be = reinterpret_cast<const rg::engine::support::bundle_event<rg::engine::scene*>&>(e_);
				
				auto s = std::get<0>(be);
				(*app::logger()) << log_::priority::info << "Recived scene to start with id: " << s->id() << log_::end_log;
				app::add_scene(s);

				scene()->windows()[0]->attach_scene(s->id(), support::make_bundle_event(s->id(), engine::uuids::null_id, back_scene_id_));
			}
			else if(engine::user_event_code<engine::timer_event>::value == e_.code())
			{
				transform(glm::rotate(glm::mat4(1), 0.5f, glm::vec3{0, 1, 0}));
			}

		}
		catch(std::exception& e)
		{

		}
	}
}

void level_loader::render(void)
{

}

