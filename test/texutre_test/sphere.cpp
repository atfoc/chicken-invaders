#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/timer_event.hpp"
#include "engine/log.hpp"
#include "engine/application.hpp"
#include "sphere.hpp"
#include "engine/event.hpp"
#include "engine/application.hpp"
#include "engine/scene.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/window.hpp"
#include "engine/light.hpp"


sphere::sphere(float rad, unsigned tex_name)
	:	rad_{rad},
		tex_name_{tex_name}
{}

void sphere::on_frame(void)
{
}


void set_normal_and_vertex(float u, float v, float r)
{
    glNormal3f(
            std::sin(u) * std::sin(v),
            std::cos(u),
            std::sin(u) * std::cos(v)
            );
    glVertex3f(
            r*std::sin(u) * std::sin(v),
            r*std::cos(u),
            r*std::sin(u) * std::cos(v)
            );
}

void sphere::render(void)
{
	static float eps{0.001};

	glEnable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);	
	glBindTexture(GL_TEXTURE_2D, tex_name_);

	GLUquadricObj* s = gluNewQuadric();

	gluQuadricNormals(s, GLU_SMOOTH);
	gluQuadricTexture(s, true);
	
	gluSphere(s, 1, 200, 200);
	gluDeleteQuadric(s);
	glDisable(GL_TEXTURE_2D);
	//for (float u = 0; u < M_PI; u += M_PI/20) 
	//{
	//	glBegin(GL_TRIANGLE_STRIP);
    //    for (float v = 0; v <= M_PI*2 + eps; v += M_PI / 20)
	//	{
	//		//glTexCoord2f(v/(2*M_PI), u/(M_PI));
	//		glTexCoord2f(u/(M_PI),v/(2*M_PI));
    //        set_normal_and_vertex(u, v, rad_);
	//		glTexCoord2f(u/(M_PI),(v+M_PI/20)/(2*M_PI));
    //        set_normal_and_vertex(u + M_PI / 20, v, rad_);
    //    }
    //    glEnd();
    //}
}

bool sphere::handle_events(const rg::engine::event& e)
{
	if(SDL_USEREVENT == e.type())
	{
		auto& e_ = dynamic_cast<const rg::engine::user_event&>(e);
		if(rg::engine::user_event_code<rg::engine::timer_event>::value == e_.code())
		{
			transform(glm::rotate(glm::mat4(1), 0.025f, glm::vec3{0,1,0}));
		}
	}
	return false;
}

rg::engine::game_object* sphere::copy(void)
{
	return new sphere(*this);
}


rg::engine::box sphere::box_mash(void)
{
	return rg::engine::box();
}

