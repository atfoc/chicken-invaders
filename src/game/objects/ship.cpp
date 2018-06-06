#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/event.hpp"
#include "engine/box.hpp"
#include "engine/resume_event.hpp"
#include "engine/scene.hpp"
#include "game/objects/ship.hpp"
#include "game/objects/bullet.hpp"

ship::ship(rg::engine::model_loader& ml, bool dummy, unsigned expl_tex)
	:	dummy_{dummy},
		healt_{100},
		health_obj_{nullptr},
		expl_tex_{expl_tex}
{

	auto res =ml.load("./materials/ship/model.obj");
	if(res.first)
	{
		(*rg::engine::application::logger()) << rg::engine::log::priority::info << "Ship model loaded sucessfuly" << rg::engine::log::end_log;	
		model_ = res.second;
	}
	else
	{
		(*rg::engine::application::logger()) << rg::engine::log::priority::warning << "Ship model failed to load" << rg::engine::log::end_log;	
		(*rg::engine::application::logger()) << rg::engine::log::priority::danger<< "No default model expect a creash" << rg::engine::log::end_log;	
		/*Set Default model*/
	}

	res = ml.load("./materials/rocket/model.obj");

	if(res.first)
	{
		(*rg::engine::application::logger()) << rg::engine::log::priority::info << "Rocket model loaded sucessfuly" << rg::engine::log::end_log;	
		bullet_model_ = res.second;
	}
	else
	{
		(*rg::engine::application::logger()) << rg::engine::log::priority::warning << "Ship model failed to load" << rg::engine::log::end_log;	
		(*rg::engine::application::logger()) << rg::engine::log::priority::danger<< "No default model expect a creash" << rg::engine::log::end_log;	
		/*Set Default model*/
	}
}

void ship::render(void)
{
	glEnable(GL_TEXTURE_2D);
	model_->render();
	glDisable(GL_TEXTURE_2D);
}

bool ship::handle_events(const rg::engine::event& e)
{
	if(!dummy_ && e.type() == SDL_KEYDOWN)
	{

		SDL_Event se = e.sdl_event();
		if(SDLK_LEFT == se.key.keysym.sym)	
		{
			ltransform(glm::translate(glm::mat4(1), glm::vec3{-0.2, 0, 0}));
			health_obj_->ltransform(glm::translate(glm::mat4(1), glm::vec3{-0.2, 0, 0}));
			return true;
		}
		else if(SDLK_RIGHT == se.key.keysym.sym)
		{
			ltransform(glm::translate(glm::mat4(1), glm::vec3{0.2, 0, 0}));
			health_obj_->ltransform(glm::translate(glm::mat4(1), glm::vec3{0.2, 0, 0}));
			return true;
		}
		else if(SDLK_UP == se.key.keysym.sym)
		{
			ltransform(glm::translate(glm::mat4(1), glm::vec3{0, 0, -0.2}));
			health_obj_->ltransform(glm::translate(glm::mat4(1), glm::vec3{0, 0, -0.2}));
			return true;
		}
		else if(SDLK_DOWN == se.key.keysym.sym)
		{
			ltransform(glm::translate(glm::mat4(1), glm::vec3{0, 0, 0.2}));
			health_obj_->ltransform(glm::translate(glm::mat4(1), glm::vec3{0, 0, 0.2}));
			return true;
		}
		
		
	}
	else if(!dummy_ && e.type() == SDL_KEYUP)
	{
		SDL_Event se = e.sdl_event();

		if(SDLK_SPACE == se.key.keysym.sym)
		{
			auto b = new bullet(bullet_model_, 20, bullet::direction::up, expl_tex_);
			b->ltransform(glm::scale(glm::mat4(1), 0.15f*glm::vec3{1,1,1}));
			b->ltransform(glm::translate(glm::mat4(1), position()+glm::vec3{0.5, 0, 0}));
			(*rg::engine::application::logger()) << rg::engine::log::priority::debug << "bullet" << rg::engine::log::end_log;
			scene()->add_object(b);
		}
	}
	else if(!dummy_ && e.type() == SDL_USEREVENT)
	{
		auto& ue = dynamic_cast<const rg::engine::user_event&>(e);

		if(rg::engine::user_event_code<rg::engine::resume_event>::value == ue.code())
		{
			if(!health_obj_)
			{
				health_obj_ = new health(10);
				scene()->add_object(health_obj_);
				health_obj_->show(false);
				health_obj_->ltransform(glm::translate(glm::mat4(1), position() + glm::vec3{0,1, 0}));
			}
		}
	}
	return false;
}

rg::engine::game_object* ship::copy(void)
{
	return new ship(*this);
}

rg::engine::box ship::box_mash(void)
{
	return rg::engine::box(2,2, position());
}

void ship::deal_dmg(float dmg)
{
	healt_ -= dmg;
	if(healt_ <= 0)
	{
		scene()->remove_object(id());
		return ;
	}
	else
	{
		health_obj_->display(healt_);
	}
}

ship::~ship(void)
{
}
