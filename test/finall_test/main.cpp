#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/window.hpp"
#include "engine/orthogonal_camera.hpp"
#include "level_loader.hpp"
#include "level_representation.hpp"
#include "lvl1.hpp"
#include "engine/light.hpp"


int main(int argc, char *argv[])
{
	rg::engine::application::init(argc, argv);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	rg::engine::window* w = new rg::engine::window("Model test");

	rg::engine::scene* s = new rg::engine::scene();
	rg::engine::perspective_camera* pc = new rg::engine::perspective_camera(glm::vec3{-2, 2, 5}, glm::vec3{0, 0, 0}, 60, 0, 1, 100);

	rg::engine::application::add_scene(s);
	rg::engine::application::add_window(w);
	rg::engine::light* l = new rg::engine::light(glm::vec4{-1,2,0,0});

	level_representation* l1 = new level_representation(false, true);
	level_representation* l2 = new level_representation(true, false);
	level_representation* l3 = new level_representation(true, true);
	
	s->add_camera(pc);
	s->add_object(l1);
	s->add_light(l);
	l2->transform(glm::translate(glm::mat4(1), glm::vec3{2.0, 0, 0}));
	s->add_object(l2);
	l3->transform(glm::translate(glm::mat4(1), glm::vec3{4.0, 0, 0}));
	s->add_object(l3);

	w->attach_scene(s->id());
	w->attach_camera(pc->id(),[](int w, int h){return std::make_tuple(0,0, w, h);});

	
	w->show(true);


	rg::engine::application::exec();
	return 0;
}
