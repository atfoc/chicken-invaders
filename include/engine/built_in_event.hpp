#ifndef BUILT_IN_EVENT_HPP_J7RKDI5Q
#define BUILT_IN_EVENT_HPP_J7RKDI5Q

#include <utility>
#include "event.hpp"


namespace rg
{
namespace engine
{
	class built_in_event : public event
	{

		public:
			built_in_event(const SDL_Event& e);
			built_in_event(const built_in_event& e) = default;
			built_in_event(built_in_event&& e) = default;


			inline built_in_event& operator=(const built_in_event& e);
			inline built_in_event& operator=(built_in_event&& e);

		
			virtual Uint32 type(void) const;
			virtual SDL_Event sdl_event(void) const;

			virtual ~built_in_event(void) = default;


		private:
			SDL_Event e_;
	};

	inline built_in_event& built_in_event::operator=(const built_in_event& e)
	{
		e_ = e.e_;
		return *this;
	}

	inline built_in_event& built_in_event::operator=(built_in_event&& e)
	{
		e_ = std::move(e.e_);

		return *this;
	}

}
}

#endif /* end of include guard: BUILT_IN_EVENT_HPP_J7RKDI5Q */

