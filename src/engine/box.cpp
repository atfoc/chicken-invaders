#include "engine/box.hpp"

namespace rg
{
namespace engine
{
	box::box(float w, float h, float d)
		:	front_lower_left_(-w/2, -h/2, d/2, 1),
			front_lower_right_(w/2, -h/2, d/2, 1),
			front_upper_left_(-w/2, h/2, d/2, 1),
			front_upper_right_(w/2, h/2, d/2, 1),
			back_lower_left_(-w/2, -h/2, -d/2, 1),
			back_lower_right_(w/2, -h/2, -d/2, 1),
			back_upper_left_(-w/2, h/2, -d/2, 1),
			back_upper_right_(w/2, h/2, -d/2, 1)
	{}

}
}
