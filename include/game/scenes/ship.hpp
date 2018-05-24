#ifndef SHIP_HPP_CNZBLLX6
#define SHIP_HPP_CNZBLLX6


#include "engine/game_object.hpp"
class game_object
{
	public:
		game_object(void);
		game_object(const game_object& obj);

		
		void on_frame(void);
		void render(void);
		game_object::game_object* copy(void);
		rg::engine::box box_mash(void);

		void apply_transformations(void);

		const glm::mat4& transformation(void);
		void transformation(const glm::mat4& pos);

		void transform(const glm::mat4& pos);

		void show(bool v);
		bool visable(void);

		const uuid& id(void);
		~game_object(void) = default;
};


#endif /* end of include guard: SHIP_HPP_CNZBLLX6 */
