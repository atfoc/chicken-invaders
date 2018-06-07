#include <map>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <IL/il.h>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/event.hpp"
#include "engine/user_event.hpp"
#include "engine/render_event.hpp"
#include "engine/built_in_event.hpp"
#include "engine/window.hpp"
#include "engine/scene.hpp"
#include "engine/upload_texture_event.hpp"

namespace rg
{
namespace engine
{
namespace application
{

	static log log_(true, "application.log");
	static std::map<Uint32, std::unique_ptr<window>> windows_;
	static std::map<uuid, std::unique_ptr<class scene>> scenes_;	
	std::thread::id main_thread_id_;
	std::map<uuid, std::thread> threads_;
	std::vector<boost::any> delete_at_the_end_;


	void init(int argc, char** argv)
	{
		/* This should be used as a way to set things like logging to a file
		 * random seed and simular*/
		static_cast<void>(argc);
		static_cast<void>(argv);

		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glClearColor(1,1,1,1);

		main_thread_id_ = std::this_thread::get_id();

		ilInit();
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
			
			/*WARNING!!! UGLY BLOCK OF CODE INCOMING*/
			/*TODO: cleanup*/
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
						else if(e_->code() == user_event_code<thread_finished_event>::value)
						{
							thread_finished_event* tf{dynamic_cast<thread_finished_event*>(e_)};
							auto it = threads_.find(tf->th_id());

							if(it != threads_.end())
							{
								it->second.join();
								log_ << log::priority::info << "Succesfuly joined with thread" << log::end_log;
								threads_.erase(it);
							}
						}
						else if(e_->code() == user_event_code<upload_texture_event>::value)
						{
							upload_texture_event* ee_{dynamic_cast<upload_texture_event*>(e_)};

							unsigned tex_name = upload_texture();

							ee_->tex_name(tex_name);
							ee_->done();
							
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
						windows_[e.button.windowID]->handle_events(built_in_event(e)); }
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
					threads_.clear();
					delete_at_the_end_.clear();
					quit = true;	
					break;
			}
		}
	}

	log* logger(void)
	{
		return &log_;
	}

	void add_scene(class scene* s)
	{
		auto it = scenes_.insert(std::make_pair(s->id(),std::unique_ptr<class scene>(s)));

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

	class scene* scene(const uuid& id)
	{
		auto it = scenes_.find(id);

		if(scenes_.end() != it)
		{
			return it->second.get();
		}

		return nullptr;
	}

	std::thread::id main_thread_id(void)
	{
		return main_thread_id_;
	}

	unsigned upload_texture(void)
	{
		unsigned tex_name;

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &tex_name);
		glBindTexture(GL_TEXTURE_2D, tex_name);

		glTexParameteri(GL_TEXTURE_2D,
			                GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,
			                GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,
			                GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,
			                GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
						ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
			             GL_RGB, GL_UNSIGNED_BYTE, ilGetData());
			
		glDisable(GL_TEXTURE_2D);
		return tex_name;

	}
}
}
}
