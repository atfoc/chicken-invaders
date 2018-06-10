#ifndef LEVEL_LOADER_HPP_ILMR28BJ
#define LEVEL_LOADER_HPP_ILMR28BJ

#include <memory>
/**
 * @briefthis is the function that allows you to
 *copy an object polymorphicly
 *
 * @returncopied object as gameobject
 */
#include "engine/game_object.hpp"
#include "engine/timer.hpp"
#include "engine/support/bundle.hpp"
#include "engine/id.hpp"

/**
 * @briefthis is the function that allows you to
 *copy an object polymorphicly
 *
 * @returncopied object as gameobject
 */
class level_loader : public rg::engine::game_object
{
	public:
		level_loader(void);
		level_loader(const level_loader& l);

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

/**
 * @Brief function that is called by the system for handling events
 *
 * @param e event to be handled
 *
 * @return true if the events was handled else false
 */
		bool handle_events(const rg::engine::event& e);
/**
 * @brief function that is called by the system for object to render
 */

		void render(void);

		~level_loader(void) = default;
		
	private:
		rg::engine::uuid back_scene_id_;
		rg::engine::uuid camid_;
		std::unique_ptr<rg::engine::timer> t_;
		float end_animation_;
		
};


#endif /* end of include guard: LEVEL_LOADER_HPP_ILMR28BJ */
