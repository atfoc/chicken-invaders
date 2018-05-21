#ifndef CUBE_HPP_QCEKLRIN
#define CUBE_HPP_QCEKLRIN

#include <map>
#include "engine/game_object.hpp"
#include "engine/color.hpp"
#include "engine/model.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

class object  : public rg::engine::game_object
{
	public:
		object(rg::engine::model* m);
		object(const object& c) = default;
		
		rg::engine::game_object* copy(void);
		void render(void);
		bool handle_events(const rg::engine::event& e);

		rg::engine::box box_mash(void);

		void on_frame(void);
		~object(void) = default;

	private:
		rg::engine::model* m_;
		
};

#endif /* end of include guard: CUBE_HPP_QCEKLRIN */
