#ifndef SHIP_HPP_CNZBLLX6
#define SHIP_HPP_CNZBLLX6


#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"
#include "game/objects/health.hpp"

class ship : public rg::engine::game_object
{
	public:
		ship(rg::engine::model_loader& ml, bool dummy, unsigned expl_tex = -1);
		ship(const ship& obj) = default;

		
		void render(void);
		bool handle_events(const rg::engine::event& e);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);

		void deal_dmg(float dmg);



		~ship(void);
	private:
		rg::engine::model* model_;
		rg::engine::model* bullet_model_;
		bool dummy_;
		float healt_;
		health* health_obj_;
		unsigned expl_tex_;
};


#endif /* end of include guard: SHIP_HPP_CNZBLLX6 */
