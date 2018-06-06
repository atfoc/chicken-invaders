#include "engine/box.hpp"

namespace rg
{
namespace engine
{
	box::box(float w, float h, const glm::vec3& pos)
		:	pos_(pos),
			w_{w},
			h_{h}
	{}

}
}
