#ifndef LVL2_HPP_DTEAPXEG
#define LVL2_HPP_DTEAPXEG



#include "engine/perspective_camera.hpp"
#include "engine/model_loader.hpp"
#include "engine/texture_loader.hpp"
#include "game/level/level_representation.hpp"
#include "game/level/level.hpp"

class lvl2 : public level
{
	public:
		lvl2(void) = default;
		lvl2(const lvl2& l) = default;
	
		rg::engine::scene* scene(rg::engine::texture_loader& tl, rg::engine::model_loader& ml);
		level_representation* representation(rg::engine::texture_loader& tl, rg::engine::model_loader& ml);
		rg::engine::uuid camera(void);
		~lvl2(void) = default;
	private:
		rg::engine::perspective_camera* c;
};
#endif /* end of include guard: LVL2_HPP_DTEAPXEG */
