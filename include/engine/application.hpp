#ifndef APPLICATION_HPP_PJTWXWVJ
#define APPLICATION_HPP_PJTWXWVJ

#include <map>
#include <thread>
#include <utility>
#include <boost/any.hpp>
#include "engine/id.hpp"
#include "engine/thread_finished_event.hpp"
#include "engine/upload_texture_event.hpp"


namespace rg {
namespace engine
{
	class window;
	class log;
	class scene;
	class event;

namespace application
{

	extern std::map<uuid, std::thread> threads_;
	extern std::vector<boost::any> delete_at_the_end_;

	void init(int argc, char** argv);
	void add_window(window* w);
	void add_scene(scene* s);
	bool scene_exist(const uuid& id);
	scene* scene(const uuid& id);
	void remove_window(int id);
	void remove_scene(const uuid& id);
	void post_event(const event& e);
	void exec(void);
	log* logger(void);
	template<typename Fn, typename... Args>
	void create_thread(Fn&& f, Args&&... args);
	std::thread::id main_thread_id(void);
	unsigned upload_texture(void);


	/*TODO: not needed any more add t.detach*/
	template<typename Fn, typename... Args>
	void on_thread(uuid th_id, Fn&& f, Args&&... a)
	{
		f(std::forward<Args>(a)...);
		post_event(thread_finished_event(uuids::null_id,th_id));
	}

	template<typename Fn, typename... Args>
	void create_thread(Fn&& f, Args&&... args)
	{
		uuid id = uuids::random_id();
		threads_.insert(std::make_pair(id, std::thread(on_thread<std::decay_t<Fn>, std::decay_t<Args>...>, id, std::forward<Fn>(f),std::forward<Args>(args)...)));
	}

	template <typename T>
	void ensure_delete(T* a)
	{
		delete_at_the_end_.push_back(std::shared_ptr<T>(a));
	}

}
}
}
#endif /* end of include guard: APPLICATION_HPP_PJTWXWVJ */
