#ifndef FLOOR_HPP_I8IOBSKE
#define FLOOR_HPP_I8IOBSKE




#include "engine/game_object.hpp"
#include "engine/color.hpp"

class floor  : public rg::engine::game_object
{
	public:
		floor(float w, float h, float depth,const rg::engine::color& c);			
		floor(const floor& c) = default;
		
		rg::engine::game_object* copy(void);
		void render(void);
		bool handle_events(const rg::engine::event& e);

		rg::engine::box box_mash(void);

		void on_frame(void);
		~floor(void) = default;
	private:
		float w_, h_, d_;
		rg::engine::color c_;
		
};

#endif /* end of include guard: FLOOR_HPP_I8IOBSKE */
