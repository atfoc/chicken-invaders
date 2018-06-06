#ifndef EXPLOSION_HPP_8OZZG4XX
#define EXPLOSION_HPP_8OZZG4XX


#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"

class explosion : public rg::engine::game_object
{
	public:
		explosion(unsigned tex);
		explosion(const explosion& obj) = default;

		
		void render(void);
		bool handle_events(const rg::engine::event& e);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);




		~explosion(void);
	private:
		unsigned tex_;
		float a_;
		int part_;
		int time_next_;
		int	time_left_; 
};


#endif /* end of include guard: EXPLOSION_HPP_8OZZG4XX */
