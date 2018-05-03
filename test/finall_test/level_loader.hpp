#ifndef LEVEL_LOADER_HPP_ILMR28BJ
#define LEVEL_LOADER_HPP_ILMR28BJ

#include <memory>
#include "engine/game_object.hpp"
#include "engine/timer.hpp"
#include "engine/support/bundle.hpp"
#include "engine/id.hpp"

class level_loader : public rg::engine::game_object
{
	public:
		level_loader(void);
		level_loader(const level_loader& l);

		rg::engine::game_object* copy(void);	
		rg::engine::box box_mash(void);

		bool handle_events(const rg::engine::event& e);
		void render(void);

		~level_loader(void) = default;
		
	private:
		rg::engine::uuid back_scene_id_;
		std::unique_ptr<rg::engine::timer> t_;
		float end_animation_;
		
};


#endif /* end of include guard: LEVEL_LOADER_HPP_ILMR28BJ */
