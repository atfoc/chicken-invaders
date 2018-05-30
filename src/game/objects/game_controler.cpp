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
#include "engine/support/bundle.hpp"
#include "game/objects/game_controler.hpp"

using log_ = rg::engine::log;
namespace app = rg::engine::application;

void init_level_scene(game_controler& gc);

game_controler::game_controler(int wave_number) 
	:	t_(nullptr),
		wave_number_{wave_number},
		game_started_{false}
{}

game_controler::game_controler(const game_controler& o)
	:	game_object(o),
		t_(new rg::engine::timer(*o.t_)),
		wave_number_{o.wave_number_},
		game_started_{o.game_started_}
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

					if(game_started_)
					{
						/*Game tick logic here*/
					}

				}
				else if(e_.code() == rg::engine::user_event_code<rg::engine::resume_event>::value)
				{
					t_ = std::make_unique<rg::engine::timer>(this->scene()->id(), rg::engine::uuids::null_id,  50, true);
					t_->start();
					(*app::logger()) << log_::priority::info << "Timer started in game object within scene id: " << scene()->id() << log_::end_log;

					(*app::logger()) << log_::priority::info << "Initialazing level scene with objects" << log_::end_log;
					init_level_scene(*this);

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
			(*app::logger()) << log_::priority::info << "You closed a level" << log_::end_log;
			auto win = scene()->windows()[0];
			win->attach_scene(back_scene_, rg::engine::support::make_bundle_event(back_scene_, rg::engine::uuids::null_id, scene()->id()));
			win->attach_camera(camid_, [](int w, int h){return std::make_tuple(0,0, w, h);});
			return true;
		}
	}
	return false;
}

void game_controler::load_models(rg::engine::model_loader& ml)
{
	ship_ = new ship(ml);
	ship_->rtransform(glm::translate(glm::mat4(1), glm::vec3{0, 0, 4.5}));
	ship_->rtransform(glm::rotate(glm::mat4(1), static_cast<float>(M_PI), glm::vec3{0,1,0}));
	ship_->rtransform(glm::scale(glm::mat4(1), 0.001f*glm::vec3{1,1,1}));

	chicken_ = new chicken(ml.load("./materials/chicken/model.obj").second, this);
	chicken_->ltransform(glm::scale(glm::mat4(1), 0.04f*glm::vec3{1,1,1}));
	chicken_->ltransform(glm::rotate(glm::mat4(1), static_cast<float>(M_PI), glm::vec3{0,0,1}));
	chicken_->ltransform(glm::rotate(glm::mat4(1), static_cast<float>(-M_PI/4), glm::vec3{1,0,0}));
	chicken_->ltransform(glm::rotate(glm::mat4(1), static_cast<float>(M_PI), glm::vec3{0,1,0}));

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
	auto t = gc.chicken_->copy();
	gc.scene()->add_object(t);
}
