#ifndef GAME_CONTROLER_HPP_NJBXIHKJ
#define GAME_CONTROLER_HPP_NJBXIHKJ



#include "engine/game_object.hpp"
#include "engine/color.hpp"
#include "engine/timer.hpp"

class game_controler  : public rg::engine::game_object
{
	public:
		game_controler(void);			
		game_controler(const game_controler& c);
		
		rg::engine::game_object* copy(void);
		void render(void);
		bool handle_events(const rg::engine::event& e);
		rg::engine::box box_mash(void);

		void on_frame(void);
		~game_controler(void) = default;
	private:
		std::unique_ptr<rg::engine::timer> t_;
};

#endif /* end of include guard: GAME_CONTROLER_HPP_NJBXIHKJ */
