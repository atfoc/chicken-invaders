#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/light.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/scene.hpp"
#include "engine/window.hpp"
#include "engine/support/camera_controler.hpp"
#include "cube.hpp"
#include "game_controler.hpp"
#include "floor.hpp"

int main(int argc, char *argv[])
{
	rg::engine::application::init(argc, argv);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	rg::engine::window* w = new rg::engine::window("Model test");
	rg::engine::scene* s = new rg::engine::scene;
	rg::engine::perspective_camera* c = new rg::engine::perspective_camera(glm::vec3{0,0,0}, glm::vec3{0,0,1}, 60, static_cast<float>(w->width()) / w->height(), 1, 100);
	rg::engine::light* l = new rg::engine::light(glm::vec4{1,0,0,0});
	rg::engine::light* l1 = new rg::engine::light(glm::vec4{0,0,0,1});

	rg::engine::support::camera_controler* cc = new rg::engine::support::camera_controler(c, 0.05, 0.05, 0.2);

	cube* cube_1 = new cube(1,1,1, rg::engine::color("#ffff00"));
	cube_1->transform(glm::translate(glm::mat4(1), glm::vec3{0,0,3}));

	cube* cube_2 = new cube(1,1,1, rg::engine::color("#ff00ff"));
	cube_2->transform(glm::translate(glm::mat4(1), glm::vec3{0,0,-3}));

	class floor* wall= new class floor(20,1, 20, rg::engine::color("#0000ff"));
	game_controler* gc = new game_controler();

	wall->transform(glm::translate(glm::mat4(1), glm::vec3{0, -2, 0}));

	s->add_light(l);
	s->add_light(l1);
	s->add_camera(c);
	s->add_object(cc);
	s->add_object(cube_1);
	s->add_object(cube_2);
	s->add_object(wall);
	s->add_object(gc);

	rg::engine::application::add_scene(s);
	rg::engine::application::add_window(w);
	
	w->attach_scene(s);
	w->attach_camera(c->id(),[](int w, int h){return std::make_tuple(0,0, w, h);});

	
	w->show(true);


	rg::engine::application::exec();
	return 0;
}
