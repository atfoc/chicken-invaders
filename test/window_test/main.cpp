#include "engine/application.hpp"
#include "engine/window.hpp"



int main(int argc, char *argv[])
{
	rg::engine::application::init(argc, argv);	
	rg::engine::window w("hi there");

	rg::engine::window* w_handle = rg::engine::application::add_window(std::move(w));

	w_handle->show(true);

	rg::engine::application::exec();
	return 0;
}
