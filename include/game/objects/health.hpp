#ifndef HEALTH_HPP_EOCGAMNV
#define HEALTH_HPP_EOCGAMNV


#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"


class health : public rg::engine::game_object
{
	public:

		health(int time);
		health(const health& obj) = default;

		
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
		
		void display(float value);

		~health(void);
	private:
		float value_;
		int time_;
		int time_left_;
		bool should_render_;
};
#endif /* end of include guard: HEALTH_HPP_EOCGAMNV */
