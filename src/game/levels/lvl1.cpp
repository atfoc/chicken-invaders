#include <thread>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/scene.hpp"
#include "engine/game_object.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "engine/support/bundle.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "game/levels/lvl1.hpp"
#include "game/scenes/game_controler.hpp"

namespace engine = rg::engine;
namespace support = rg::engine::support;

static glm::vec3 gen_random_cord(void);
rg::engine::color gen_random_color(void);

engine::scene* lvl1::scene(rg::engine::texture_loader& tl, rg::engine::model_loader& ml)
{
	engine::scene* s = new rg::engine::scene();

	c = new engine::perspective_camera(glm::vec3{1,1,1}, glm::vec3{0,0,0}, 60, 0, 0, 100);

	s->add_camera(c);
	s->add_object(new game_controler());

	std::this_thread::sleep_for(std::chrono::seconds(4));
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

static glm::vec3 gen_random_cord(int xz, int yl)
{
	int x =  std::rand() % xz;	
	int z =  std::rand() % xz;	
	int y =  std::rand() % yl;	


	return glm::vec3{x, y, z};
}
