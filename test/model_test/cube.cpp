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

static bool changed{false};

cube::cube(float w, float h, float depth, const rg::engine::color& c) :	w_{w}, h_{h}, d_{depth}, c_(c)
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

}

bool cube::handle_events(const rg::engine::event& e)
{
	SDL_Event e_;
	switch(e.type())
	{

		case SDL_KEYDOWN:
			e_ = e.sdl_event();
			if(e_.key.keysym.sym == SDLK_LEFT)
			{
				(*rg::engine::application::logger()) <<rg::engine::log::priority::debug <<"Left down recived" << rg::engine::log::end_log;
				transform(glm::rotate(glm::mat4(1), 0.1f, glm::vec3{0,1,0}));	
			}
			else if(e_.key.keysym.sym == SDLK_RIGHT)
			{
				(*rg::engine::application::logger()) <<rg::engine::log::priority::debug <<"Right down recived" << rg::engine::log::end_log;
				transform(glm::rotate(glm::mat4(1), -0.1f, glm::vec3{0,1,0}));	
			}


			break;
		case SDL_KEYUP:
			e_ = e.sdl_event();
			if(e_.key.keysym.sym == SDLK_SPACE)
			{
				if(changed)
				{
					return true;
				}
				changed = true;
				rg::engine::window* w{nullptr};
				auto ws = scene()->windows();
				auto it = std::find_if(ws.begin(), ws.end(), [&](auto&& w_){return w_->id() ==  e_.key.windowID;});

				w = *it;

				rg::engine::scene* s = new rg::engine::scene;
				rg::engine::camera* c1 =
					new rg::engine::perspective_camera(glm::vec3{2,3,5}, glm::vec3{0,0,0}, 60, static_cast<float>(w->width()) / w->height(), 1, 10);

				s->add_camera(c1);
				s->add_light(new rg::engine::light(glm::vec4{-1,0,0,0}));
				s->add_object(new cube(2,2,1, rg::engine::color("#aa0000")));

				rg::engine::application::add_scene(s);

				w->detach_scene();
				w->attach_scene(s);
				w->attach_camera(c1->id(), [](int w, int h){return std::make_tuple(0,0,w,h);});
			}
			else if(e_.key.keysym.sym == SDLK_ESCAPE)
			{
				rg::engine::application::remove_window(e_.key.windowID);
			}
			break;

	}
	return true;
}

rg::engine::game_object* cube::copy(void)
{
	return new cube(*this);
}



