#include <algorithm>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/event.hpp"
#include "engine/timer_event.hpp"
#include "engine/box.hpp"
#include "engine/scene.hpp"
#include "engine/removed_event.hpp"
#include "engine/support/box_visualizer.hpp"

namespace rg
{
namespace engine
{
namespace support
{
	box_visualizer::box_visualizer(void)
	{}
	
	void box_visualizer::render(void)
	{
		rg::engine::box b;
		glm::vec3 tmp;
		for(auto it : objs_)
		{
			b = it->box_mash();	
			tmp = b.bottom_left();
			glDisable(GL_LIGHTING);
			glBegin(GL_LINE_LOOP);
				glVertex3f(tmp.x, tmp.y, tmp.z);
				tmp = b.bottom_right();
				glVertex3f(tmp.x, tmp.y, tmp.z);
				tmp = b.top_right();
				glVertex3f(tmp.x, tmp.y, tmp.z);
				tmp = b.top_left();
				glVertex3f(tmp.x, tmp.y, tmp.z);
	
			glEnd();
			glEnable(GL_LIGHTING);
		}
	}
	
	bool box_visualizer::handle_events(const rg::engine::event& e)
	{
		if(SDL_USEREVENT == e.type())
		{
			//TODO: exception
			const auto& user_event = dynamic_cast<const rg::engine::user_event&>(e);
			if(rg::engine::user_event_code<rg::engine::removed_event>::value == user_event.code())				
			{
				const auto& rm_ev =dynamic_cast<const rg::engine::removed_event&>(user_event);
				auto it = std::find_if(objs_.begin(), objs_.end(), [&](auto x){return x->id() == rm_ev.removed_object();});
				if(objs_.end() != it)
				{
					objs_.erase(it);
				}
			}
	
		}
		return false;
	}
	
	rg::engine::game_object* box_visualizer::copy(void)
	{
		return new box_visualizer(*this);
	}
	
	rg::engine::box box_visualizer::box_mash(void)
	{
		return rg::engine::box();
	}
	
	box_visualizer::~box_visualizer(void)
	{
	
	}
	void box_visualizer::add_object(game_object* obj)
	{
		objs_.push_back(obj);
	
	}
}
}
}

