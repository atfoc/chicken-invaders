#ifndef PLAYER_HPP_9NAOLPB4
#define PLAYER_HPP_9NAOLPB4

#include "engine/support/camera_controler.hpp"
#include "engine/game_object.hpp"

class player : public rg::engine::game_object
{
	public:
		player(rg::engine::perspective_camera* c, const glm::vec3& pos);
		player(const player& p) = default;
		
		void save(void);
		void restore(void);

		void render(void);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);
		bool handle_events(const rg::engine::event& e);

	private:
		rg::engine::perspective_camera* c_;
		rg::engine::support::camera_controler cc_;
		glm::vec3 pos_;
		glm::vec3 point_;

};

#endif /* end of include guard: PLAYER_HPP_9NAOLPB4 */
