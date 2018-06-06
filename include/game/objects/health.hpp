#ifndef HEALTH_HPP_EOCGAMNV
#define HEALTH_HPP_EOCGAMNV

#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"

class health : public rg::engine::game_object
{
	public:

		health(int time);
		health(const health& obj) = default;

		
		void render(void);
		bool handle_events(const rg::engine::event& e);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);
		
		void display(float value);

		~health(void);
	private:
		float value_;
		int time_;
		int time_left_;
		bool should_render_;
};
#endif /* end of include guard: HEALTH_HPP_EOCGAMNV */
