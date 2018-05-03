#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/log.hpp"
#include "engine/application.hpp"
#include "floor.hpp"
#include "engine/event.hpp"
#include "engine/application.hpp"
#include "engine/scene.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/window.hpp"
#include "engine/light.hpp"
#include "rotate_event.hpp"

static bool changed{false};

floor::floor(float w, float h, float depth, const rg::engine::color& c) :	w_{w}, h_{h}, d_{depth}, c_(c)
{}

void floor::on_frame(void)
{
}

void floor::render(void)
{

	float tmp[]{0.33f*c_.red(), 0.33f*c_.green(), 0.33f*c_.blue()};
	float tmp1[]{0.66f*c_.red(), 0.66f*c_.green(), 0.66f*c_.blue()};
	float tmp2[]{0.99f*c_.red(), 0.99f*c_.green(), 0.99f*c_.blue()};

	glMaterialfv(GL_FRONT, GL_AMBIENT, tmp);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tmp1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tmp2);
	glMaterialf(GL_FRONT, GL_SHININESS, 20);


	glNormal3f(0,0, 1);
	glBegin(GL_POLYGON);
		glVertex3f(w_/2,0, d_/2);
		glVertex3f(-w_/2,0, d_/2);
		glVertex3f(-w_/2,h_, d_/2);
		glVertex3f(w_/2,h_, d_/2);
	glEnd();

	glNormal3f(0,0, -1);
	glBegin(GL_POLYGON);
		glVertex3f(w_/2,0, -d_/2);
		glVertex3f(-w_/2,0, -d_/2);
		glVertex3f(-w_/2,h_, -d_/2);
		glVertex3f(w_/2,h_, -d_/2);

	glEnd();


	glNormal3f(1,0, 0);
	glBegin(GL_POLYGON);
		glVertex3f(w_/2,0, d_/2);
		glVertex3f(w_/2,0, -d_/2);
		glVertex3f(w_/2,h_, -d_/2);
		glVertex3f(w_/2,h_, d_/2);
	glEnd();

	glNormal3f(-1,0, 0);
	glBegin(GL_POLYGON);
		glVertex3f(-w_/2,0, d_/2);
		glVertex3f(-w_/2,0, -d_/2);
		glVertex3f(-w_/2,h_, -d_/2);
		glVertex3f(-w_/2,h_, d_/2);
	glEnd();

	glNormal3f(0,1,0);
	glBegin(GL_POLYGON);
		glVertex3f(-w_/2,h_, -d_/2);
		glVertex3f(w_/2,h_, -d_/2);
		glVertex3f(w_/2,h_, d_/2);
		glVertex3f(-w_/2,h_, d_/2);
	glEnd();

	glNormal3f(0,-1,0);
	glBegin(GL_POLYGON);
		glVertex3f(-w_/2,0, -d_/2);
		glVertex3f(w_/2,0, -d_/2);
		glVertex3f(w_/2,0, d_/2);
		glVertex3f(-w_/2,0, d_/2);
	glEnd();
}

bool floor::handle_events(const rg::engine::event& e)
{
	
	return false;
}

rg::engine::game_object* floor::copy(void)
{
	return new floor(*this);
}


rg::engine::box floor::box_mash(void)
{
	return rg::engine::box();
}

