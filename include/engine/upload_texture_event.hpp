#ifndef UPLOAD_TEXTURE_EVENT_HPP_W6VKFGG0
#define UPLOAD_TEXTURE_EVENT_HPP_W6VKFGG0

#include <condition_variable>
#include "engine/user_event.hpp"
#include "engine/id.hpp"

namespace rg
{
namespace engine
{
	class upload_texture_event : public user_event
	{

		public:
			upload_texture_event(const uuid& scene_id, std::condition_variable* cv, unsigned* pt);
			upload_texture_event(const upload_texture_event& e) = default;


			void tex_name(unsigned tex_name);	
			void done(void);

			SDL_Event sdl_event(void) const;
			Uint32 code(void) const;

			~upload_texture_event(void) = default;

		private:
			std::condition_variable* cv_;
			unsigned* tex_name_;	

			

	};


}
}


#endif /* end of include guard: UPLOAD_TEXTURE_EVENT_HPP_W6VKFGG0 */
