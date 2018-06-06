#ifndef TEXTURE_LOADER_HPP_YZCEATXW
#define TEXTURE_LOADER_HPP_YZCEATXW

#include <boost/filesystem.hpp>
#include <map>
#include <mutex>
#include <condition_variable>

namespace rg
{
namespace engine
{
	class texture_loader
	{
		public:
			texture_loader(void) = default;
			texture_loader(const texture_loader& t) = delete;


			std::pair<bool, unsigned> load(const std::string& path);
			std::pair<bool, unsigned> try_to_load(const std::string& path);
			

			texture_loader& operator=(const texture_loader& other) = delete; 
			~texture_loader(void);
		private:
			std::mutex m;
			std::mutex loading_lock_;
			std::condition_variable cv;
			std::map<boost::filesystem::path, std::pair<bool, unsigned>> textures_;
	};
}
}


#endif /* end of include guard: TEXTURE_LOADER_HPP_YZCEATXW */
