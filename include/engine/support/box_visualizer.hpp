#ifndef BOX_VISUALIZER_HPP_DJVUURSM
#define BOX_VISUALIZER_HPP_DJVUURSM


#include <vector>
#include "engine/game_object.hpp"
#include "engine/model_loader.hpp"
#include "engine/model.hpp"

namespace rg
{
namespace engine
{
namespace support
{
	class box_visualizer : public rg::engine::game_object
	{
		public:
	
			box_visualizer(void);
			box_visualizer(const box_visualizer& obj) = default;
	
			
			void render(void);
			bool handle_events(const rg::engine::event& e);
			rg::engine::game_object* copy(void);
			rg::engine::box box_mash(void);
	
	
			void add_object(game_object* obj);
	
	
	
			~box_visualizer(void);
		private:
			std::vector<game_object*> objs_;
	};
}
}
}
;


#endif /* end of include guard: BOX_VISUALIZER_HPP_DJVUURSM */
