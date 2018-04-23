#include <map>
#include <GL/gl.h>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/event.hpp"
#include "engine/built_in_event.hpp"
#include "engine/window.hpp"
#include <SDL2/SDL.h>

namespace rg
{
namespace engine
{
namespace application
{

	static log log_(true, "application.log");
	static std::map<Uint32, window> windows_;
	
	void init(int argc, char** argv)
	{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1,1,1,1);
	}

	window* add_window(window&& w)
	{
		auto it = windows_.insert(std::make_pair(w.id(), std::move(w)));

		if(!it.second)
		{
			throw std::runtime_error("Window with this id allready exist!");
		}

		return &it.first->second;
	}

	void post_event(const event& e)
	{
		SDL_Event e_ = e.sdl_event();
		
		SDL_PushEvent(&e_);
	}

	void exec(void)
	{
		SDL_Event e;
		while(true)
		{
			SDL_WaitEvent(&e);

			switch(e.type)
			{
				case SDL_WINDOWEVENT:
					windows_[e.key.windowID].handle_events(built_in_event(e));
					break;
				case SDL_USEREVENT:
					/* TODO: handle user events
					 * extract check if it is thread render or timer event
					 * process them if not pass it on to scene*/
					break;
				case SDL_KEYUP:
					windows_[e.key.windowID].handle_events(built_in_event(e));
					break;
				case SDL_KEYDOWN:
					windows_[e.key.windowID].handle_events(built_in_event(e));
					break;
				case SDL_MOUSEMOTION:
					windows_[e.key.windowID].handle_events(built_in_event(e));
					break;
				case SDL_MOUSEBUTTONUP:
					windows_[e.key.windowID].handle_events(built_in_event(e));
					break;
				case SDL_MOUSEBUTTONDOWN:
					windows_[e.key.windowID].handle_events(built_in_event(e));
					break;
				case SDL_MOUSEWHEEL:
					windows_[e.key.windowID].handle_events(built_in_event(e));
					break;
			}
		}
	}

	log* logger(void)
	{
		return &log_;
	}

}
}
}
