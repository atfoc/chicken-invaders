#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/window.hpp"
#include "engine/orthogonal_camera.hpp"
#include "level_loader.hpp"
#include "level_representation.hpp"
#include "lvl1.hpp"
#include "lvl2.hpp"
#include "lvl3.hpp"
#include "engine/light.hpp"
#include "level_selector.hpp"


int main(int argc, char *argv[])
{
	rg::engine::application::init(argc, argv);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	rg::engine::window* w = new rg::engine::window("Model test");

	rg::engine::application::add_window(w);

	rg::engine::scene* s = new rg::engine::scene();
	rg::engine::application::add_scene(s);

	rg::engine::perspective_camera* pc = new rg::engine::perspective_camera(glm::vec3{-2, 2, 5}, glm::vec3{0, 0, 0}, 60, 0, 1, 100);
	rg::engine::light* l = new rg::engine::light(glm::vec4{-1,2,0,0});


	s->add_camera(pc);
	s->add_light(l);

	rg::engine::scene* loader_scene = new rg::engine::scene();
	rg::engine::application::add_scene(loader_scene);	

	//rg::engine::orthogonal_camera* oc = new rg::engine::orthogonal_camera(-20, 20, 15, -15, 0, 5);
	rg::engine::perspective_camera* oc = new rg::engine::perspective_camera(glm::vec3{0, 0, -20}, glm::vec3{0, 0, 0}, 60, 0, 1, 100);
	level_loader* ll = new level_loader();	
	loader_scene->add_camera(oc);
	loader_scene->add_object(ll);


	level_selector* ls = new level_selector(pc, 0.5, loader_scene->id(), ll->id(), oc->id());

	s->add_object(ls);
	ls->add_level(new lvl1());
	ls->add_level(new lvl2());
	ls->add_level(new lvl3());


	w->attach_scene(s->id());
	w->attach_camera(pc->id(),[](int w, int h){return std::make_tuple(0,0, w, h);});

	
	w->show(true);


	rg::engine::application::exec();
	return 0;
}
