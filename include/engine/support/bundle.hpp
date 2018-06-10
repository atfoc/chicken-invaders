#ifndef BUNDLE_HPP_ITPANLZS
#define BUNDLE_HPP_ITPANLZS

#include <tuple>
#include "engine/target_event.hpp"
#include "engine/id.hpp"

namespace rg
{
namespace engine
{
namespace support
{
	/**
	 * @brief	This class is intended to be used as faster way to
	 *			make custom events. Because events usually just send some
	 *			information you can use bundle event to bundle that data 
	 *			and send it. But be careful when handling this event
	 *			if you have two bundle events with the same data their 
	 *			code will be the same so suggestion is to add another argument
	 *			of enumeration or int to easily distinguished between this events
	 */
	template<typename... Args>
	class bundle_event: public target_event
	{
		public:
			/**
			 * @brief constructor for bundle event 
			 *
			 * @param scene_id	scene to send an event
			 * @param objec_id	object to send an event rg::engine::uuids::null_id if you want to
			 *					send to all objects in a scene
			 * @param args	arguments to wrap in an event
			 */
			bundle_event(const uuid& scene_id, const uuid& objec_id, Args... args);

			/**
			 * @brief copy constructor
			 *
			 * @param b object to copy
			 */
			bundle_event(const bundle_event<Args...>& b) = default;

			/**
			 * @brief move constructor
			 *
			 * @param b object to be moved 
			 */bundle_event(bundle_event<Args...>&& b) = default;
			

			/**
			 * @brief return an sdl wrapper of this event
			 *
			 * @return sdl wrapper of this event
			 */
			SDL_Event sdl_event(void) const;


			/**
			 * @brief code of this event
			 *
			 * @return code for this event.
			 *
			 * XXX	Warning two bundle events with same types have the same code
			 * 
			 * 
			 */
			Uint32 code(void) const;

			~bundle_event(void) = default;

		/**
		 * @brief	returns Nth element of bundle_event
		 *
		 * @param b	bundle event to extract element from
		 *
		 * @return nth element
		 */
		template<size_t I, typename... Args1>
		friend constexpr std::tuple_element_t<I, std::tuple<Args1...>>& std::get(bundle_event<Args1...>& b) noexcept;

		template<size_t I, typename... Args1>
		friend constexpr std::tuple_element_t<I, std::tuple<Args1...>>&& std::get(bundle_event<Args1...>&& b) noexcept;

		template<size_t I, typename... Args1>
		friend constexpr const std::tuple_element_t<I, std::tuple<Args1...>>& std::get(const bundle_event<Args1...>& b) noexcept;
	

		private:
			std::tuple<Args...>	args_;
	};
	
	template<typename... Args>
	bundle_event<Args...>::bundle_event(const uuid& scene_id, const uuid& objec_id, Args... args)
		:	target_event(scene_id, objec_id),
			args_(std::make_tuple(std::forward<Args>(args)...))
	{}

	template<typename... Args>
	SDL_Event bundle_event<Args...>::sdl_event(void) const
	{
		SDL_Event e;
		e.type = SDL_USEREVENT;
		e.user.data1 = new bundle_event<Args...>(*this);

		return 	e;
	}

	template<typename... Args>
	Uint32 bundle_event<Args...>::code(void) const
	{
		return user_event_code<bundle_event<Args...>>::value;
	}

	template<typename... Args>
	bundle_event<Args...> make_bundle_event(const uuid& scene_id, const uuid& obj_id, Args... args)
	{
		return bundle_event<std::decay_t<Args>...>(scene_id, obj_id, std::forward<Args>(args)...);
	}

}
}
}


namespace std
{

	template<size_t I, typename... Args>
	constexpr std::tuple_element_t<I, std::tuple<Args...>>& get(rg::engine::support::bundle_event<Args...>& b) noexcept
	{
		return std::get<I>(b.args_);
	}

	template<size_t I, typename... Args>
	constexpr std::tuple_element_t<I, std::tuple<Args...>>&& get(rg::engine::support::bundle_event<Args...>&& b) noexcept
	{
		return std::get<I>(b.args_);
	}

	template<size_t I, typename... Args>
	constexpr const std::tuple_element_t<I, std::tuple<Args...>>& get(const rg::engine::support::bundle_event<Args...>& b) noexcept
	{
		return std::get<I>(b.args_);
	}
}
#endif /* end of include guard: BUNDLE_HPP_ITPANLZS */
