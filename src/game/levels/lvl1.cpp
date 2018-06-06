#include <thread>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/scene.hpp"
#include "engine/game_object.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "engine/support/bundle.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/support/camera_controler.hpp"
#include "game/levels/lvl1.hpp"
#include "game/objects/game_controler.hpp"

namespace engine = rg::engine;
namespace support = rg::engine::support;


engine::scene* lvl1::scene(rg::engine::texture_loader& tl, rg::engine::model_loader& ml)
{

	engine::scene* s = new rg::engine::scene();
	c = new engine::perspective_camera(glm::vec3{0,10,5}, glm::vec3{0,0,0}, 60, 0, 1, 100);
	s->add_camera(c);
	engine::light* l = new engine::light(glm::vec4{5, 2, 5, 0});
	s->add_light(l);

	game_controler* gc = new game_controler(1);	
	gc->load_models(ml, tl);
	s->add_object(gc);


	
	//std::this_thread::sleep_for(std::chrono::seconds(4));
	return s;
}

level_representation* lvl1::representation(rg::engine::texture_loader& tl, rg::engine::model_loader& ml)
{
	auto res = tl.load("./materials/planets/planet1.jpg");
	if(!res.first)
	{
		(*rg::engine::application::logger()) << rg::engine::log::priority::debug << "Loading failed" << rg::engine::log::end_log;

	}

	return new level_representation(ml.sphere(), res.second);
}


engine::uuid lvl1::camera(void)
{
	return c->id();
}
