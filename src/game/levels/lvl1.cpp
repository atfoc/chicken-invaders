#include <thread>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/scene.hpp"
#include "engine/game_object.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "engine/support/bundle.hpp"
#include "game/levels/lvl1.hpp"

namespace engine = rg::engine;
namespace support = rg::engine::support;

static glm::vec3 gen_random_cord(int xz, int y);
rg::engine::color gen_random_color(void);

engine::scene* lvl1::scene(void)
{
	
}

level_representation* lvl1::representation()
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
