#include <glm/gtc/matrix_transform.hpp>
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/event.hpp"
#include "engine/timer_event.hpp"
#include "engine/box.hpp"
#include "engine/scene.hpp"
#include "game/objects/explosion.hpp"
#include "game/objects/chicken.hpp"
#include "game/objects/ship.hpp"

explosion::explosion(unsigned tex)
	:	tex_{tex},
		a_{65.0/256},
		part_{0},
		time_next_{1},
		time_left_{time_next_}
{}

void explosion::render(void)
{
	float col_ = part_ % 4;
	float row_ = part_ / 4;

	glm::vec2 tl{col_*a_, row_*a_};
	glm::vec2 tr{(col_+1)*a_, row_*a_};
	glm::vec2 bl{col_*a_, (row_+1)*a_};
	glm::vec2 br{(col_+1)*a_, (row_+1)*a_};

	glEnable(GL_TEXTURE_2D);
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, tex_);
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
		glTexCoord2f(tl.x, tl.y);
		glVertex3f(-0.5, 0, -0.5);

		glTexCoord2f(tr.x, tr.y);
		glVertex3f(0.5, 0, -0.5);

		glTexCoord2f(br.x, br.y);
		glVertex3f(0.5, 0, 0.5);

		glTexCoord2f(bl.x, bl.y);
		glVertex3f(-0.5, 0, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

bool explosion::handle_events(const rg::engine::event& e)
{
	if(SDL_USEREVENT == e.type())
	{
		const rg::engine::user_event& ue = dynamic_cast<const rg::engine::user_event&>(e);
		if(rg::engine::user_event_code<rg::engine::timer_event>::value == ue.code())
		{
			if(part_ < 16)
			{
				--time_left_;
				if(time_left_ <= 0)
				{
					time_left_ = time_next_;
					++part_;
				}
			}
			else
			{
				scene()->remove_object(id());
			}
			return true;
		}

	}
	return false;
}

rg::engine::game_object* explosion::copy(void)
{
	return new explosion(*this);
}

rg::engine::box explosion::box_mash(void)
{
	return rg::engine::box();
}

explosion::~explosion(void)
{

}
