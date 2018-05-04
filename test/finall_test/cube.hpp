#ifndef CUBE_HPP_QCEKLRIN
#define CUBE_HPP_QCEKLRIN

#include "engine/game_object.hpp"
#include "engine/color.hpp"

class cube  : public rg::engine::game_object
{
	public:
		cube(float w, float h, float depth,const rg::engine::color& c);			
		cube(const cube& c) = default;
		
		rg::engine::game_object* copy(void);
		void render(void);
		bool handle_events(const rg::engine::event& e);

		void color(const rg::engine::color& c);
		rg::engine::box box_mash(void);

		void frame(bool val);
		void on_frame(void);
		~cube(void) = default;

	private:
		float w_, h_, d_;
		rg::engine::color c_;
		bool frame_;
		
};

#endif /* end of include guard: CUBE_HPP_QCEKLRIN */
