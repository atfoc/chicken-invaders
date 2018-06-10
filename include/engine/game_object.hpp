#ifndef GAME_OBJECT_HPP_2PCDHOIU
#define GAME_OBJECT_HPP_2PCDHOIU

#include <array>
#include "engine/id.hpp"
#include "engine/box.hpp"
#include <glm/matrix.hpp>



namespace rg
{
namespace engine
{
	class event;
	class scene;


	class game_object
	{
		public:
			game_object(void);
			game_object(const game_object& obj);

			game_object(game_object&& obj);

			
			virtual void on_frame(void);

			/**
			 * @Brief function that is called by the system for handling events
			 *
			 * @param e event to be handled
			 *
			 * @return true if the events was handled else false
			 */
			virtual bool handle_events(const event& e);

			/**
			 * @briefthis is the function that allows you to
			 *copy an object polymorphicly
			 *
			 * @returncopied object as gameobject
			 */
			virtual void on_collision(game_object& obj);

			/**
			 * @brief function that is called by the system for object to render
			 */
			virtual void render(void);
			/*TODO: Remove this from api this is a bad choice
			 * maybe not at the end turns out it is kind of usfull*/

			/**
			 * @briefthis is the function that allows you to
			 *copy an object polymorphicly
			 *
			 * @returncopied object as gameobject
			 */
			virtual game_object* copy(void) = 0;

			/**
			 * @briefthis function returns box representation that is used for collision
			 *detection
			 *
			 * @returnbox that actually is rectangle
			 */
			virtual box box_mash(void) = 0;

			void apply_transformations(void);

			const glm::mat4& transformation(void);
			void transformation(const glm::mat4& pos);

			/* Deprecated. It is same as   rtransform.
			 * Left it in because it was used too offten to be
			 * changed with rtransform*/
			void transform(const glm::mat4& pos);
			void rtransform(const glm::mat4& pos);
			void ltransform(const glm::mat4& pos);

			void show(bool v);
			bool visable(void);

			const uuid& id(void);
			virtual ~game_object(void) = default;
			
			void on_attached(scene *s);

			
			glm::vec3 position(void);


			rg::engine::scene* scene(void);
		private:
			glm::mat4 transformation_;
			uuid id_;
			bool visable_;
			rg::engine::scene* attached_scene_;
	};
}
}

#endif /* end of include guard: GAME_OBJECT_HPP_2PCDHOIU */
