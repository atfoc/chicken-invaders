#include <GL/gl.h>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/scene.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/window.hpp"
#include "engine/timer_event.hpp" 
#include "engine/resume_event.hpp"
#include "engine/pause_event.hpp"
#include "engine/support/bundle.hpp"
#include "game/scenes/level_loader.hpp"

namespace engine = rg::engine;
namespace support = rg::engine::support;
namespace app = rg::engine::application;

using log_ = rg::engine::log;
level_loader::level_loader(void)
	:	back_scene_id_(rg::engine::uuids::null_id),
		t_(nullptr),
		end_animation_{0}
{

}

level_loader::level_loader(const level_loader& l)
	:	game_object(l),
		back_scene_id_(l.back_scene_id_),
		t_(nullptr),
		end_animation_{0}
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
	static float eps{0.01};
	if(SDL_USEREVENT == e.type())
	{
		try
		{
			const rg::engine::user_event& e_ = reinterpret_cast<const rg::engine::user_event&>(e);

			if(rg::engine::user_event_code<rg::engine::support::bundle_event<rg::engine::uuid, rg::engine::uuid>>::value == e_.code())
			{
				auto& be = dynamic_cast<const rg::engine::support::bundle_event<rg::engine::uuid, rg::engine::uuid>&>(e_);
				
				back_scene_id_ = std::get<0>(be);
				camid_ = std::get<1>(be);
				(*app::logger()) << log_::priority::info << "Registered back scene with id: " << back_scene_id_ << log_::end_log;
				return true;
			}
			else if(rg::engine::user_event_code<rg::engine::support::bundle_event<rg::engine::scene*, rg::engine::uuid>>::value == e_.code())
			{
				auto& be = dynamic_cast<const rg::engine::support::bundle_event<rg::engine::scene*, rg::engine::uuid>&>(e_);
				
				auto s = std::get<0>(be);
				auto cid = std::get<1>(be);
				(*app::logger()) << log_::priority::info << "Recived scene to start with id: " << s->id() << log_::end_log;
				app::add_scene(s);

				auto win = scene()->windows()[0];
				win->attach_scene(s->id(), support::make_bundle_event(s->id(), engine::uuids::null_id, back_scene_id_, camid_));
				win->attach_camera(cid, [](int w, int h){return std::make_tuple(0, 0, w, h);});
				return true;
			}
			else if(engine::user_event_code<engine::timer_event>::value == e_.code())
			{
				#ifdef TIMER_DEBUG
					(*app::logger()) << log_::priority::info << "Recived timer event in scene with id: " << scene()->id() << log_::end_log; 
				#endif
				end_animation_ += M_PI/20;
				if(end_animation_ + eps> 2*M_PI)
				{
					end_animation_ = 0;
				}
				transform(glm::rotate(glm::mat4(1), 0.1f, glm::vec3{0, 0, 1}));
				return true;
			}
			else if(engine::user_event_code<engine::resume_event>::value == e_.code())
			{
				if(!t_)
				{
					t_ = std::make_unique<engine::timer>(scene()->id(), id(), 50, true);
					(*app::logger()) << log_::priority::info << "Timer crated in scene with id: "  << scene()->id() << log_::end_log;
				}

				if(t_)
				{
					t_->start();
					(*app::logger()) << log_::priority::info << "Timer started in scene with id: "  << scene()->id() << log_::end_log;
				}
				return true;
			}
			else if(engine::user_event_code<engine::pause_event>::value == e_.code())
			{
				if(t_)
				{
					t_->stop();
					(*app::logger()) << log_::priority::info << "Timer paused in scene with id: " << scene()->id() << log_::end_log;
				}
				return true;
			}

		}
		catch(std::exception& e)
		{

		}
	}
	return false;
}

void level_loader::render(void)
{
	glNormal3f(0, 0, 1);
	static float eps{0.005};
	static float inner{5};
	static float outter{8};

	glDisable(GL_LIGHTING);
	glColor3f(0,0.2,1);
	glBegin(GL_TRIANGLE_STRIP);
	for(float fi = 0; fi < end_animation_ + eps;  fi += M_PI/20)
	{
		glVertex3f(inner*std::cos(fi),inner*std::sin(fi),0);
		glVertex3f(outter*std::cos(fi), outter*std::sin(fi), 0);
	}
	glEnd();
	glEnable(GL_LIGHTING);
}


