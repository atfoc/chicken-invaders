#ifndef GAME_OBJECT_HPP_2PCDHOIU
#define GAME_OBJECT_HPP_2PCDHOIU

#include <array>
#include "engine/id.hpp"
#include <glm/matrix.hpp>



namespace rg
{
namespace engine
{
	class event;

	class game_object
	{
		public:
			game_object(void);
			game_object(const game_object& obj);
			game_object(game_object&& obj);

			
			virtual void on_frame(void);
			virtual bool handle_events(const event& e);
			virtual void on_collision(game_object& obj);
			virtual void render(void);
			virtual game_object* copy(void) = 0;

			void apply_transformations(void);

			const glm::mat4& transformation(void);
			void transformation(const glm::mat4& pos);

			void transform(const glm::mat4& pos);

			void show(bool v);
			bool visable(void);

			const uuid& id(void);
		private:
			glm::mat4 transformation_;
			uuid id_;
			bool visable_;
	};
}
}

#endif /* end of include guard: GAME_OBJECT_HPP_2PCDHOIU */