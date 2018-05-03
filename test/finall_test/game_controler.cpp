#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/log.hpp"
#include "engine/application.hpp"
#include "game_controler.hpp"
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

using log_ = rg::engine::log;
namespace app = rg::engine::application;

rg::engine::color gen_random_color(void);

game_controler::game_controler(void) 
	: t_(nullptr), curr_player_{0}
{}

game_controler::game_controler(const game_controler& o)
	:	game_object(o),
		t_(new rg::engine::timer(*o.t_)),
		rotate_cubes_(o.rotate_cubes_),
		color_cubes_(o.color_cubes_),
		curr_player_{o.curr_player_}
{}

void game_controler::on_frame(void)
{
}

void game_controler::render(void)
{
	for(size_t i = 0; i < players_.size(); ++i)
	{
		if(i == curr_player_)
		{
			continue;
		}

		glPushMatrix();
		players_[i]->render();
		glPopMatrix();
	}
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

					for(auto&& it : color_cubes_)
					{
						it->color(gen_random_color());
					}

					for(auto&& it : rotate_cubes_)
					{
						it->transform(glm::rotate(glm::mat4(1), 0.1f, glm::vec3{0, 1, 0}));
					}
				}
				else if(e_.code() == rg::engine::user_event_code<rg::engine::resume_event>::value)
				{
					t_ = std::make_unique<rg::engine::timer>(this->scene()->id(), id(),  200, true);
					t_->start();
					(*app::logger()) << log_::priority::info << "Timer started in game object within scene id: " << scene()->id() << log_::end_log;

				}
				else if(e_.code() == rg::engine::user_event_code<rg::engine::pause_event>::value)
				{
					t_->pause();
					(*app::logger()) << log_::priority::info << "Timer paused in game object within scene id: " << scene()->id() << log_::end_log;
				}
			}
			catch(std::exception& e)
			{
	
			}
			break;
				
		case SDL_MOUSEWHEEL:
			SDL_Event es = e.sdl_event();
			if(es.wheel.y < 0)
			{
				/*scroll down*/
				/*TODO: implement later*/
				return true;
			}
			else if(es.wheel.y > 0)
			{
				/*scroll up*/
				players_[curr_player_]->save();
				++curr_player_;
				curr_player_ %= players_.size();
				players_[curr_player_]->restore();
				return true;
			}
			break;
	}
	if(e.type() == SDL_KEYDOWN)
	{
		return players_[curr_player_]->handle_events(e);		
	}
	else if(e.type() == SDL_MOUSEMOTION)
	{
		return players_[curr_player_]->handle_events(e);
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


void game_controler::add_rotate(cube* c)
{
	rotate_cubes_.push_back(c);
}

void game_controler::add_color(cube* c)
{
	color_cubes_.push_back(c);
}

rg::engine::color gen_random_color(void)
{
	int r = std::rand() % 256;
	int g = std::rand() % 256;
	int b = std::rand() % 256;

	return rg::engine::color(r/255.0f, g/255.0f, b/255.0f);
}


void game_controler::add_player(player* p)
{
	players_.push_back(std::unique_ptr<player>(p));
}
