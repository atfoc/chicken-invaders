#ifndef WINDOW_HPP_O3YX1Q05
#define WINDOW_HPP_O3YX1Q05

#include <string>
#include <functional>
#include <vector>
#include "engine/event.hpp"
#include "engine/id.hpp"
#include "engine/camera.hpp"
#include "engine/scene.hpp"
namespace rg {
namespace engine
{
	class scene;
	class log;

	class window
	{
		public:
			using camera_men = std::pair<camera*, std::function<std::tuple<int, int, int, int>(int, int)>> ;

			window(	const std::string& name = "hi", 
					int posx = SDL_WINDOWPOS_CENTERED, int posy = SDL_WINDOWPOS_CENTERED, 
					int width = 800, int height = 600);
			window(const window& w) = delete;
			window(window&& w);

			
			window& operator=(const window& w) = delete;
			window& operator=(window&& w) = delete;

			void attach_scene(scene* id);	
			void attach_scene(const uuid& id);
			void attach_scene(const uuid& id, const event& e);
			void detach_scene(void);
			void detach_scene(const event& e);

			template<typename Callable>
			void attach_camera(const uuid& id, Callable view_port); 
			void detach_camera(const uuid& id);
				

/**
 * @Brief function that is called by the system for handling events
 *
 * @param e event to be handled
 *
 * @return true if the events was handled else false
 */
			bool handle_events(const event& e);

			std::string title(void);
			void title(const std::string& t);
			
			bool is_showing(void);
			void show(bool s);

			int id(void);

			bool has_scene(void);

/**
 * @brief function that is called by the system for object to render
 */

			void render(void);

			int width(void);
			int height(void);


			~window(void);


		private:
			std::vector<camera_men> cameras_;
			scene* scene_;
			SDL_Window* window_;
			SDL_GLContext gl_context_;
			log* log_;
	};

	template<typename Callable>
	void window::attach_camera(const uuid& id, Callable view_port)
	{
		if(!scene_)
		{
			return ;
		}

		camera* cam{scene_->get_camera(id)};

		if(!cam)
		{
			return ;
		}

		cameras_.push_back(std::make_pair(cam, view_port));
	}
}
}

#endif /* end of include guard: WINDOW_HPP_O3YX1Q05 */
