#ifndef USER_EVENT_HPP_OR4XR3IL
#define USER_EVENT_HPP_OR4XR3IL

#include "event.hpp"
#include "id.hpp"

namespace rg
{
namespace engine
{
	class user_event : public event
	{

		public:
			user_event(const uuid& scene_id);
			user_event(const user_event& e) = default;
			user_event(user_event&& e) = default;


			inline user_event& operator=(const user_event& e);
			inline user_event& operator=(user_event&& e);


			Uint32 type(void) const;	
			inline const uuid& scene_id(void);	

			virtual SDL_Event sdl_event(void) const = 0;
			virtual Uint32 code(void) const = 0;

			virtual ~user_event(void) = default;


			inline static Uint32 regiser_event(void);

			

		private:
			uuid scene_id_;

	};


	inline user_event& user_event::operator=(const user_event& e)
	{
		scene_id_ = e.scene_id_;

		return *this;
	}

	inline user_event& user_event::operator=(user_event&& e)
	{
		scene_id_ = std::move(e.scene_id_);

		/*test if e.scene_id_ is set to null*/
		return *this;
	}

	inline Uint32 user_event::regiser_event(void)
	{
		return SDL_RegisterEvents(1);
	}

	inline const uuid& user_event::scene_id(void)
	{
		return scene_id_;
	}


	template<typename T>
	struct user_event_code
	{
		static Uint32 value;
	};

	template<typename T>
	Uint32 user_event_code<T>::value = user_event::regiser_event();

}
}

#endif /* end of include guard: USER_EVENT_HPP_OR4XR3IL */
