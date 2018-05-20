#include <glm/gtc/matrix_transform.hpp>
#include <IL/il.h>
#include "engine/application.hpp"
#include "engine/window.hpp"
#include "engine/perspective_camera.hpp"
#include "engine/light.hpp"
#include "engine/support/camera_controler.hpp"
#include  "engine/timer.hpp"
#include "sphere.hpp"

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

	rg::engine::perspective_camera* pc = new rg::engine::perspective_camera(glm::vec3{-2, 2, 5}, glm::vec3{0, 0, 0}, 60, 0, 1, 100);
	rg::engine::light* l = new rg::engine::light(glm::vec4{-1,2,0,0});

	sphere *sf = new sphere(1, setup_texture("test.jpg"));

	rg::engine::support::camera_controler* cc = new rg::engine::support::camera_controler(pc);

	s->add_camera(pc);
	s->add_light(l);
	s->add_object(cc);

	s->add_object(sf);
	sphere *sf1 = new sphere(1, setup_texture("test1.jpg"));
	sf1->transform(glm::translate(glm::mat4(1), glm::vec3{2.5, 0, 0}));
	s->add_object(sf1);
	sphere *sf2 = new sphere(1, setup_texture("test2.jpg"));
	sf2->transform(glm::translate(glm::mat4(1), glm::vec3{5, 0, 0}));
	s->add_object(sf2);

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

	glGenTextures(1, &tex_name);

	glBindTexture(GL_TEXTURE_2D, tex_name);

	glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
                 GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

	ilDeleteImages(1, &pic);

	return tex_name;
}
