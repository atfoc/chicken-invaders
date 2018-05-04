#ifndef GAME_CONTROLER_HPP_NJBXIHKJ
#define GAME_CONTROLER_HPP_NJBXIHKJ



#include <vector>
#include "engine/game_object.hpp"
#include "engine/color.hpp"
#include "engine/timer.hpp"
#include "cube.hpp"
#include "player.hpp"

class game_controler  : public rg::engine::game_object
{
	public:
		game_controler(void);			
		game_controler(const game_controler& c);
		
		rg::engine::game_object* copy(void);
		void render(void);
		bool handle_events(const rg::engine::event& e);
		rg::engine::box box_mash(void);

		void add_rotate(cube* c);
		void add_color(cube* c);
		void add_player(player* p);

		void on_frame(void);
		~game_controler(void) = default;
	private:
		std::unique_ptr<rg::engine::timer> t_;
		std::vector<cube*> rotate_cubes_;
		std::vector<cube*> color_cubes_;
		std::vector<std::unique_ptr<player>> players_;
		size_t curr_player_;
		rg::engine::uuid back_scene_;
		rg::engine::uuid camid_;
};

#endif /* end of include guard: GAME_CONTROLER_HPP_NJBXIHKJ */

