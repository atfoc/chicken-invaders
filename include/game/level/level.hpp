#ifndef LEVEL_HPP_JEMUJOLD
#define LEVEL_HPP_JEMUJOLD

#include "engine/id.hpp"
#include "engine/texture_loader.hpp"
#include "engine/model_loader.hpp"
#include "game/level/level_representation.hpp"

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

		virtual rg::engine::scene* scene(rg::engine::texture_loader& tl, rg::engine::model_loader& ml) = 0;
		virtual level_representation* representation(rg::engine::texture_loader& tl, rg::engine::model_loader& ml) = 0;
		virtual rg::engine::uuid camera(void) = 0;

		virtual ~level(void) = default;
};



#endif /* end of include guard: LEVEL_HPP_JEMUJOLD */
