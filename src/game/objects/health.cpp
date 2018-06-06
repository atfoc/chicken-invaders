#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/event.hpp"
#include "engine/timer_event.hpp"
#include "engine/box.hpp"
#include "engine/scene.hpp"
#include "game/objects/health.hpp"
#include "game/objects/chicken.hpp"

health::health(int time)
	:	time_{time},
		should_render_{false}
{}

void health::render(void)
{
	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	glBegin(GL_QUADS);
		glVertex3f(-0.5, 0, -0.1);
		glVertex3f(0.5, 0, -0.1);
		glVertex3f(0.5, 0, 0.1);
		glVertex3f(-0.5, 0, 0.1);
	glEnd();
	float w = value_/100.0f;
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
		glVertex3f(-0.5, 0.01, -0.1);
		glVertex3f(-0.5+w, 0.01, -0.1);
		glVertex3f(-0.5+w, 0.01, 0.1);
		glVertex3f(-0.5, 0.01, 0.1);
	glEnd();
	glEnable(GL_LIGHTING);
}

bool health::handle_events(const rg::engine::event& e)
{
	
	static_cast<void>(e);
	if(SDL_USEREVENT == e.type())
	{
		const rg::engine::user_event& ue = dynamic_cast<const rg::engine::user_event&>(e);
		if(rg::engine::user_event_code<rg::engine::timer_event>::value == ue.code())
		{	
			if(should_render_)
			{
				--time_left_;
				if(time_left_ < 0)
				{
					should_render_= false;
					show(false);
				}
			}
		}
	
	}
	return false;
}

rg::engine::game_object* health::copy(void)
{
	return new health(*this);
}

rg::engine::box health::box_mash(void)
{
	return rg::engine::box(0.5,1.5, position());
}

void health::display(float value)
{
	value_ = value;
	should_render_ = true;
	time_left_ = time_;
	show(true);	
}

health::~health(void)
{

}
