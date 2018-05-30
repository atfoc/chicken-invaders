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

class game_controler  : public rg::engine::game_object
{
	public:
		game_controler(int wave_number = 1);
		game_controler(const game_controler& c);

		rg::engine::game_object* copy(void);
		void render(void);
		bool handle_events(const rg::engine::event& e);
		rg::engine::box box_mash(void);
		
		void load_models(rg::engine::model_loader& ml);

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
};

#endif /* end of include guard: GAME_CONTROLER_HPP_NJBXIHKJ */

