#ifndef LVL1_HPP_JV4ETVKY
#define LVL1_HPP_JV4ETVKY

#include "engine/perspective_camera.hpp"
#include "game/level/level.hpp"



class lvl1 : public level
{
	public:
		lvl1(void) = default;
		lvl1(const lvl1& l) = default;
	
		rg::engine::scene* scene(rg::engine::texture_loader& tl, rg::engine::model_loader& ml);
		level_representation* representation(rg::engine::texture_loader& tl, rg::engine::model_loader& ml);
		rg::engine::uuid camera(void);

		~lvl1(void) = default;
	private:
		rg::engine::perspective_camera* c;
};

#endif /* end of include guard: LVL1_HPP_JV4ETVKY */

