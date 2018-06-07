#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/log.hpp"
#include "engine/application.hpp"
#include "engine/event.hpp"
#include "engine/application.hpp"
#include "engine/scene.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/window.hpp"
#include "engine/light.hpp"
#include "engine/box.hpp"
#include "engine/timer_event.hpp"
#include "engine/resume_event.hpp"
#include "engine/user_event.hpp"
#include "engine/pause_event.hpp"
#include "engine/removed_event.hpp"
#include "engine/support/bundle.hpp"
#include "game/objects/game_controler.hpp"
#include "game/objects/explosion.hpp"

using log_ = rg::engine::log;
namespace app = rg::engine::application;

void init_level_scene(game_controler& gc);

game_controler::game_controler(int wave_number) 
	:	t_(nullptr),
		wave_number_{wave_number},
		game_started_{false},
		time_for_chicken_to_shoot_{20},
		time_left_{time_for_chicken_to_shoot_}
{}

game_controler::game_controler(const game_controler& o)
	:	game_object(o),
		t_(new rg::engine::timer(*o.t_)),
		wave_number_{o.wave_number_},
		game_started_{o.game_started_},
		time_for_chicken_to_shoot_{o.time_for_chicken_to_shoot_},
		time_left_{time_for_chicken_to_shoot_}
{}

void game_controler::on_frame(void)
{
}

void game_controler::render(void)
{
	
}

bool game_controler::handle_events(const rg::engine::event& e)
{
	switch(e.type())
	{

		case SDL_USEREVENT:
			try
			{
				auto& e_ = dynamic_cast<const rg::engine::user_event&>(e);

				if(e_.code() == rg::engine::user_event_code<rg::engine::timer_event>::value)
				{
					#ifdef TIMER_DEBUG
						(*app::logger()) << log_::priority::info << "Tick from timer in scene with id: " << scene()->id() << log_::end_log;
					#endif

					static float tmp_sin_par = 0;
					static float move_chick = 0;
					tmp_sin_par += 0.05;
					move_chick = (std::signbit(std::cos(tmp_sin_par)) == 0 ? 1: -1) * 0.1 ;


						(*app::logger()) << log_::priority::info <<move_chick  << log_::end_log;
					for(auto it : chickens_)
					{
						it->pos(it->pos() + glm::vec3{move_chick, 0, 0});
					}

					--time_left_;
					if(0 == time_left_)
					{
						auto n = std::rand() % chickens_.size();
						auto b = new bullet(*b_);
						b->ltransform(glm::scale(glm::mat4(1), 0.15f*glm::vec3{1,1,1}));
						b->ltransform(glm::rotate(glm::mat4(1), static_cast<float>(M_PI), glm::vec3{0,1,0}));
						b->ltransform(glm::translate(glm::mat4(1), chickens_[n]->pos()));
						scene()->add_object(b);
						time_left_ = time_for_chicken_to_shoot_;
					}

				}
				else if(e_.code() == rg::engine::user_event_code<rg::engine::resume_event>::value)
				{
					t_ = std::make_unique<rg::engine::timer>(this->scene()->id(), rg::engine::uuids::null_id,  50, true);
					t_->start();
					(*app::logger()) << log_::priority::info << "Timer started in game object within scene id: " << scene()->id() << log_::end_log;

					if(!game_started_)
					{
						(*app::logger()) << log_::priority::info << "Initialazing level scene with objects" << log_::end_log;
						init_level_scene(*this);
					}

					(*app::logger()) << log_::priority::info << "Game starting" << log_::end_log;
					game_started_ = true;
				}
				else if(e_.code() == rg::engine::user_event_code<rg::engine::pause_event>::value)
				{
					t_->stop();
					(*app::logger()) << log_::priority::info << "Timer paused in game object within scene id: " << scene()->id() << log_::end_log;
				}
				else if(rg::engine::user_event_code<rg::engine::support::bundle_event<rg::engine::uuid, rg::engine::uuid>>::value == e_.code())
				{
					auto& be = dynamic_cast<const rg::engine::support::bundle_event<rg::engine::uuid, rg::engine::uuid>&>(e_);
					back_scene_ = std::get<0>(be);
					camid_ = std::get<1>(be);
				}
				else if(rg::engine::user_event_code<rg::engine::removed_event>::value == e_.code())
				{
					auto rm_ev = dynamic_cast<const rg::engine::removed_event&>(e_);

					if(rm_ev.removed_object() == ship_->id())
					{
						//TODO:wait few seconds 
						app::post_event(rg::engine::support::make_bundle_event(scene()->id(), id(), std::string("You lost")));
						return true;
					}
					else
					{
						auto it = std::find_if(chickens_.begin(), chickens_.end(), [&](auto x){return x->id() == rm_ev.removed_object();});
						if(it != chickens_.end())
						{
							chickens_.erase(it);
						}

						if(chickens_.empty())
						{
							--wave_number_;
							if(0 == wave_number_)
							{
								app::post_event(rg::engine::support::make_bundle_event(scene()->id(), id(), std::string("You won")));
							}
							else
							{
								for(int i = 0; i < 5; ++i)
								{
									auto tmp = dynamic_cast<chicken*>(chicken_->copy());
									chickens_.push_back(tmp);
									tmp->pos(glm::vec3{-4 + 2*i, 0, -2.5});
									scene()->add_object(tmp);
								}
							}
						}
					}
				}
				else if(rg::engine::user_event_code<rg::engine::support::bundle_event<std::string>>::value == e_.code())
				{
					auto be = dynamic_cast<const rg::engine::support::bundle_event<std::string>&>(e_);
					(*app::logger()) << log_::priority::info << std::get<0>(be) << log_::end_log;
					auto win = scene()->windows()[0];
					win->attach_scene(back_scene_, rg::engine::support::make_bundle_event(back_scene_, rg::engine::uuids::null_id, scene()->id()));
					win->attach_camera(camid_, [](int w, int h){return std::make_tuple(0,0, w, h);});
					return true;

				}
			}
			catch(std::exception& e)
			{
	
			}
			break;
				
	}
	if(e.type() == SDL_KEYDOWN)
	{
	}
	else if(e.type() == SDL_MOUSEMOTION)
	{
	}
	else if(e.type() == SDL_KEYUP)
	{
		SDL_Event se = e.sdl_event();

		if(SDLK_ESCAPE == se.key.keysym.sym)
		{
			app::post_event(rg::engine::support::make_bundle_event(scene()->id(), id(), std::string("You quited the levle")));
		}
	}
	return false;
}

