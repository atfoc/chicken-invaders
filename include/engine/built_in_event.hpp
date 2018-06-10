#ifndef BUILT_IN_EVENT_HPP_J7RKDI5Q
#define BUILT_IN_EVENT_HPP_J7RKDI5Q

#include <utility>
#include "event.hpp"


namespace rg
{
namespace engine
{
	/**
	 * @brief	this class represents all SDL2 events
	 */
	class built_in_event : public event
	{

		public:
			/**
			 * @brief	construct event from the SDL2 event that you represent
			 *
			 * @param e	event you want to wrap
			 */
			built_in_event(const SDL_Event& e);

			/**
			 * @brief	copy constructor
			 *
			 * @param e	event to copy
			 */
			built_in_event(const built_in_event& e) = default;

			/**
			 * @brief	returns a type of event this is SDL2 types	
			 *
			 * @return	type of SLD2 event ex. SLD_USER_EVENT
			 */
			virtual Uint32 type(void) const;

			/**
			 * @brief	returns event object wrapped in sdl2 event
			 *			for base_event this is underling event for user event
			 *			it is user event with data1 field set to pointer to event
			 *			object
			 *
			 * @return	sdl event wrapper
			 */
			virtual SDL_Event sdl_event(void) const;


			/**
			 * @brief	deconstructor
			 */
			virtual ~built_in_event(void) = default;


		private:
			SDL_Event e_;
	};
}
}

#endif /* end of include guard: BUILT_IN_EVENT_HPP_J7RKDI5Q */

