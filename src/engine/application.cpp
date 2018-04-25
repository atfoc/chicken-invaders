#include <map>
#include <GL/gl.h>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/event.hpp"
#include "engine/user_event.hpp"
#include "engine/render_event.hpp"
#include "engine/built_in_event.hpp"
#include "engine/window.hpp"
#include "engine/scene.hpp"
#include <SDL2/SDL.h>

namespace rg
{
namespace engine
{
namespace application
{

	static log log_(true, "application.log");
	static std::map<Uint32, std::unique_ptr<window>> windows_;
	static std::map<uuid, std::unique_ptr<scene>> scenes_;	

	void init(int argc, char** argv)
	{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1,1,1,1);
	}

	void add_window(window* w)
	{
		auto it = windows_.insert(std::make_pair(w->id(),std::unique_ptr<window>(w)));

		if(!it.second)
		{
			throw std::runtime_error("Window with this id allready exist!");
		}

	}

	void post_event(const event& e)
	{
		SDL_Event e_ = e.sdl_event();
		
		SDL_PushEvent(&e_);
	}

	void exec(void)
	{
		SDL_Event e;
		bool quit{false};
		while(!quit)
		{
			SDL_WaitEvent(&e);

			switch(e.type)
			{
				case SDL_WINDOWEVENT:
					if(windows_.find(e.window.windowID) != windows_.end())
					{
						windows_[e.window.windowID]->handle_events(built_in_event(e));
					}
					break;
				case SDL_USEREVENT:
					try
					{
						user_event* e_{reinterpret_cast<user_event*>(e.user.data1)};
						if(e_->code() == user_event_code<render_event>::value)
						{
							render_event* r{dynamic_cast<render_event*>(e_)};
							if(windows_.find(r->w_id()) != windows_.end())
							{
								windows_[r->w_id()]->handle_events(*e_);
							}
						}
						else
						{
							if(scene_exist(e_->scene_id()))
							{
								scenes_[e_->scene_id()]->handle_events(*e_);
							}
						}
						delete e_;
					}
					catch(std::exception& e)
					{
						log_ << log::priority::warning << e.what() << log::end_log;
					}
					break;
				case SDL_KEYUP:
					if(windows_.find(e.key.windowID) != windows_.end())
					{
						windows_[e.key.windowID]->handle_events(built_in_event(e));
					}
					break;
				case SDL_KEYDOWN:
					if(windows_.find(e.key.windowID) != windows_.end())
					{
						windows_[e.key.windowID]->handle_events(built_in_event(e));
					}
					break;
				case SDL_MOUSEMOTION:
					if(windows_.find(e.motion.windowID) != windows_.end())
					{
						windows_[e.motion.windowID]->handle_events(built_in_event(e));
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if(windows_.find(e.button.windowID) != windows_.end())
					{
						windows_[e.button.windowID]->handle_events(built_in_event(e));
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(windows_.find(e.button.windowID) != windows_.end())
					{
						windows_[e.button.windowID]->handle_events(built_in_event(e));
					}
					break;
				case SDL_MOUSEWHEEL:
					if(windows_.find(e.wheel.windowID) != windows_.end())
					{
						windows_[e.wheel.windowID]->handle_events(built_in_event(e));
					}
					break;
				case SDL_QUIT:
					windows_.clear();
					scenes_.clear();
					quit = true;	
					break;
			}
		}
	}

	log* logger(void)
	{
		return &log_;
	}

	void add_scene(scene* s)
	{
			auto it = scenes_.insert(std::make_pair(s->id(),std::unique_ptr<scene>(s)));

		if(!it.second)
		{
			throw std::runtime_error("Scene with this id allready exist!");
		}	
	}

	bool scene_exist(const uuid& id)
	{
		return scenes_.find(id) != scenes_.end();	
	}

	void remove_window(int id)
	{
		windows_.erase(id);	
		if(windows_.empty())
		{
			SDL_Event e;
			e.type = SDL_QUIT;
			post_event(built_in_event(e));
		}
	}

	void remove_scene(const uuid& id)
	{
		scenes_.erase(id);
	}
}
}
}
