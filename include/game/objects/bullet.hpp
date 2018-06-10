#ifndef BULLET_HPP_SD2YLWE8
#define BULLET_HPP_SD2YLWE8


#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"

/**
 * @brief	class for representing a bullet
 */
class bullet : public rg::engine::game_object
{
	public:
		/**
		 * @brief	this is enumeration describing direction bullet is moving
		 *			up players bullet down enemy bullet
		 */
		enum class direction
		{
			up, down
		};

		/**
		 * @brief	constructor for bullet
		 *
		 * @param m	this is model loaded that will be how your bullet looks
		 * @param max_dist	how long to travel before destroying itself
		 * @param d	direction that bullet travels
		 * @param expl_tex	name of explosion texture that will be displayed when two bullets of
		 *					different direction collide
		 */
		bullet(rg::engine::model* m, float max_dist, direction d, unsigned expl_tex = -1);

		/**
		 * @brief	copy constructor
		 *
		 * @param obj	object to be copied
		 */
		bullet(const bullet& obj) = default;


		
		/**
		 * @brief function that is called by the system for object to render
		 */
		void render(void);

		/**
		 * @brief	function that is called by the system for handling events
		 *
		 * @param e	event to be handled
		 *
		 * @return true if the events was handled else false
		 */
		bool handle_events(const rg::engine::event& e);

		/**
		 * @brief	this is the function that allows you to
		 *			copy an object polymorphicly
		 *
		 * @return	copied object as gameobject
		 */
		rg::engine::game_object* copy(void);

		/**
		 * @brief	this function returns box representation that is used for collision
		 *			detection
		 *
		 * @return	box that actually is rectangle
		 */
		rg::engine::box box_mash(void);





		/**
		 * @brief deconstructor
		 */
		~bullet(void);

	private:
		rg::engine::model* model_;
		float max_dist_;
		float curr_dist_;
		direction dir_;
		unsigned expl_tex_;
};

#endif /* end of include guard: BULLET_HPP_SD2YLWE8 */
