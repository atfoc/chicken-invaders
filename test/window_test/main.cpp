#include "engine/application.hpp"
#include "engine/window.hpp"



int main(int argc, char *argv[])
{
	rg::engine::application::init(argc, argv);	
	rg::engine::window* w = new rg::engine::window("hi there");

	rg::engine::application::add_window(w);

	w->show(true);

	rg::engine::application::exec();
	return 0;
}
