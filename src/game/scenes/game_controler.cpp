#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/log.hpp"
#include "engine/application.hpp"
#include "game/scenes/game_controler.hpp"
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

using log_ = rg::engine::log;
namespace app = rg::engine::application;

rg::engine::color gen_random_color(void);

game_controler::game_controler(void) 
	: t_(nullptr) 
{}

game_controler::game_controler(const game_controler& o)
	:	game_object(o),
		t_(new rg::engine::timer(*o.t_))
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

				}
				else if(e_.code() == rg::engine::user_event_code<rg::engine::resume_event>::value)
				{
					t_ = std::make_unique<rg::engine::timer>(this->scene()->id(), id(),  50, true);
					t_->start();
					(*app::logger()) << log_::priority::info << "Timer started in game object within scene id: " << scene()->id() << log_::end_log;
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
			auto win = scene()->windows()[0];
			win->attach_scene(back_scene_, rg::engine::support::make_bundle_event(back_scene_, rg::engine::uuids::null_id, scene()->id()));
			win->attach_camera(camid_, [](int w, int h){return std::make_tuple(0,0, w, h);});
			return true;
		}
	}
	return false;
}

rg::engine::game_object* game_controler::copy(void)
{
	return new game_controler(*this);
}

rg::engine::box game_controler::box_mash(void)
{
	return rg::engine::box();
}
