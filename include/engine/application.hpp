#ifndef APPLICATION_HPP_PJTWXWVJ
#define APPLICATION_HPP_PJTWXWVJ

#include "engine/id.hpp"


namespace rg
{
namespace engine
{
	class window;
	class event;
	class log;
	class scene;

namespace application
{
	
	void init(int argc, char** argv);
	void add_window(window* w);	
	void add_scene(scene* s);
	bool scene_exist(const uuid& id);
	void remove_window(int id);
	void remove_scene(const uuid& id);
	void post_event(const event& e);
	void exec(void);
	log* logger(void);	

}
}
}
#endif /* end of include guard: APPLICATION_HPP_PJTWXWVJ */
