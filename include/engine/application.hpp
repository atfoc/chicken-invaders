#ifndef APPLICATION_HPP_PJTWXWVJ
#define APPLICATION_HPP_PJTWXWVJ



namespace rg
{
namespace engine
{
	class window;
	class event;
	class log;
namespace application
{
	
	void init(int argc, char** argv);
	window* add_window(window&& w);	
	void post_event(const event& e);
	void exec(void);
	log* logger(void);	

}
}
}
#endif /* end of include guard: APPLICATION_HPP_PJTWXWVJ */
