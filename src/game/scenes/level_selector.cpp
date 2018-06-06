#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/user_event.hpp"
#include "engine/timer_event.hpp"
#include "engine/scene.hpp"
#include "engine/support/bundle.hpp"
#include "engine/resume_event.hpp"
#include "engine/pause_event.hpp"
#include "engine/timer.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/window.hpp"
#include "game/level/level.hpp"
#include "game/scenes/level_selector.hpp"
#include "game/level/level_representation.hpp"

namespace engine = rg::engine;
namespace app = rg::engine::application;
namespace support = rg::engine::support;
using log_ = engine::log;

void thread_function(level* l, engine::uuid scene, engine::uuid obj, rg::engine::texture_loader* tl, rg::engine::model_loader* ml);

level_selector::level_selector(	rg::engine::perspective_camera* cam, float speed, const engine::uuid& loader_scene,
								const engine::uuid& loader_obj, const engine::uuid& cam_id,
								engine::texture_loader* tl, engine::model_loader* ml)
	:	curr_level_{0},
		moving_{false},
		cam_{cam},
		scene_to_delete_(engine::uuids::null_id),
		t_(nullptr),
		speed_{speed},
		ls_(loader_scene),
		lo_(loader_obj),
		cam_id_(cam_id),
		tl_{tl},
		ml_{ml},
		ship_{new ship(*ml, true)},
		ship_is_added_{false}
{
}


bool level_selector::handle_events(const rg::engine::event& e)
{
	static float eps{0.5};
	if(SDL_USEREVENT == e.type())
	{
		try
		{

			auto& e_{dynamic_cast<const engine::user_event&>(e)};
			if(engine::user_event_code<engine::timer_event>::value == e_.code())
			{
#ifdef TIMER_DEBUG
				(*app::logger()) << log_::priority::debug<< "Recived timer event in scene with id: " << scene()->id() << log_::end_log;;
#endif

				auto res = cam_->point();
				res[1] = 0;
				res[2] = 0;
				if(std::fabs(res[0] - target_position_[0]) < eps)
				{
					moving_ = false;
				}
				else if(moving_)
				{
					glm::vec3 direction_vec = target_position_ - cam_->point() ;
					direction_vec[1] = 0;
					direction_vec[2] = 0;
					glm::vec3 move_vector = static_cast<float>(std::pow(speed_, 2)/direction_vec.length()) * direction_vec;

					if(direction_vec.length() < move_vector.length())
					{
						cam_->eye(cam_->eye() + direction_vec);
						cam_->point(cam_->point() + direction_vec);
						ship_->ltransform(glm::translate(glm::mat4(1), direction_vec));
					}
					else
					{
						cam_->eye(cam_->eye() + move_vector);
						cam_->point(cam_->point() + move_vector);
						ship_->ltransform(glm::translate(glm::mat4(1), move_vector));
					}
				}

				for(const auto& it : levels_objects_)
				{
					it->on_tick();
				}
				return true;
			}

			if(engine::user_event_code<support::bundle_event<engine::uuid>>::value == e_.code())
			{

				auto& be = dynamic_cast<const support::bundle_event<engine::uuid>&>(e_);

				scene_to_delete_ = std::get<0>(be);

				return true;
			}

			if(engine::user_event_code<engine::resume_event>::value == e_.code())
			{
				if(!t_)
				{
					t_ = std::make_unique<engine::timer>(scene()->id(), id(),  50, true);
				}

				if(t_)
				{
					t_->start();
				}

				if(!engine::uuids::is_null(scene_to_delete_))
				{

					app::remove_scene(scene_to_delete_);
				}
				scene_to_delete_ = engine::uuids::null_id;

				if(!ship_is_added_)
				{
					ship_->rtransform(glm::translate(glm::mat4(1), glm::vec3{-0.3,0,1.5}));
					ship_->rtransform(glm::rotate(glm::mat4(1), 90.0f, glm::vec3{0, 1, 0}));
					ship_->rtransform(glm::scale(glm::mat4(1), 0.0004f*glm::vec3{1,1,1}));
					scene()->add_object(ship_);
					ship_is_added_ = true;
				}
				return true;
			}

			if(engine::user_event_code<engine::pause_event>::value == e_.code())
			{
				if(t_)
				{
					t_->stop();
				}
				return true;
			}
		}
		catch(std::exception& e)
		{

		}
	}

	if(SDL_KEYUP == e.type())
	{
		SDL_Event e_ = e.sdl_event();

		if(SDLK_RIGHT== e_.key.keysym.sym)
		{
			if(static_cast<unsigned>(curr_level_ + 1) < levels_.size())
			{
				(*app::logger()) << log_::priority::info << "Selecting next level" << log_::end_log;
				
				++curr_level_;
				moving_ = true;
				target_position_ = levels_objects_[curr_level_]->position();
			}

			return true;
		}
		else if(SDLK_LEFT== e_.key.keysym.sym)
		{
			if(curr_level_ -1 >= 0)
			{
				(*app::logger()) << log_::priority::info << "Selecting previous level" << log_::end_log;
				--curr_level_;
				moving_ = true;
				target_position_ = levels_objects_[curr_level_]->position();
			}
			return true;

		}
		else if(SDLK_RETURN== e_.key.keysym.sym)
		{
			if(!moving_)
			{
				(*app::logger()) << log_::priority::info << "Selected " << curr_level_ << " level" << log_::end_log;
				app::create_thread(thread_function, levels_[curr_level_].get(), ls_, lo_, tl_, ml_);
				auto win = scene()->windows()[0];
				win->attach_scene(ls_, support::make_bundle_event(ls_, lo_, scene()->id(), cam_->id()));
				win->attach_camera(cam_id_, [](int w, int h){return std::make_tuple(0, 0, w, h);});
			}

		}
		return true;
	}
	return false;
}

/*TODO: this will be delteted*/
rg::engine::game_object* level_selector::copy(void)
{
	return nullptr;
}

rg::engine::box level_selector::box_mash(void)
{
	return engine::box();
}

void level_selector::add_level(level* l)
{
	levels_.push_back(std::unique_ptr<level>(l));
	level_representation* lr = l->representation(*tl_, *ml_);
	lr->transform(glm::translate(glm::mat4(1), glm::vec3{levels_objects_.size()*2, 0, 0}));
	levels_objects_.push_back(lr);
	scene()->add_object(lr);
}

void thread_function(level* l, engine::uuid scene, engine::uuid obj, rg::engine::texture_loader* tl, rg::engine::model_loader* ml)
{
	auto s = l->scene(*tl, *ml);
	auto cid = l->camera();
	app::post_event(support::make_bundle_event(scene, obj, s, cid));
}
