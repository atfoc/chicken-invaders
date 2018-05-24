#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/window.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "engine/texture_loader.hpp"
#include "engine/model_loader.hpp"
#include "game/scenes/level_selector.hpp"
#include "game/scenes/level_loader.hpp"
#include "game/levels/lvl1.hpp"
#include "game/levels/lvl2.hpp"
#include "game/levels/lvl3.hpp"

int main(int argc, char *argv[])
{
	rg::engine::application::init(argc, argv);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	/*Creating window*/
	rg::engine::window* w = new rg::engine::window("Chicken Invaders");
	rg::engine::application::add_window(w);


	rg::engine::texture_loader* tl = new rg::engine::texture_loader();	
	rg::engine::application::ensure_delete(tl);

	rg::engine::model_loader* ml = new rg::engine::model_loader(tl);
	rg::engine::application::ensure_delete(ml);

	rg::engine::scene* level_loader_scene = new rg::engine::scene();
	rg::engine::application::add_scene(level_loader_scene);

	rg::engine::perspective_camera* pc1 = new rg::engine::perspective_camera(glm::vec3{0, 0, 15}, glm::vec3{0,0, 0}, 60, 0, 1, 100);
	level_loader_scene->add_camera(pc1);


	level_loader* level_loader_object  =new level_loader();
	level_loader_scene->add_object(level_loader_object);

	rg::engine::scene* level_selector_scene = new rg::engine::scene();
	rg::engine::application::add_scene(level_selector_scene);
	

	rg::engine::perspective_camera* pc = new rg::engine::perspective_camera(glm::vec3{-2, 2, 5}, glm::vec3{0, 0, 0}, 60, 0, 1, 100);
	level_selector_scene->add_camera(pc);

	rg::engine::light* l = new rg::engine::light(glm::vec4{-2,2,5,0});
	level_selector_scene->add_light(l);

	level_selector* level_selector_object = new level_selector(pc, 0.5, level_loader_scene->id(), level_loader_object->id(), pc1->id(), tl, ml);
	level_selector_scene->add_object(level_selector_object);

	level_selector_object->add_level(new lvl1());
	level_selector_object->add_level(new lvl2());
	level_selector_object->add_level(new lvl3());



	/*Attaching scene and camera to window and showing window*/
	w->attach_scene(level_selector_scene->id());
	w->attach_camera(pc->id(),[](int w, int h){return std::make_tuple(0,0, w, h);});
	w->show(true);


	/*Running application*/
	rg::engine::application::exec();
	return 0;
}
