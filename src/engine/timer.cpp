#include <time.h>
#include "engine/timer.hpp"
#include "engine/timer_event.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"

namespace rg
{
namespace engine
{
	/*TODO: check timer logic*/
	static Uint32 on_timer(Uint32 interval, void* param);

	;

	timer::timer(const uuid& scene_id, const uuid& obj_id , Uint32 delay, bool continues)
		:	scene_id_(scene_id),
			obj_id_(obj_id),
			sdl_timer_id_{0},
			timer_id_(uuids::random_id()),
			started_{false},
			continues_{continues},
			delay_{delay},
			time_started_{0},
			paused_{false},
			passed_{0},
			ti_{continues_, scene_id_, obj_id_, timer_id_, delay_}
	{}

	timer::timer(timer&& t)
		:	scene_id_(std::move(t.scene_id_)),
			obj_id_(std::move(t.obj_id_)),
			sdl_timer_id_{t.sdl_timer_id_},
			timer_id_(std::move(t.timer_id_)),
			started_{t.started_},
			continues_{t.continues_},
			delay_{t.delay_},
			time_started_{t.time_started_},
			paused_{t.paused_},
			passed_{t.passed_},
			ti_{continues_, scene_id_, obj_id_, timer_id_, delay_}
	{
		t.scene_id_ = t.obj_id_ = t.timer_id_ = uuids::null_id;
		t.sdl_timer_id_ = -1;
		t.started_ = false;
	}


	timer::timer(const timer& t)
		:	scene_id_(t.scene_id_),
			obj_id_(t.obj_id_),
			timer_id_(uuids::random_id()),
			started_{false},
			continues_{t.continues_},
			delay_{t.delay_},
			paused_{false},
			ti_{continues_, scene_id_, obj_id_, timer_id_, delay_}
	{

	}

	void timer::start(void)
	{

		if(started_)
		{
			throw std::runtime_error("Iligal state timer already running");
		}


		sdl_timer_id_ = SDL_AddTimer((!paused_) ? delay_ : delay_*1000 - passed_*1000, on_timer, &ti_);

		paused_ = false;

		time(&time_started_);
		started_ = true;
	}

	void timer::stop(void)
	{
		paused_ = false;

		if(started_)
		{
			SDL_RemoveTimer(sdl_timer_id_);
		}

		started_ = false;
	}

	void timer::pause(void)
	{
		if(!started_ || passed_)
		{
			return ;
		}

		time_t now;
		time(&now);
		int t = delay_  - (now - time_started_);
		if(t < 0)
		{
			stop();
			return ;
		}
		passed_ = now - time_started_;
		started_ = false;
		paused_= true;

		SDL_RemoveTimer(sdl_timer_id_);

	}

	bool timer::started(void) const
	{
		return started_;
	}

	const uuid& timer::id(void)
	{
		return timer_id_;
	}

	timer::~timer(void)
	{
		stop();
	}

	static Uint32 on_timer(Uint32 interval, void* param)
	{
		static_cast<void>(interval);

		timer_info* t{reinterpret_cast<timer_info*>(param)};
		application::post_event(timer_event(t->scene_id, t->obj_id, t->timer_id));
		//(*application::logger()) << log::priority::debug << "t_>cont" << t->cont << log::end_log;
		return (t->cont) ? t->interval : 0;

	}


}
}

