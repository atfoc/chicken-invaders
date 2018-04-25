#ifndef GAME_OBJECT_HPP_2PCDHOIU
#define GAME_OBJECT_HPP_2PCDHOIU

#include <array>
#include <glm/vec3.hpp>
#include "engine/id.hpp"

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
			virtual game_object* copy(void);

			void apply_transformations(void);

			const glm::vec3& position(void);
			void position(const glm::vec3& pos);

			float rotation(void);
			void rotation(float f);

			void scale(float x, float y, float z);
			std::tuple<float, float, float> scale(void);

			void move(const glm::vec4& v);
			void rotate(float f);
			void streach(float x, float y, float z);

			void show(bool v);
			bool visable(void);

			const uuid& id(void);
		private:
			glm::vec3 position_;
			float rot_angle_;
			std::array<float,3> scale_factor_;
			uuid id_;
	};
}
}

#endif /* end of include guard: GAME_OBJECT_HPP_2PCDHOIU */
