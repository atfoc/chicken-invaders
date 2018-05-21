#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/timer_event.hpp"
#include "engine/log.hpp"
#include "engine/application.hpp"
#include "object.hpp"
#include "engine/event.hpp"
#include "engine/application.hpp"
#include "engine/scene.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/window.hpp"
#include "engine/light.hpp"


object::object(rg::engine::model* m)
	:	m_{m}
{
}


void object::on_frame(void)
{
}



void object::render(void)
{
	glEnable(GL_TEXTURE_2D);
	m_->render();
	glDisable(GL_TEXTURE_2D);
}

bool object::handle_events(const rg::engine::event& e)
{
	if(SDL_USEREVENT == e.type())
	{
		auto& e_ = dynamic_cast<const rg::engine::user_event&>(e);
		if(rg::engine::user_event_code<rg::engine::timer_event>::value == e_.code())
		{
	//		transform(glm::rotate(glm::mat4(1), 0.1f, glm::vec3{0,0,1}));
		}
	}
	return false;
}

rg::engine::game_object* object::copy(void)
{
	return new object(*this);
}


rg::engine::box object::box_mash(void)
{
	return rg::engine::box();
}

