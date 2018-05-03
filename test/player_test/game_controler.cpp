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
#include "rotate_event.hpp"
#include "engine/timer_event.hpp"
#include "engine/resume_event.hpp"
#include "engine/user_event.hpp"
#include "rotate_event.hpp"

static bool changed{false};

game_controler::game_controler(void) 
	: t_(nullptr)
{
	
}
game_controler::game_controler(const game_controler& o)
	:	game_object(o),
		t_(new rg::engine::timer(*o.t_))
{

}
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
					scene()->broadcast(rotate_event(scene()->id()));
				}
				else if(e_.code() == rg::engine::user_event_code<rg::engine::resume_event>::value)
				{
					t_ = std::make_unique<rg::engine::timer>(this->scene()->id(), id(),  200, true);
					t_->start();
				}

			}
			catch(std::exception& e)
			{
	
			}
			break;
				

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




