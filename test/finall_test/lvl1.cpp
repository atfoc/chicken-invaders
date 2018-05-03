#include <glm/gtc/matrix_transform.hpp>
#include "engine/scene.hpp"
#include "engine/game_object.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "player.hpp"
#include "game_controler.hpp"
#include "lvl1.hpp"
#include "cube.hpp"


namespace engine = rg::engine;
namespace support = rg::engine::support;

static glm::vec3 gen_random_cord(int xz, int y);
rg::engine::color gen_random_color(void);

engine::scene* lvl1::scene(void)
{
	engine::scene* s = new engine::scene;

	c = new engine::perspective_camera(	glm::vec3{0,0,0},
										glm::vec3{0,0,1},
										60,
										0,
										1,
										100);

	engine::light* l = new engine::light(glm::vec4{1, 0,0, 0});

	game_controler* gc = new game_controler;
	
	player* ptmp = nullptr;
	
	for(int i = 0; i < 10; ++i)
	{
		ptmp = new player(c, gen_random_cord(40, 10));
		gc->add_player(ptmp);
	}

	ptmp->restore();
	cube* ctmp = nullptr;
	int rtmp;

	for(int i = 0; i < 1000; ++i)
	{
		ctmp = new cube(1,1,1, gen_random_color());
		ctmp->transform(glm::translate(glm::mat4(1), gen_random_cord(40, 10)));
		s->add_object(ctmp);
	
		rtmp = std::rand() % 3;

		if(0 == rtmp)
		{
			gc->add_color(ctmp);
		}
		else if(1 == rtmp)
		{
			gc->add_rotate(ctmp);
		}
		else
		{
			gc->add_rotate(ctmp);
			gc->add_color(ctmp);
		}

	}

	cube* floor = new cube(200, 2, 200, rg::engine::color("#ff0000"));
	floor->transform(glm::translate(glm::mat4(1), glm::vec3(0, -2, 0)));
	s->add_camera(c);
	s->add_light(l);
	s->add_object(gc);
	s->add_object(floor);

	return s;

}

engine::game_object* lvl1::representation(void)
{

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
