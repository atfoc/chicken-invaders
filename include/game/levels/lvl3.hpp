#ifndef LVL3_HPP_PYN8ZJKE
#define LVL3_HPP_PYN8ZJKE



#include "engine/perspective_camera.hpp"
#include "game/level/level.hpp"
#include "game/level/level_representation.hpp"



class lvl3 : public level
{
	public:
		lvl3(void) = default;
		lvl3(const lvl3& l) = default;
	
		rg::engine::scene* scene(rg::engine::texture_loader& tl, rg::engine::model_loader& ml);
		level_representation* representation(rg::engine::texture_loader& tl, rg::engine::model_loader& ml);
		rg::engine::uuid camera(void);

		~lvl3(void) = default;
	private:
		rg::engine::perspective_camera* c;
};
#endif /* end of include guard: LVL3_HPP_PYN8ZJKE */
