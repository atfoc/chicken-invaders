#ifndef GAME_CONTROLER_HPP_NJBXIHKJ
#define GAME_CONTROLER_HPP_NJBXIHKJ

#include <vector>

#include "engine/game_object.hpp"
#include "engine/color.hpp"
#include "engine/timer.hpp"
#include "engine/model_loader.hpp"
#include "engine/texture_loader.hpp"
#include "game/objects/ship.hpp"
#include "game/objects/chicken.hpp"
#include "game/objects/bullet.hpp"

class game_controler  : public rg::engine::game_object
{
	public:
		game_controler(int wave_number = 1);
		game_controler(const game_controler& c);

		/**
		 * @briefthis is the function that allows you to
		 *copy an object polymorphicly
		 *
		 * @returncopied object as gameobject
		 */
		rg::engine::game_object* copy(void);

		/**
		 * @brief function that is called by the system for object to render
		 */
		void render(void);

		/**
		 * @Brief function that is called by the system for handling events
		 *
		 * @param e event to be handled
		 *
		 * @return true if the events was handled else false
		 */
		bool handle_events(const rg::engine::event& e);

		/**
		 * @briefthis function returns box representation that is used for collision
		 *detection
		 *
		 * @returnbox that actually is rectangle
		 */
		rg::engine::box box_mash(void);
		
		void load_models(rg::engine::model_loader& ml, rg::engine::texture_loader& tl);

		void on_frame(void);
		~game_controler(void) = default;


		friend void init_level_scene(game_controler& gc);
	private:
		std::unique_ptr<rg::engine::timer> t_;
		rg::engine::uuid back_scene_;
		rg::engine::uuid camid_;
		int wave_number_;
		bool game_started_;
		ship* ship_;
		chicken* chicken_;
		std::vector<chicken*> chickens_;
		int time_for_chicken_to_shoot_;
		int time_left_;
		bullet* b_;
};

#endif /* end of include guard: GAME_CONTROLER_HPP_NJBXIHKJ */

