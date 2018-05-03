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
	template<typename... Args>
	class bundle_event: public target_event
	{
		public:
			bundle_event(const uuid& scene_id, const uuid& objec_id, Args... args);
			bundle_event(const bundle_event<Args...>& b) = default;
			bundle_event(bundle_event<Args...>&& b) = default;
			
			SDL_Event sdl_event(void) const;
			Uint32 code(void) const;

			~bundle_event(void) = default;
			
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
