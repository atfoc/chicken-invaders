#include "engine/application.hpp"
#include "engine/window.hpp"
#include "lvl1.hpp"


int main(int argc, char *argv[])
{
	rg::engine::application::init(argc, argv);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	rg::engine::window* w = new rg::engine::window("Model test");
	lvl1 l1;

	rg::engine::scene* s = l1.scene();
	rg::engine::uuid c_id = l1.camera();

	rg::engine::application::add_scene(s);
	rg::engine::application::add_window(w);
	
	w->attach_scene(s->id());
	w->attach_camera(c_id,[](int w, int h){return std::make_tuple(0,0, w, h);});

	
	w->show(true);


	rg::engine::application::exec();
	return 0;
}
