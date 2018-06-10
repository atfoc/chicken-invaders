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

		
		/**
		 * @brief function that is called by the system for object to render
		 */
		void render(void);
		/**
		 * @Brief function that is called by the system for handling events
		 *
		 * @param e event to be handled
		 *
		 * @return true if the events was handled else false
		 */
		bool handle_events(const rg::engine::event& e);

		/**
		 * @briefthis is the function that allows you to
		 *copy an object polymorphicly
		 *
		 * @returncopied object as gameobject
		 */
		rg::engine::game_object* copy(void);

		/**
		 * @briefthis function returns box representation that is used for collision
		 *detection
		 *
		 * @returnbox that actually is rectangle
		 */
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
