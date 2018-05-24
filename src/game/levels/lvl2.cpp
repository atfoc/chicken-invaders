#include <thread>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/scene.hpp"
#include "engine/game_object.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "game/levels/lvl2.hpp"


namespace engine = rg::engine;

engine::scene* lvl2::scene(rg::engine::texture_loader& tl, rg::engine::model_loader& ml)
{
	engine::scene* s = new rg::engine::scene();

	c = new engine::perspective_camera(glm::vec3{1,1,1}, glm::vec3{0,0,0}, 60, 0, 0, 100);

	s->add_camera(c);

	std::this_thread::sleep_for(std::chrono::seconds(4));
	return s;
}

level_representation* lvl2::representation(rg::engine::texture_loader& tl, rg::engine::model_loader& ml)
{
	return new level_representation(ml.sphere(), tl.load("./materials/planets/planet2.jpg").second);
}


engine::uuid lvl2::camera(void)
{
}
