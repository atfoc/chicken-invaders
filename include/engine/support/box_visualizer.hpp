#ifndef BOX_VISUALIZER_HPP_DJVUURSM
#define BOX_VISUALIZER_HPP_DJVUURSM


#include <vector>
/**
 * @briefthis is the function that allows you to
 *copy an object polymorphicly
 *
 * @returncopied object as gameobject
 */
#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"

namespace rg
{
namespace engine
{
namespace support
{
	/**
	 * @brief support class that helps visualize box collision shape
	*/
	class box_visualizer : public rg::engine::game_object
	{
		public:
	
			/**
			 * @brief default constructor
			 */
			box_visualizer(void);

			/**
			 * @brief	copy constructor
			 *
			 * @param obj	instance to be copied
			 */
			box_visualizer(const box_visualizer& obj) = default;

	
			
			/**
			 * @brief	this function is called when object needs to be rendered
			 *			It renders all boxes. You don't call this method it is called
			 *			by the system
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
			 * @brief	information for collision detection
			 *
			 * @return	this function returns a box that is of width 0 and height 0 because
			 *			it dose not collide with anything
			 */
			rg::engine::box box_mash(void);

	
	
			/**
			 * @briefthis is the function that allows you to
			 *copy an object polymorphicly
			 *
			 * @returncopied object as gameobject
			 */
			void add_object(game_object* obj);

	
	
	
			/**
			 * @brief deconstructor
			 */
			~box_visualizer(void);

		private:

			std::vector<game_object*> objs_;
	};
}
}
}


#endif /* end of include guard: BOX_VISUALIZER_HPP_DJVUURSM */
