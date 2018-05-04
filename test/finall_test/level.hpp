#ifndef LEVEL_HPP_JEMUJOLD
#define LEVEL_HPP_JEMUJOLD

#include "engine/id.hpp"
#include "level_representation.hpp"

namespace rg
{
namespace engine
{
	class scene;
	class game_object;
}
}

class level
{
	public:
		level(void) = default;
		level(const level& l) = default;

		virtual rg::engine::scene* scene(void) = 0;
		virtual level_representation* representation(void) = 0;
		virtual rg::engine::uuid camera(void) = 0;

		virtual ~level(void) = default;
};



#endif /* end of include guard: LEVEL_HPP_JEMUJOLD */
