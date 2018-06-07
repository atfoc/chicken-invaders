#ifndef APPLICATION_HPP_PJTWXWVJ
#define APPLICATION_HPP_PJTWXWVJ
#include <map>
#include <thread>
#include <utility>
#include <boost/any.hpp>
#include "engine/id.hpp"
#include "engine/thread_finished_event.hpp"

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

	/**
	 * @brief function to initialize all systems including SDL2, and engine
	 *
	 * @param argc argument count for program
	 * @param argv argument values idea was to customize initialization  with this values
	*/
	void init(int argc, char** argv);

	/**
	 * @brief this function adds window to application and after that system takes care
	 *			of windows life cycle and memory management, and also this makes window
	 *			receive events
	 *
	 * @param w window to be added
	*/
	void add_window(window* w);

	/**
	 * @brief	this function adds scene to application and after that system takes
	 *			care of scenes life cycle and memory management
	 *
	 * @param s scene to be added
	*/
	void add_scene(scene* s);

	/**
	 * @brief	Checks if scene with given id is managed by the system
	 *
	 * @param id	id to check
	 *
	 * @return	boolean telling dose the scene exist
	*/
	bool scene_exist(const uuid& id);

	/**
	 * @brief	similar to previous function but this returns a handle to scene
	 *
	 * @param id	scene to search for
	 *
	 * @return	scene handle inform of a  pointer
	*/
	scene* scene(const uuid& id);

	/**
	 * @brief	removes window from application management this window will not receive events
	 *			after this
	 * @param id	id returned by SDL2 system uniquely identifying window
	*/
	void remove_window(int id);

	/**
	 * @brief	deletes a scene from a system
	 *
	 * @param id	id of a scene to delete
	*/
	void remove_scene(const uuid& id);

	/**
	 * @brief	this sends event to the system. This function is thread safe
	 *
	 *  @param e	event to post
	*/
	void post_event(const event& e);

	/**
	 * @brief	start the system you must call this
	*/
	void exec(void);

	/**
	 * @brief	Get application level logger
	 *
	 * @return logger handle inform of pointer
	*/
	log* logger(void);

	/**
	 * @brief	this function creates a thread and runs a function in it
	 *
	 * @param f	function to run
	 * @param args	arguments for the function
	*/
	template<typename Fn, typename... Args>
	void create_thread(Fn&& f, Args&&... args);

	/**
	 * @brief	this function should help you check if you are on a main thread or not
	 *
	 * @return	main thread id
	*/
	std::thread::id main_thread_id(void);

	/**
	 * @brief	this function requires from opengl to generate a texture
	 *
	 * @return	texture name
	*/
	unsigned upload_texture(void);


	/*TODO: not needed any more add t.detach*/
	/**
	 * @brief	function that runs your function in a thread and then send event to join thread
	 *			you will not use this function
	 * @param th_id	what thread to join
	 * @param f	what function to run
	 * @param a	arguments to pass to function
	*/
	template<typename Fn, typename... Args>
	void on_thread(uuid th_id, Fn&& f, Args&&... a)
	{
		f(std::forward<Args>(a)...);
		post_event(thread_finished_event(uuids::null_id,th_id));
	}

	/**
	 * @brief	this function creates new thread and runs your function in it. This is what you use
	 *
	 * @param f	what function to run
	 * @param args	what arguments to pass to function
	*/
	template<typename Fn, typename... Args>
	void create_thread(Fn&& f, Args&&... args)
	{
		uuid id = uuids::random_id();
		threads_.insert(std::make_pair(id, std::thread(on_thread<std::decay_t<Fn>, std::decay_t<Args>...>, id, std::forward<Fn>(f),std::forward<Args>(args)...)));
	}

	/**
	 * @brief	This is memory management function. This adds your dynamically allocated value to system and system will delete it
	 *			when it is done. Currently there is no way to undo this once added you have no control of life time.
	 *
	 * @param a	value to manage
	*/
	template <typename T>
	void ensure_delete(T* a)
	{
		delete_at_the_end_.push_back(std::shared_ptr<T>(a));
	}

}
}
}
#endif /* end of include guard: APPLICATION_HPP_PJTWXWVJ */
