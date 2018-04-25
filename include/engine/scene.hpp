#ifndef SCENE_HPP_M5CHOAAW
#define SCENE_HPP_M5CHOAAW

#include <map>
#include <glm/vec3.hpp>
#include "engine/id.hpp"

namespace rg
{
namespace engine
{
	class game_object;
	class event;
	class camera;
	class window;
	class log;
	class light;

	class scene
	{
		public:
			scene(void);
			scene(const scene& s);
			scene(scene&& s);


			/*TODO: implement this later*/
			scene& operator=(const scene& s) = delete;
			scene& operator=(scene&& s) = delete;

			void add_object(game_object* obj);
			game_object* get_object(const uuid& id);

			std::vector<game_object*> collision(game_object* obj);		

			void broadcast(const event& e); 
			void broadcast_unit_handle(const event& e);
			void notify(const uuid& id, const event& e);
			
			void remove_object(const uuid& id);
			

			void render(void);

			void handle_events(const event& e);

			void add_camera(camera* c);
			camera* get_camera(int id);
			void remove_camera(int id);

			void attach(window* w); 
			void detach(window* w);

			void add_light(light* l);
			void remove_light(int id);

			std::vector<window*> windows(void);

			const uuid& id(void);

			~scene(void);
		private:
			std::map<uuid, std::unique_ptr<game_object>> game_objects_;
			std::vector<window*> attached_windows_;
			std::vector<std::unique_ptr<camera>> cameras_;
			std::vector<std::unique_ptr<light>> lights_;
			uuid id_;
			log* log_;

	};
}
}

#endif /* end of include guard: SCENE_HPP_M5CHOAAW */
