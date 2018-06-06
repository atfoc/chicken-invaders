#include "engine/game_object.hpp"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include "engine/event.hpp"
#include "engine/scene.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"

namespace rg
{
namespace engine
{

	game_object::game_object::game_object(void)
		:	transformation_(1),
			id_(uuids::random_id()),
			visable_{true}
	{}

	game_object::game_object(const game_object& obj)
		:	transformation_(obj.transformation_),
			id_(uuids::random_id()),
			visable_{obj.visable_}
	{}

	game_object::game_object(game_object&& obj)
		:	transformation_(std::move(obj.transformation_)),
			id_(std::move(obj.id_)),
			visable_{obj.visable_}
	{}


	void game_object::on_frame(void)
	{
		/*This is default implementation of this function*/
	}

	bool game_object::handle_events(const event& e)
	{
		/*This is default implementation of this function*/
		static_cast<void>(e);
		return false;
	}

	const glm::mat4& game_object::transformation(void)
	{
		return transformation_;
	}

	void game_object::transformation(const glm::mat4& pos)
	{
		transformation_ = pos;
	}

	void game_object::transform(const glm::mat4x4& pos)
	{
		transformation_ *= pos;
	}

	void game_object::on_collision(game_object& obj)
	{
		static_cast<void>(obj);
		/*This is default implementation of this function*/
	}

	void game_object::render(void)
	{
		/*This is default implementation of this function*/
	}

	void game_object::apply_transformations(void)
	{
		float arr[16];

		const float *sor = glm::value_ptr(transformation_);

		std::copy(sor, sor + 16, arr);

		glMatrixMode(GL_MODELVIEW);
		glMultMatrixf(sor);
	}

	void game_object::show(bool v)
	{
		visable_ = v;		
	}

	bool game_object::visable(void)
	{
		return visable_;
	}

	const uuid& game_object::id(void)
	{
		return id_;
	}


	void game_object::on_attached(rg::engine::scene *s)
	{
		attached_scene_  = s;
	}

	rg::engine::scene* game_object::scene(void)
	{
		return attached_scene_;
	}

	glm::vec3 game_object::position(void)
	{
		return transformation_*glm::vec4{0,0,0, 1};
	}

	void game_object::rtransform(const glm::mat4& pos)
	{
		transformation_ *= pos;
	}

	void game_object::ltransform(const glm::mat4& pos)
	{
		transformation_ = pos * transformation_;
	}
	
}
}
