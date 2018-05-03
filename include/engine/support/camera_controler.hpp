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
			camera_controler(perspective_camera* c, float h_speed = 0.05f, float v_speed = 0.05f, float speed = 0.2f);
			camera_controler(const camera_controler& c) = default;

			
			bool handle_events(const event& e);
			game_object* copy(void);
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
