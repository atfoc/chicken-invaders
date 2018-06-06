#ifndef BULLET_HPP_SD2YLWE8
#define BULLET_HPP_SD2YLWE8


#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"

class bullet : public rg::engine::game_object
{
	public:
		enum class direction
		{
			up, down
		};

		bullet(rg::engine::model* m, float max_dist, direction d, unsigned expl_tex = -1);
		bullet(const bullet& obj) = default;

		
		void render(void);
		bool handle_events(const rg::engine::event& e);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);




		~bullet(void);
	private:
		rg::engine::model* model_;
		float max_dist_;
		float curr_dist_;
		direction dir_;
		unsigned expl_tex_;
};

#endif /* end of include guard: BULLET_HPP_SD2YLWE8 */
