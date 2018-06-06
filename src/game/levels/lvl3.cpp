#include <stdint.h>
#include <thread>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/scene.hpp"
#include "engine/game_object.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "game/levels/lvl3.hpp"
#include "game/objects/game_controler.hpp"


namespace engine = rg::engine;

engine::scene* lvl3::scene(rg::engine::texture_loader& tl, rg::engine::model_loader& ml)
{
	static_cast<void>(tl);

	engine::scene* s = new rg::engine::scene();
	c = new engine::perspective_camera(glm::vec3{0,10,5}, glm::vec3{0,0,0}, 60, 0, 1, 100);
	s->add_camera(c);
	engine::light* l = new engine::light(glm::vec4{5, 2, 5, 0});
	s->add_light(l);

	game_controler* gc = new game_controler(INT32_MAX);	
	gc->load_models(ml, tl);
	s->add_object(gc);


	
	//std::this_thread::sleep_for(std::chrono::seconds(4));
	return s;

}

level_representation* lvl3::representation(rg::engine::texture_loader& tl, rg::engine::model_loader& ml)
{
	return new level_representation(ml.sphere(), tl.load("./materials/planets/planet3.jpg").second);
}


engine::uuid lvl3::camera(void)
{
	return c->id();
}


