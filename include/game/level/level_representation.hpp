#ifndef LEVEL_REPRESENTATION_HPP_G7JWQ3IS
#define LEVEL_REPRESENTATION_HPP_G7JWQ3IS

/**
 * @briefthis is the function that allows you to
 *copy an object polymorphicly
 *
 * @returncopied object as gameobject
 */
#include "engine/game_object.hpp"
#include "engine/color.hpp"


/**
 * @briefthis is the function that allows you to
 *copy an object polymorphicly
 *
 * @returncopied object as gameobject
 */
class level_representation : public rg::engine::game_object
{
	public:
		level_representation(unsigned model, unsigned texture);	
		level_representation(const level_representation& l) = default;

/**
 * @brief function that is called by the system for object to render
 */

		void render(void);
/**
 * @briefthis is the function that allows you to
 *copy an object polymorphicly
 *
 * @returncopied object as gameobject
 */
		rg::engine::game_object* copy(void);
n/**
 * @briefthis function returns box representation that is used for collision
 *detection
 *
 * @returnbox that actually is rectangle
 */
		rg::engine::box box_mash(void);

		void on_tick(void);


		~level_representation(void) = default;
		
	private:
		unsigned model_;
		unsigned texutre_;
		
};


#endif /* end of include guard: LEVEL_REPRESENTATION_HPP_G7JWQ3IS */	
