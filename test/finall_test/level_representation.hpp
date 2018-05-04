#ifndef LEVEL_REPRESENTATION_HPP_G7JWQ3IS
#define LEVEL_REPRESENTATION_HPP_G7JWQ3IS

#include "engine/game_object.hpp"
#include "engine/color.hpp"


class level_representation : public rg::engine::game_object
{
	public:
		level_representation(bool rotate, bool color);	
		level_representation(const level_representation& l);

		void render(void);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);

		void selected(bool val);
		void on_tick(void);


		~level_representation(void) = default;
	private:
		bool rotate_;
		bool color_;
		rg::engine::color c_;
		bool selected_;
		
};


#endif /* end of include guard: LEVEL_REPRESENTATION_HPP_G7JWQ3IS */	
