#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/event.hpp"
#include "engine/box.hpp"
#include "engine/scene.hpp"
#include "engine/timer_event.hpp"
#include "engine/window.hpp"
#include "game/objects/chicken.hpp"
#include "game/objects/bullet.hpp"
#include "game/objects/explosion.hpp"


chicken::chicken(rg::engine::model* m, unsigned expl_tex)
	:	model_{m},
		first_{true},
		health_{100},
		h_{nullptr},
		expl_tex_{expl_tex}
{}

void chicken::render(void)
{
	glEnable(GL_TEXTURE_2D);
	model_->render();
	glDisable(GL_TEXTURE_2D);
}

bool chicken::handle_events(const rg::engine::event& e)
{
	//static_cast<void>(e);
	if(SDL_USEREVENT == e.type())
	{
		const rg::engine::user_event& ue = dynamic_cast<const rg::engine::user_event&>(e);
		if(rg::engine::user_event_code<rg::engine::timer_event>::value == ue.code())
		{	

			if(first_)
			{
				trans_ = transformation();
				first_ = false;
			}

			
			trans_ = glm::rotate(glm::mat4(1), static_cast<float>(M_PI)/20, glm::vec3{0, 1, 0}) * trans_;
			transformation(	glm::translate(glm::mat4(1), pos_)*
							glm::rotate(glm::mat4(1), static_cast<float>(M_PI/5), glm::vec3{1,0,0})*
							trans_);

		}
	
	}

	return false;
}

rg::engine::game_object* chicken::copy(void)
{
	return new chicken(*this);
}

rg::engine::box chicken::box_mash(void)
{
	return rg::engine::box(2,2, pos_);
}

void chicken::pos(const glm::vec3& v)
{
	pos_ = v;

	if(h_)
	{
		h_->transformation(glm::translate(glm::mat4(1), pos_ + glm::vec3{0, 1.5, 1.7})*
				glm::rotate(glm::mat4(1), static_cast<float>(M_PI)/4, glm::vec3{1,0,0}));
	}
}

glm::vec3 chicken::pos(void)
{
	return pos_;
}

chicken::~chicken(void)
{

}

void chicken::deal_dmg(float dmg)
{
	if(!h_)
	{
		h_ = new health(10);
		scene()->add_object(h_);
		h_->ltransform(glm::rotate(glm::mat4(1), static_cast<float>(M_PI)/4, glm::vec3{1,0,0}));
		h_->ltransform(glm::translate(glm::mat4(1), pos_ + glm::vec3{0, 1.5, 1.7}));
	}
	health_-=dmg;
	h_->display(health_);
	if(health_ <= 0)
	{
		scene()->remove_object(h_->id());
		auto expl = new explosion(expl_tex_);
		expl->ltransform(glm::scale(glm::mat4(1), 1.5f*glm::vec3{1, 1, 1}));
		expl->ltransform(glm::translate(glm::mat4(1), pos_));
		show(false);
		scene()->add_object(expl);
		scene()->remove_object(id());
	}
}
