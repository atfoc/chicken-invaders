#include "engine/upload_texture_event.hpp"

namespace rg
{
namespace engine
{

	upload_texture_event::upload_texture_event(const uuid& scene_id, std::condition_variable* cv, unsigned* pt)
		:	user_event(scene_id),
			cv_{cv},
			tex_name_{pt}
	{}


	void upload_texture_event::tex_name(unsigned tex_name)	
	{
		*tex_name_ = tex_name;	
	}

	void upload_texture_event::done(void)
	{
		cv_->notify_all();	
	}
	
	SDL_Event upload_texture_event::sdl_event(void) const
	{
		SDL_Event e;

		e.type = SDL_USEREVENT;
		e.user.data1 = new upload_texture_event(*this);
		return e;
	}
	
	Uint32 upload_texture_event::code(void) const
	{
		return user_event_code<upload_texture_event>::value;	
	}
}
}
