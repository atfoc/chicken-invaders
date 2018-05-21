#ifndef MODEL_LOADER_HPP_EWEM9DOB
#define MODEL_LOADER_HPP_EWEM9DOB

#include <boost/filesystem.hpp>
#include <map>
#include <mutex>
#include <condition_variable>
#include "engine/model.hpp"

namespace rg
{
namespace engine
{
	class model_loader
	{
		public:
			model_loader(texture_loader* tl);
			model_loader(const model_loader& t) = delete;


			std::pair<bool, model*> load(const std::string& path);
			std::pair<bool, model*> try_to_load(const std::string& path);
			

			model_loader& operator=(const model_loader& other) = delete; 
			~model_loader(void);
		private:
			texture_loader* tl_;
			std::mutex m;
			std::condition_variable cv;
			std::map<boost::filesystem::path, std::pair<bool, model*>> models_;
	};
}
}



#endif /* end of include guard: MODEL_LOADER_HPP_EWEM9DOB */
