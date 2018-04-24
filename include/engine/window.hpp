#ifndef WINDOW_HPP_O3YX1Q05
#define WINDOW_HPP_O3YX1Q05

#include <string>
#include <functional>
#include <vector>
#include "engine/event.hpp"
#include "engine/id.hpp"
#include "engine/camera.hpp"

namespace rg
{
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
			void detach_scene(void);

			template<typename Callable>
			void attach_camera(int cam_id, Callable view_port); 
			void detach_camera(int cam_id);
				

			bool handle_events(const event& e);

			std::string title(void);
			void title(const std::string& t);
			
			bool is_showing(void);
			void show(bool s);

			int id(void);

			bool has_scene(void);

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
}
}

#endif /* end of include guard: WINDOW_HPP_O3YX1Q05 */
