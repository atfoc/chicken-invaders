#ifndef LEVEL_SELECTOR_HPP_VTKGNDZI
#define LEVEL_SELECTOR_HPP_VTKGNDZI

#include "engine/game_object.hpp"
#include "engine/texture_loader.hpp"
#include "engine/model_loader.hpp"

class level_representation;
class level;

namespace rg
{
namespace engine
{
	class event;
	class perspective_camera;
	class timer;
}
}

class level_selector : public rg::engine::game_object 
{
	public:
		level_selector(	rg::engine::perspective_camera* cam, float speed, const rg::engine::uuid& loader_scene, 
						const rg::engine::uuid& loader_obj, const rg::engine::uuid& cam_id,
						rg::engine::texture_loader* tl, rg::engine::model_loader* ml);
		level_selector(const level_selector& l) = delete;
		level_selector(level_selector&& l) = default;

		
		bool handle_events(const rg::engine::event& e);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);

		void add_level(level* l);

		~level_selector(void) = default;

	private:
		std::vector<level_representation*> levels_objects_;
		std::vector<std::unique_ptr<level>> levels_;
		int curr_level_;
		bool moving_;
		glm::vec3 target_position_;
		rg::engine::perspective_camera* cam_;
		rg::engine::uuid scene_to_delete_;
		std::unique_ptr<rg::engine::timer> t_;
		float speed_;
		rg::engine::uuid ls_;
		rg::engine::uuid lo_;
		rg::engine::uuid cam_id_;
		rg::engine::texture_loader* tl_;
		rg::engine::model_loader* ml_;
};

#endif /* end of include guard: LEVEL_SELECTOR_HPP_VTKGNDZI */
