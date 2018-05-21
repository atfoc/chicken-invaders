#include <glm/gtc/matrix_transform.hpp>
#include <IL/il.h>
#include "engine/application.hpp"
#include "engine/window.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "engine/support/camera_controler.hpp"
#include  "engine/timer.hpp"
#include "engine/model_loader.hpp"
#include "engine/texture_loader.hpp"
#include "object.hpp"

unsigned setup_texture(const std::string& file_name);


int main(int argc, char *argv[])
{
	ilInit();
	rg::engine::application::init(argc, argv);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	rg::engine::window* w = new rg::engine::window("Model test");
	rg::engine::application::add_window(w);

	rg::engine::scene* s = new rg::engine::scene();
	rg::engine::application::add_scene(s);

	rg::engine::perspective_camera* pc = new rg::engine::perspective_camera(glm::vec3{-2, 2, 5}, glm::vec3{0, 0, 0}, 60, 0, 1, 1000);
	s->add_camera(pc);

	rg::engine::light* l = new rg::engine::light(glm::vec4{4,2,5,0});
	s->add_light(l);


	rg::engine::support::camera_controler* cc = new rg::engine::support::camera_controler(pc);
	s->add_object(cc);

	
	rg::engine::texture_loader* tl = new rg::engine::texture_loader();
	rg::engine::application::ensure_delete(tl);
	rg::engine::model_loader* ml = new rg::engine::model_loader(tl);
	rg::engine::application::ensure_delete(ml);

	rg::engine::model* m1 = ml->load("./model1/model.obj").second;	
	object* o = new object(m1);
	o->transform(glm::scale(glm::mat4(1), glm::vec3{0.01f, 0.01f, 0.01f}));
	s->add_object(o);

	rg::engine::model* m2 = ml->load("./model2/model.obj").second;
	object* o1 = new object(m2);
	o1->transform(glm::translate(glm::mat4(1), glm::vec3{5,0,0}));
	o1->transform(glm::rotate(glm::mat4(1), 363.0f, glm::vec3{1,0,0}));
	o1->transform(glm::scale(glm::mat4(1), glm::vec3{0.2f, 0.2f, 0.2f}));
	s->add_object(o1);


	rg::engine::timer t(s->id(), rg::engine::uuids::null_id, 50, true);
	t.start();

	w->attach_scene(s->id());
	w->attach_camera(pc->id(),[](int w, int h){return std::make_tuple(0,0, w, h);});


	w->show(true);


	rg::engine::application::exec();
	return 0;
}

unsigned setup_texture(const std::string& file_name)
{
	ILuint pic;
	unsigned tex_name;

	ilGenImages(1, &pic);
	ilBindImage(pic);
	ilLoadImage(file_name.c_str());
	ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
	glGenTextures(1, &tex_name);

	glBindTexture(GL_TEXTURE_2D, tex_name);

//	glTexParameteri(GL_TEXTURE_2D,
//                    GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D,
//                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);

glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
				ilGetData());
            // we also want to be able to deal with odd texture dimensions
            glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
            glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
            glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
            glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
 //                ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
 //                GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

	ilDeleteImages(1, &pic);

	return tex_name;
}
