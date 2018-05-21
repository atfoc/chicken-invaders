#ifndef MODEL_HPP_SONJWFE6
#define MODEL_HPP_SONJWFE6

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "engine/texture_loader.hpp"

namespace rg
{
namespace engine
{
	class model
	{
		
		public:
			model(const std::string& path, texture_loader* tl);
			model(const model& m) = delete;

			void render(void);	
			bool has_textures(void);
			~model(void) = default;
		private:
			Assimp::Importer importer_;
			const aiScene* scene_;
			texture_loader* tl_;
			std::string path_to_model_;
	};
}
}

#endif /* end of include guard: MODEL_HPP_SONJWFE6 */
