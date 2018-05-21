#include "engine/model_loader.hpp"


namespace rg
{
namespace engine
{

	model_loader::model_loader(texture_loader* tl)
		:	tl_{tl}
	{
	}

	std::pair<bool, model*> model_loader::load(const std::string& path)
	{
		boost::filesystem::path p(path);
		if(!boost::filesystem::exists(p))
		{
			return std::make_pair(false, nullptr);
		}

		std::unique_lock<std::mutex> lock(m, std::defer_lock);
		p = boost::filesystem::absolute(p);

		lock.lock();
		auto it = models_.find(p);
		/*Dose not exist need to load*/
		if(models_.end() ==  it)
		{
			models_[p] = std::make_pair(false, nullptr);
			lock.unlock();

			model* m= new model(p.string(), tl_);
			lock.lock();

			models_[p].first = true;
			models_[p].second = m;

			cv.notify_all();
			/*Uniqe lock unlocked here*/
			return std::make_pair(true, m);
		}
		/*Fount texture but it is not loaded yet*/
		else if(!it->second.first)
		{
			/*While not loaded wait*/
			cv.wait(lock, [&](){return models_.find(p)->second.first;});

			auto it1 = models_.find(p);
			/*uniqe lock unlocked here*/
			return it1->second;
		}
		else
		{
			/*Uniqe lock unlocked here*/
			return it->second;
		}
	}

	std::pair<bool, model*> model_loader::try_to_load(const std::string& path)
	{
		boost::filesystem::path p(path);
		if(!boost::filesystem::exists(p))
		{
			return std::make_pair(false, nullptr);
		}
		std::unique_lock<std::mutex> lock(m, std::defer_lock);

		p = boost::filesystem::absolute(p);

		lock.lock();
		auto it = models_.find(p);
		/*Dose not exist need to load*/
		if(models_.end() ==  it)
		{
			models_[p] = std::make_pair(false, nullptr);
			lock.unlock();

			model* m = new model(path, tl_);
			lock.lock();

			models_[p].first = true;
			models_[p].second = m;

			cv.notify_all();
			/*Uniqe lock unlocked here*/
			return std::make_pair(true, m);
		}
		else if(!it->second.first)
		{
			/*Uniqe lock unlocked here*/
			return std::make_pair(false, nullptr);
		}
		else
		{
			/*Uniqe lock unlocked here*/
			return it->second;
		}

	}


	model_loader::~model_loader(void)
	{
		std::for_each(models_.begin(), models_.end(), [](auto& it){delete it.second.second;});
	}

}
}
