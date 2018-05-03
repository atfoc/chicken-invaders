#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "player.hpp"
#include "engine/event.hpp"
#include "cube.hpp"

player::player(rg::engine::perspective_camera* c, const glm::vec3& pos)
	:	c_{c}, cc_(c), pos_(pos)
{
	c_->eye(pos_);
	cc_.apply();
	point_ = c_->point();
}

void player::save(void)
{
	pos_ = c_->eye();
	point_ = c_->point();
}

void player::restore(void)
{
	c_->eye(pos_);
	cc_.apply();
}

void player::render(void)
{
	cube c(0.3, 0.3, 0.3, rg::engine::color("#00ffff"));	

	glm::mat4 t = glm::translate(glm::mat4(1), pos_);
	glm::mat4 r1 = glm::rotate(glm::mat4(1), cc_.fi(), glm::vec3{0, 1, 0});
	glm::mat4 r2 = glm::rotate(glm::mat4(1), cc_.thet(), glm::vec3{0, 0, 1});
	
	c.transformation(t*r2*r1);
	glPushMatrix();
	c.apply_transformations();
	c.render();
	glPopMatrix();

	glLineWidth(10);
	glColor3f(1, 1, 1);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		glVertex3f(pos_[0], pos_[1], pos_[2]);
		glVertex3f(point_[0], point_[1],point_[2]);
	glEnd();
#ifdef DEBUG_DRAW
	glBegin(GL_LINES);
		glVertex3f(0, 100, 0);
		glVertex3f(pos_[0], pos_[1], pos_[2]);
	glEnd();
#endif
	glEnable(GL_LIGHTING);
}

rg::engine::game_object* player::copy(void)
{
	return new player(*this);
}
rg::engine::box player::box_mash(void)
{
	return rg::engine::box();
}
bool player::handle_events(const rg::engine::event& e)
{
	return cc_.handle_events(e);
}