void game_controler::load_models(rg::engine::model_loader& ml, rg::engine::texture_loader& tl)
{
	unsigned tex = tl.load("./materials/expl.jpeg").second;
	ship_ = new ship(ml, false, tex);
	ship_->rtransform(glm::translate(glm::mat4(1), glm::vec3{0, 0, 4.5}));
	ship_->rtransform(glm::rotate(glm::mat4(1), static_cast<float>(M_PI), glm::vec3{0,1,0}));
	ship_->rtransform(glm::scale(glm::mat4(1), 0.001f*glm::vec3{1,1,1}));

	chicken_ = new chicken(ml.load("./materials/ship2/UFO.obj").second, tex);
	chicken_->ltransform(glm::translate(glm::mat4(1), glm::vec3{0,0,-4}));
	chicken_->ltransform(glm::scale(glm::mat4(1), 0.4f*glm::vec3{1,1,1}));
	//How terrable thisg can go here
	b_ = new bullet(ml.load("./materials/rocket/model.obj").second, 20, bullet::direction::down, tex);


}

rg::engine::game_object* game_controler::copy(void)
{
	return new game_controler(*this);
}

rg::engine::box game_controler::box_mash(void)
{
	return rg::engine::box();
}


void init_level_scene(game_controler& gc)
{
	gc.scene()->add_object(gc.ship_);	
	gc.ship_->handle_events(rg::engine::resume_event(gc.scene()->id()));
	chicken* tmp;
	for(int i = 0; i < 5; ++i)
	{
		tmp = dynamic_cast<chicken*>(gc.chicken_->copy());
		gc.chickens_.push_back(tmp);
		tmp->pos(glm::vec3{-4 + 2*i, 0, -2.5});
		gc.scene()->add_object(tmp);
	}
}

