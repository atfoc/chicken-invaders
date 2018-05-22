#ifndef LEVEL_REPRESENTATION_HPP_G7JWQ3IS
#define LEVEL_REPRESENTATION_HPP_G7JWQ3IS

#include "engine/game_object.hpp"
#include "engine/color.hpp"


class level_representation : public rg::engine::game_object
{
	public:
		level_representation(unsigned model, unsigned texture);	
		level_representation(const level_representation& l) = default;

		void render(void);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);

		void on_tick(void);


		~level_representation(void) = default;
		
	private:
		unsigned model_;
		unsigned texutre_;
		
};


#endif /* end of include guard: LEVEL_REPRESENTATION_HPP_G7JWQ3IS */	
