#ifndef EXPLOSION_HPP_8OZZG4XX
#define EXPLOSION_HPP_8OZZG4XX


#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"

class explosion : public rg::engine::game_object
{
	public:
		explosion(unsigned tex);
		explosion(const explosion& obj) = default;

		
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




		~explosion(void);
	private:
		unsigned tex_;
		float a_;
		int part_;
		int time_next_;
		int	time_left_; 
};


#endif /* end of include guard: EXPLOSION_HPP_8OZZG4XX */
