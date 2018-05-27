#ifndef SHIP_HPP_CNZBLLX6
#define SHIP_HPP_CNZBLLX6


#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"

class ship : public rg::engine::game_object
{
	public:
		ship(rg::engine::model_loader* ml);
		ship(const ship& obj) = default;

		
		void render(void);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);




		~ship(void);
	private:
		rg::engine::model* model_;
};


#endif /* end of include guard: SHIP_HPP_CNZBLLX6 */
