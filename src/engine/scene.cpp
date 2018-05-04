#include <GL/gl.h>
#include "engine/scene.hpp"
#include "engine/event.hpp"
#include "engine/user_event.hpp"
#include "engine/target_event.hpp"
#include "engine/camera.hpp"
#include "engine/window.hpp"
#include "engine/game_object.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/light.hpp"
#include "engine/pause_event.hpp"
#include "engine/resume_event.hpp"
#include "engine/removed_event.hpp"

static const std::array<GLenum, 8> lights_id_{{GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7}};

namespace rg 
{
namespace engine
{
	scene::scene(void)
		:	id_(uuids::random_id()),
			log_{application::logger()}
	{}

	scene::scene(const scene& s)
		:	attached_windows_(s.attached_windows_),
			id_(uuids::random_id()),
			log_{s.log_}

	{
		for(auto&& it: s.game_objects_)
		{
			game_object* obj = it.second->copy();
			add_object(obj);
		}

		for(auto&& it : s.cameras_)
		{
			add_camera(it->copy());
		}

		for(auto&& it: s.lights_)
		{
			lights_.push_back(std::make_unique<light>(*it));
		}
	}

	scene::scene(scene&& s)
		:	game_objects_(std::move(s.game_objects_)),
			attached_windows_(std::move(s.attached_windows_)),
			cameras_(std::move(s.cameras_)),
			lights_(std::move(s.lights_)),
			id_(std::move(s.id_)),
			log_{s.log_}
	{
		s.log_ = nullptr;
	}


	void scene::add_object(game_object* obj)
	{
		game_objects_.insert(std::make_pair(obj->id(), std::unique_ptr<game_object>(obj)));
		obj->on_attached(this);
	}

	game_object* scene::get_object(const uuid& id)
	{
		auto it = game_objects_.find(id);

		if(it != game_objects_.end())
		{
			return it->second.get();
		}

		return nullptr;
	}
	
	std::vector<game_object*> scene::collision(game_object* obj)		
	{
		static_cast<void>(obj);
		/*TODO: implement after implementing collision*/	
		return std::vector<game_object*>();
	}
	
	void scene::broadcast(const event& e) 
	{
		for(auto&& it : game_objects_)
		{
			it.second->handle_events(e);
		}
	}

	void scene::broadcast_unit_handle(const event& e)
	{
		for(auto&& it : game_objects_)
		{
			if(it.second->handle_events(e))
			{
				break;
			}
		}
	}

	void scene::notify(const uuid& id, const event& e)
	{
		auto it = game_objects_.find(id);
		if(it != game_objects_.end())
		{
			it->second->handle_events(e);
		}
	}
	
	void scene::remove_object(const uuid& id)
	{
		
		auto it = game_objects_.find(id);
		if(game_objects_.end() != it)
		{
			broadcast(removed_event(id_, it->first));
			game_objects_.erase(id);
		}


	}
	
	void scene::render(void)
	{
		int i{0};
		for(auto&& it: lights_)
		{
			if(!it->on())
			{
				continue;
			}
			glEnable(lights_id_[i]);
			it->apply(i);
			++i;
		}

		for(auto&& it : game_objects_)
		{
			if(it.second->visable())
			{
				it.second->on_frame();
				glPushMatrix();
				it.second->apply_transformations();
				it.second->render();
				glPopMatrix();
			}
		}

		i = 0;
		for(auto&& it  : lights_)
		{
			if(!it->on())
			{
				continue;
			}
			glDisable(lights_id_[i]);
		}

	}
	
	void scene::handle_events(const event& e)
	{
		switch(e.type())
		{
			case SDL_USEREVENT:
				try
				{
					const target_event& te(dynamic_cast<const target_event&>(e));
					if(te.object_id() != uuids::null_id)
					{
						notify(te.object_id(),e);
					}
					else
					{
						broadcast(e);
					}
				}
				catch(std::exception& exp)
				{
					broadcast_unit_handle(e);
				}
				break;
			default:
				broadcast_unit_handle(e);
				break;	
		}
	}
	
	void scene::add_camera(camera* c)
	{
		cameras_.push_back(std::unique_ptr<camera>(c));		
	}

	camera* scene::get_camera(const uuid& id)
	{
		auto it = std::find_if(cameras_.begin(), cameras_.end(), [&](auto&& i){return i->id() == id;});
		if(cameras_.end() == it)
		{
			return nullptr;
		}
		return it->get();
	}

	void scene::remove_camera(const uuid& id)
	{
		auto it = std::find_if(cameras_.begin(), cameras_.end(), [&](auto&& i){return i->id() == id;});
		if(cameras_.end() == it)
		{
			return ;
		}
		
		for(auto&& i :attached_windows_)
		{
			i->detach_camera((*it)->id());
		}

		broadcast(removed_event(id_, (*it)->id()));
		cameras_.erase(it);


	}
	
	void scene::attach(window* w) 
	{
		if(attached_windows_.empty())		
		{
			broadcast(resume_event(id_));
		}

		attached_windows_.push_back(w);
	}

	void scene::detach(window* w)
	{
		auto it(std::find(attached_windows_.begin(), attached_windows_.end(), w));

		if(it != attached_windows_.end())
		{
			attached_windows_.erase(it);
		}

		if(attached_windows_.empty())
		{
			broadcast(pause_event(id_));
		}

	}
	
	std::vector<window*> scene::windows(void)
	{
		return attached_windows_;	
	}
	
	const uuid& scene::id(void)
	{
		return id_;
	}

	

	void scene::add_light(light* l)
	{
		/*TODO: check if it can be added and return error code*/
		lights_.push_back(std::unique_ptr<light>(l));
	}

	void scene::remove_light(const uuid& id)
	{
		auto it = std::find_if(lights_.begin(), lights_.end(), [&](auto&& i){return i->id() == id;});

		if(lights_.end() != it)
		{
			broadcast(removed_event(id_, (*it)->id()));
			lights_.erase(it);
		}

	}

	scene::~scene(void)
	{
		/*TODO: potential problem with windows iterating over array whre you delete elements*/
		for(auto&& it : attached_windows_)
		{
			it->detach_scene();
		}
		(*log_) << log::priority::debug << "~scene with id: " << id_  << log::end_log;
	}
}
}
