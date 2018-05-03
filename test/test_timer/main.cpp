#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "engine/application.hpp"
#include "engine/light.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/scene.hpp"
#include "engine/window.hpp"
#include "cube.hpp"
#include "rotate_event.hpp"
#include "engine/render_event.hpp"
#include "game_controler.hpp"


int main(int argc, char *argv[])
{
	rg::engine::application::init(argc, argv);

	rg::engine::window* w = new rg::engine::window("Model test");
	rg::engine::scene* s = new rg::engine::scene;
	rg::engine::camera* c = new rg::engine::perspective_camera(glm::vec3{2,0,5}, glm::vec3{0,0,0}, 60, static_cast<float>(w->width()) / w->height(), 1, 10);
	rg::engine::camera* c1 = new rg::engine::perspective_camera(glm::vec3{2,3,5}, glm::vec3{0,0,0}, 60, static_cast<float>(w->width()) / w->height(), 1, 10);
	rg::engine::camera* c2 = new rg::engine::perspective_camera(glm::vec3{2,3,5}, glm::vec3{0,0,0}, 60, static_cast<float>(w->width()) / w->height(), 1, 10);
	rg::engine::light* l = new rg::engine::light(glm::vec4{1,0,0,0});

	rg::engine::window* w1 = new rg::engine::window("Model test");

	s->add_light(l);
	s->add_camera(c);
	s->add_camera(c1);
	s->add_camera(c2);

	s->add_object(new cube(2,2,1, rg::engine::color("#00aaff")));
	s->add_object(new game_controler());
	rg::engine::application::add_scene(s);
	rg::engine::application::add_window(w);
	rg::engine::application::add_window(w1);
	
	w->attach_scene(s);
	w->attach_camera(c->id(),[](int w, int h){return std::make_tuple(0,0, w, h/2);});
	w->attach_camera(c1->id(),[](int w, int h){return std::make_tuple(0,h/2, w, h/2);});

	w1->attach_scene(s);
	w1->attach_camera(c2->id(),[](int w, int h){return std::make_tuple(0,0, w, h);});
	
	w->show(true);
	w1->show(true);


	rg::engine::application::exec();
	return 0;
}


