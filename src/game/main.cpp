#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/window.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "engine/texture_loader.hpp"
#include "engine/model_loader.hpp"

#include "game/level/level_representation.hpp"

int main(int argc, char *argv[])
{
	rg::engine::application::init(argc, argv);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	/*Creating window*/
	rg::engine::window* w = new rg::engine::window("Chicken Invaders");
	rg::engine::application::add_window(w);

	rg::engine::scene* s = new rg::engine::scene();
	rg::engine::application::add_scene(s);

	rg::engine::perspective_camera* pc = new rg::engine::perspective_camera(glm::vec3{-2, 2, 5}, glm::vec3{0, 0, 0}, 60, 0, 1, 100);
	s->add_camera(pc);

	rg::engine::light* l = new rg::engine::light(glm::vec4{-1,2,0,0});
	s->add_light(l);

	rg::engine::texture_loader* tl = new rg::engine::texture_loader();	
	rg::engine::application::ensure_delete(tl);

	rg::engine::model_loader* ml = new rg::engine::model_loader(tl);
	rg::engine::application::ensure_delete(ml);


	unsigned tex = tl->load("./materials/planets/planet1.jpg").second;
	unsigned mod = ml->sphere();
	level_representation* l1 = new level_representation(mod, tex); 
	s->add_object(l1);

	tex = tl->load("./materials/planets/planet2.jpg").second;
	mod = ml->sphere();
	level_representation* l2 = new level_representation(mod, tex); 
	l2->transform(glm::translate(glm::mat4(1), glm::vec3{3, 0, 0}));
	s->add_object(l2);

	tex = tl->load("./materials/planets/planet3.jpg").second;
	mod = ml->sphere();
	level_representation* l3 = new level_representation(mod, tex); 
	l3->transform(glm::translate(glm::mat4(1), glm::vec3{6, 0, 0}));
	s->add_object(l3);



	/*Attaching scene and camera to window and showing window*/
	w->attach_scene(s->id());
	w->attach_camera(pc->id(),[](int w, int h){return std::make_tuple(0,0, w, h);});
	w->show(true);


	/*Running application*/
	rg::engine::application::exec();
	return 0;
}
