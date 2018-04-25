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
		/*TODO: implement copying of game_objects and cameras */
		for(auto&& it: s.game_objects_)
		{
			game_object* obj = it.second->copy();
			add_object(obj);
		}
	}

	scene::scene(scene&& s)
		:	game_objects_(std::move(s.game_objects_)),
			attached_windows_(std::move(s.attached_windows_)),
			cameras_(std::move(s.cameras_)),
			id_(std::move(s.id_)),
			log_{s.log_}
	{
		s.log_ = nullptr;
	}


	void scene::add_object(game_object* obj)
	{
		game_objects_.insert(std::make_pair(obj->id(), std::unique_ptr<game_object>(obj)));
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
		game_objects_.erase(id);
	}
	
	void scene::render(void)
	{
		/*TODO:Setup lights*/
		for(auto&& it : game_objects_)
		{
			glPushMatrix();
			it.second->apply_transformations();
			it.second->render();
			glPopMatrix();
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
					notify(te.object_id(),e);
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

	camera* scene::get_camera(int id)
	{
		if(id < 0 || id >= cameras_.size())
		{
			return nullptr;
		}
		
		return cameras_[id].get();
	}

	void scene::remove_camera(int id)
	{
		if(id < 0 || id >= cameras_.size())
		{
			return ;
		}

		cameras_.erase(cameras_.begin() + id);
		

	}
	
	void scene::attach(window* w) 
	{
		if(attached_windows_.empty())		
		{
			/*TODO: broadcast resume event*/
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
			/*TODO: broadcast pause event*/
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

	scene::~scene(void)
	{
		for(auto&& it : attached_windows_)
		{
			it->detach_scene();
		}
	}

}
}
