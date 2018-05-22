#ifndef LVL1_HPP_JV4ETVKY
#define LVL1_HPP_JV4ETVKY

#include "engine/perspective_camera.hpp"
#include "game/level/level.hpp"



class lvl1 : public level
{
	public:
		lvl1(void) = default;
		lvl1(const lvl1& l) = default;
	
		rg::engine::scene* scene(void);
		level_representation* representation(void);
		rg::engine::uuid camera(void);

		~lvl1(void) = default;
	private:
		rg::engine::perspective_camera* c;
};

#endif /* end of include guard: LVL1_HPP_JV4ETVKY */

