#ifndef CAMERA_CONTROLER_HPP_D6QKHLIC
#define CAMERA_CONTROLER_HPP_D6QKHLIC


#include "engine/game_object.hpp"
#include "engine/perspective_camera.hpp"

namespace rg
{
namespace engine
{
namespace support
{

	class camera_controler : public game_object
	{
		public:
			
			/**
			 * @brief	constructor for camera controler 
			 *
			 * @param c camera to control
			 * @param h_speed	horizontal speed
			 * @param v_speed	vertical speed
			 * @param speed	speed for moving
			 */
			camera_controler(perspective_camera* c, float h_speed = 0.05f, float v_speed = 0.05f, float speed = 0.2f);
			camera_controler(const camera_controler& c) = default;

			

			/**
			 * @Brief function that is called by the system for handling events
			 *
			 * @param e event to be handled
			 *
			 * @return true if the events was handled else false
			 */
			bool handle_events(const event& e);
			/**
			 * @briefthis is the function that allows you to
			 *copy an object polymorphicly
			 *
			 * @returncopied object as gameobject
			 */
			game_object* copy(void);

			/**
			 * @briefthis function returns box representation that is used for collision
			 * detection
			 *
			 * @returnbox that actually is rectangle
			 */
			box box_mash(void);
			
			void apply(void);

			inline float fi(void);
			inline float thet(void);


		private:
			perspective_camera* camera_;
			float h_speed_;
			float v_speed_;
			float speed_;
			float fi_, thet_;
			
	};

	inline float camera_controler::fi(void)
	{
		return fi_;
	}
	
	inline float camera_controler::thet(void)
	{
		return thet_;
	}

}
}
}

#endif /* end of include guard: CAMERA_CONTROLER_HPP_D6QKHLIC */
