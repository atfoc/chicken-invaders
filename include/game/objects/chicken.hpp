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
		
		
		/**
		 * @brief function that is called by the system for object to render
		 */

		void render(void);
		/**
		 * @Brief function that is called by the system for handling events
		 *
		 * @param e event to be handled
		 *
		 * @return true if the events was handled else false
		 */
		bool handle_events(const rg::engine::event& e);

		/**
		 * @briefthis is the function that allows you to
		 *copy an object polymorphicly
		 *
		 * @returncopied object as gameobject
		 */
		rg::engine::game_object* copy(void);

		/**
		 * @briefthis function returns box representation that is used for collision
		 *detection
		 *
		 * @returnbox that actually is rectangle
		 */
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
