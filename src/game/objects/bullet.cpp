#include <typeinfo>
#include <typeindex>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/event.hpp"
#include "engine/timer_event.hpp"
#include "engine/box.hpp"
#include "engine/scene.hpp"
#include "game/objects/bullet.hpp"
#include "game/objects/chicken.hpp"
#include "game/objects/ship.hpp"
#include "game/objects/explosion.hpp"

bullet::bullet(rg::engine::model* m, float max_dist, direction d, unsigned expl_tex)
	:	model_{m},
		max_dist_{max_dist},
		curr_dist_{0},
		dir_{d},
		expl_tex_{expl_tex}
{}

void bullet::render(void)
{
	glEnable(GL_TEXTURE_2D);
	model_->render();
	glDisable(GL_TEXTURE_2D);
}

bool bullet::handle_events(const rg::engine::event& e)
{
	if(SDL_USEREVENT == e.type())
	{
		const rg::engine::user_event& ue = dynamic_cast<const rg::engine::user_event&>(e);
		if(rg::engine::user_event_code<rg::engine::timer_event>::value == ue.code())
		{
			curr_dist_+= 0.1;
			if(curr_dist_ >= max_dist_)
			{
				scene()->remove_object(id());
			}
			else
			{
				ltransform(glm::translate(glm::mat4(1), glm::vec3{0, 0,(direction::down == dir_ ? 1 : -1) * 0.1}));
				auto col = scene()->collision(this);

				if(!col.empty())
				{
					for(auto it : col)
					{

						if(direction::up == dir_)
						{
							if(auto ptr = dynamic_cast<chicken*>(it))
							{
								ptr->deal_dmg(10);
								scene()->remove_object(id());
								break;	
							}
							else if(auto ptr = dynamic_cast<bullet*>(it))
							{
								if(ptr->dir_ == direction::down)
								{
									scene()->remove_object(ptr->id());
									show(false);
									auto expl = new explosion(expl_tex_);
									expl->ltransform(glm::translate(glm::mat4(1), position()));
									scene()->add_object(expl);
									scene()->remove_object(id());
									return true;
								}
							}
						}
						else
						{
							if(auto ptr= dynamic_cast<ship*>(it))
							{
								ptr->deal_dmg(10);
								scene()->remove_object(id());
								break;	
							}
							else if(auto ptr = dynamic_cast<bullet*>(it))
							{
								
								if(ptr->dir_ == direction::up)
								{
									scene()->remove_object(ptr->id());
									show(false);
									auto expl = new explosion(expl_tex_);
									expl->ltransform(glm::translate(glm::mat4(1), position()));
									scene()->add_object(expl);

									scene()->remove_object(id());
									return true;
								}
							}

						}
						
					}
				}
			}
			return true;
		}

	}
	return false;
}

rg::engine::game_object* bullet::copy(void)
{
	return new bullet(*this);
}

rg::engine::box bullet::box_mash(void)
{
	return rg::engine::box(0.5,0.7, position());
}

bullet::~bullet(void)
{

}
