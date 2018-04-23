#include "engine/application.hpp"
#include "engine/window.hpp"
#include "engine/log.hpp"
/*#include "engine/scene.hpp"*/


namespace rg
{
namespace engine
{
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

	
	void window::attach_scene(uuid id)
	{
		/*TODO: after implemeting application find scene*/	
	}

	void window::detach_scene(void)
	{
		/*TODO: send detach event to scene*/
		scene_ = nullptr;
	}
	
	template<typename Callable>
	void window::attach_camera(int cam_id, Callable view_port)
	{
		camera* cam{nullptr};
		/*TODO: get camera from scene*/	

		cameras_.push_back(std::make_pair(cam, view_port));
	}

	void window::detach_camera(int cam_id)
	{
		camera* cam{nullptr};
		/*TODO: get camera from scene*/	
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
				/*Handle events like render*/
				break;
			case SDL_WINDOWEVENT:
				(*log_) << log::priority::debug << "Recived event window event in window " << id() << 
				 " with tile " << title() << log::end_log;
				break;
			default:
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
		return 0 != (SDL_GetWindowFlags(window_) & SDL_WINDOW_HIDDEN);	
	}

	void window::show(bool s)
	{
		if(s)
		{
			SDL_ShowWindow(window_);
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
		/*TODO: implement when implement scene*/
	}

	window::~window(void)
	{
		if(window_)
		{
			SDL_GL_DeleteContext(gl_context_);
			SDL_DestroyWindow(window_);
		}
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

