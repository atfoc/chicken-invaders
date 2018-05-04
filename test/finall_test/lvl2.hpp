#ifndef LVL2_HPP_DTEAPXEG
#define LVL2_HPP_DTEAPXEG



#include "engine/perspective_camera.hpp"
#include "level.hpp"



class lvl2 : public level
{
	public:
		lvl2(void) = default;
		lvl2(const lvl2& l) = default;
	
		rg::engine::scene* scene(void);
		level_representation* representation(void);
		rg::engine::uuid camera(void);
		~lvl2(void) = default;
	private:
		rg::engine::perspective_camera* c;
};
#endif /* end of include guard: LVL2_HPP_DTEAPXEG */
