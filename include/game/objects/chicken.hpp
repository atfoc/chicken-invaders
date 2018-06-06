#ifndef CHICKEN_HPP_8M0HRIXW
#define CHICKEN_HPP_8M0HRIXW

#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"
#include "game/objects/health.hpp"

class game_controler;

class chicken : public rg::engine::game_object
{
	public:
		chicken(rg::engine::model* m, unsigned expl_tex = -1);
		chicken(const chicken& obj) = default;
		
		
		void render(void);
		bool handle_events(const rg::engine::event& e);
		rg::engine::game_object* copy(void);
		rg::engine::box box_mash(void);
		void pos(const glm::vec3& v);
		glm::vec3 pos(void);

		void deal_dmg(float dmg);



		~chicken(void);
	private:
		rg::engine::model* model_;
		game_controler* gc_;
		glm::vec3 pos_;
		glm::mat4 trans_;
		bool first_;
		float health_;
		health* h_;
		unsigned expl_tex_;
};


#endif /* end of include guard: CHICKEN_HPP_8M0HRIXW */
