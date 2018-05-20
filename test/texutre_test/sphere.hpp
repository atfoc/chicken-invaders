#ifndef CUBE_HPP_QCEKLRIN
#define CUBE_HPP_QCEKLRIN

#include "engine/game_object.hpp"
#include "engine/color.hpp"

class sphere  : public rg::engine::game_object
{
	public:
		sphere(float rad, unsigned tex_name);			
		sphere(const sphere& c) = default;
		
		rg::engine::game_object* copy(void);
		void render(void);
		bool handle_events(const rg::engine::event& e);

		rg::engine::box box_mash(void);

		void on_frame(void);
		~sphere(void) = default;

	private:
		float rad_; 
		unsigned tex_name_;
		
};

#endif /* end of include guard: CUBE_HPP_QCEKLRIN */
