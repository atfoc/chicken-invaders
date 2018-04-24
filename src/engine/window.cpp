#include <GL/gl.h>
#include <SDL2/SDL_timer.h>
#include "engine/application.hpp"
#include "engine/window.hpp"
#include "engine/built_in_event.hpp"
#include "engine/log.hpp"
#include "engine/scene.hpp"
#include "engine/render_event.hpp"


namespace rg
{
namespace engine
{
	static Uint32 on_render_timer(Uint32 interval, void* arg);

	window::window(	const std::string& name,
			int posx , int posy,
			int width, int height)
		:	scene_{nullptr},
			window_{nullptr},
			log_{application::logger()}

	{
		window_ = SDL_CreateWindow(	name.c_str(),
									posx, posy,
									width, height,
									SDL_WINDOW_OPENGL| SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

		if(!window_)
		{
			/*log falied crating of window*/
			std::exit(1);
		}

		gl_context_ = SDL_GL_CreateContext(window_);
		SDL_GL_MakeCurrent(window_, gl_context_);
		glClearColor(1,1,1,1);
		glEnable(GL_DEPTH_TEST);
	}

	window::window(window&& w)
		:	cameras_(std::move(w.cameras_)),
			scene_{w.scene_},
			window_{w.window_},
			gl_context_(w.gl_context_),
			log_{w.log_}

	{
		w.scene_ = nullptr;
		w.window_ = nullptr;
		w.log_ = nullptr;
	}


	void window::attach_scene(scene* s)
	{
		if(!application::scene_exist(s->id()))
		{
			return ;
		}
		/*TODO: if scene is attahced after no scene was attached reset timer for render*/
		detach_scene();

		scene_ = s;
		scene_->attach(this);
	}

	void window::detach_scene(void)
	{
		if(!scene_)
		{
			return ;
		}
		scene_->detach(this);
		cameras_.clear();
		scene_ = nullptr;
	}

	template<typename Callable>
	void window::attach_camera(int cam_id, Callable view_port)
	{
		if(!scene_)
		{
			return ;
		}

		camera* cam{scene_->get_camera(cam_id)};

		if(!cam)
		{
			return ;
		}

		cameras_.push_back(std::make_pair(cam, view_port));
	}

	void window::detach_camera(int cam_id)
	{
		if(!scene_)
		{
			return ;
		}

		camera* cam{scene_->get_camera(cam_id)};

		if(!cam)
		{
			return ;
		}

		auto it = std::find(cameras_.begin(), cameras_.end(), cam);

		if(cameras_.end() != it)
		{
			cameras_.erase(it);
		}
	}


	bool window::handle_events(const event& e)
	{
		switch(e.type())
		{
			case SDL_USEREVENT:
				try
				{

					const user_event& e_{dynamic_cast<const user_event&>(e)};
					if(e_.code() == user_event_code<render_event>::value)
					{
						render();
						(*log_) << log::priority::debug << "Render event recived win_id: " << id() << log::end_log;
					}
				}
				catch(std::exception& c)
				{
					(*log_) << log::priority::danger << c.what() << log::end_log;
				}

				break;
			case SDL_WINDOWEVENT:
				/*TODO: stop rendering when minimized and continue when maximized maybe*/	
				break;
			default:
				if(!scene_)
				{
					break;
				}

				scene_->handle_events(e);
				break;
		}
		return true;
	}

	std::string window::title(void)
	{
		return std::string(SDL_GetWindowTitle(window_));
	}

	void window::title(const std::string& t)
	{
		SDL_SetWindowTitle(window_, t.c_str());
	}

	bool window::is_showing(void)
	{
		return 0 == (SDL_GetWindowFlags(window_) & SDL_WINDOW_HIDDEN);
	}

	void window::show(bool s)
	{
		if(s)
		{
			SDL_ShowWindow(window_);
			application::post_event(render_event(id()));
		}
		else
		{
			SDL_HideWindow(window_);
		}
	}

	int window::id(void)
	{
		return SDL_GetWindowID(window_);

	}

	bool window::has_scene(void)
	{
		return nullptr != scene_;
	}

	void window::render(void)
	{
		if(!scene_)
		{
		//	return ;
		}
		
		int x, y, w,h;
		SDL_GL_MakeCurrent(window_, gl_context_);
		for(auto&& it : cameras_)
		{
			std::tie(x, y, w, h) = it.second(width(), height());
			glViewport(x,y,w,h);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			it.first->apply();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		//	scene_->render();
		}

		if(is_showing())
		{
			void* arg = reinterpret_cast<void*>(id());
			SDL_AddTimer(1000/60, on_render_timer, arg);
		}
	}


	int window::width(void)
	{
		int w, h;
		SDL_GetWindowSize(window_, &w, &h);
		return w;
	}

	int window::height(void)
	{
		int w, h;
		SDL_GetWindowSize(window_, &w, &h);
		return h;
	}


	window::~window(void)
	{

		if(scene_)
		{
			detach_scene();
			cameras_.clear();
		}

		if(window_)
		{
			SDL_GL_DeleteContext(gl_context_);
			SDL_DestroyWindow(window_);
		}
	}

	static Uint32 on_render_timer(Uint32 interval, void* arg)
	{
		static_cast<void>(interval);	
		intptr_t w_id{reinterpret_cast<intptr_t>(arg)};
		
		application::post_event(render_event(w_id));
		
		return 0;
	}
}
}
namespace std
{
	bool operator==(const rg::engine::window::camera_men& cm, rg::engine::camera* e)
	{
		return cm.first == e;

	}

}

