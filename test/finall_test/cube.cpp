#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/log.hpp"
#include "engine/application.hpp"
#include "cube.hpp"
#include "engine/event.hpp"
#include "engine/application.hpp"
#include "engine/scene.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/window.hpp"
#include "engine/light.hpp"


cube::cube(float w, float h, float depth, const rg::engine::color& c) :	w_{w}, h_{h}, d_{depth}, c_(c), frame_{false}
{}

void cube::on_frame(void)
{
}

void cube::render(void)
{

	float tmp[]{0.33f*c_.red(), 0.33f*c_.green(), 0.33f*c_.blue()};
	float tmp1[]{0.66f*c_.red(), 0.66f*c_.green(), 0.66f*c_.blue()};
	float tmp2[]{0.99f*c_.red(), 0.99f*c_.green(), 0.99f*c_.blue()};

	glMaterialfv(GL_FRONT, GL_AMBIENT, tmp);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tmp1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tmp2);
	glMaterialf(GL_FRONT, GL_SHININESS, 20);


	glLineWidth(2);
	glColor3f(1,1,1);
	glNormal3f(0,0, 1);
	glBegin(GL_POLYGON);
		glVertex3f(w_/2,0, d_/2);
		glVertex3f(-w_/2,0, d_/2);
		glVertex3f(-w_/2,h_, d_/2);
		glVertex3f(w_/2,h_, d_/2);
	glEnd();

	if(frame_)
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINE_LOOP);
			glVertex3f(w_/2,0, d_/2);
			glVertex3f(-w_/2,0, d_/2);
			glVertex3f(-w_/2,h_, d_/2);
			glVertex3f(w_/2,h_, d_/2);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	glNormal3f(0,0, -1);
	glBegin(GL_POLYGON);
		glVertex3f(w_/2,0, -d_/2);
		glVertex3f(-w_/2,0, -d_/2);
		glVertex3f(-w_/2,h_, -d_/2);
		glVertex3f(w_/2,h_, -d_/2);

	glEnd();

	if(frame_)
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINE_LOOP);
			glVertex3f(w_/2,0, -d_/2);
			glVertex3f(-w_/2,0, -d_/2);
			glVertex3f(-w_/2,h_, -d_/2);
			glVertex3f(w_/2,h_, -d_/2);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	glNormal3f(1,0, 0);
	glBegin(GL_POLYGON);
		glVertex3f(w_/2,0, d_/2);
		glVertex3f(w_/2,0, -d_/2);
		glVertex3f(w_/2,h_, -d_/2);
		glVertex3f(w_/2,h_, d_/2);
	glEnd();

	if(frame_)
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINE_LOOP);
			glVertex3f(w_/2,0, d_/2);
			glVertex3f(w_/2,0, -d_/2);
			glVertex3f(w_/2,h_, -d_/2);
			glVertex3f(w_/2,h_, d_/2);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	glNormal3f(-1,0, 0);
	glBegin(GL_POLYGON);
		glVertex3f(-w_/2,0, d_/2);
		glVertex3f(-w_/2,0, -d_/2);
		glVertex3f(-w_/2,h_, -d_/2);
		glVertex3f(-w_/2,h_, d_/2);
	glEnd();


	if(frame_)
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-w_/2,0, d_/2);
			glVertex3f(-w_/2,0, -d_/2);
			glVertex3f(-w_/2,h_, -d_/2);
			glVertex3f(-w_/2,h_, d_/2);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	glNormal3f(0,1,0);
	glBegin(GL_POLYGON);
		glVertex3f(-w_/2,h_, -d_/2);
		glVertex3f(w_/2,h_, -d_/2);
		glVertex3f(w_/2,h_, d_/2);
		glVertex3f(-w_/2,h_, d_/2);
	glEnd();

	if(frame_)
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-w_/2,h_, -d_/2);
			glVertex3f(w_/2,h_, -d_/2);
			glVertex3f(w_/2,h_, d_/2);
			glVertex3f(-w_/2,h_, d_/2);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	glNormal3f(0,-1,0);
	glBegin(GL_POLYGON);
		glVertex3f(-w_/2,0, -d_/2);
		glVertex3f(w_/2,0, -d_/2);
		glVertex3f(w_/2,0, d_/2);
		glVertex3f(-w_/2,0, d_/2);
	glEnd();

	if(frame_)
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-w_/2,0, -d_/2);
			glVertex3f(w_/2,0, -d_/2);
			glVertex3f(w_/2,0, d_/2);
			glVertex3f(-w_/2,0, d_/2);
		glEnd();
		glEnable(GL_LIGHTING);
	}

}

void cube::color(const rg::engine::color& c)
{
	c_ = c;
}

bool cube::handle_events(const rg::engine::event& e)
{
	static_cast<void>(e);	
	return false;
}

rg::engine::game_object* cube::copy(void)
{
	return new cube(*this);
}


rg::engine::box cube::box_mash(void)
{
	return rg::engine::box();
}

void cube::frame(bool val)
{
	frame_ = val;
}
