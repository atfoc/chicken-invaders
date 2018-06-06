#include <IL/il.h>
#include <GL/gl.h>
#include "engine/texture_loader.hpp"
#include "engine/upload_texture_event.hpp"
#include "engine/application.hpp"
#include "engine/id.hpp"

namespace rg
{
namespace engine
{

	static unsigned load_texture(const std::string &path, std::mutex& load_lock)
	{
		std::lock_guard<std::mutex> guard(load_lock);
		std::mutex tmp;		
		std::unique_lock<std::mutex> dummy_lock(tmp);
		std::condition_variable cv;

		ILuint pic;
		unsigned tex_name;
	
		ilGenImages(1, &pic);
		ilBindImage(pic);
		ilLoadImage(path.c_str());

		ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		
		if(application::main_thread_id() == std::this_thread::get_id())
		{
			tex_name = application::upload_texture();
		}
		else
		{
			application::post_event(upload_texture_event(uuids::null_id, &cv, &tex_name));
			cv.wait(dummy_lock);
		}
			
		ilDeleteImages(1, &pic);
	
		return tex_name;
	}

	std::pair<bool, unsigned> texture_loader::load(const std::string& path)
	{
		boost::filesystem::path p(path);
		if(!boost::filesystem::exists(p))
		{
			return std::make_pair(false, -1u);
		}

		std::unique_lock<std::mutex> lock(m, std::defer_lock);
		p = boost::filesystem::absolute(p);

		lock.lock();
		auto it = textures_.find(p);
		/*Dose not exist need to load*/
		if(textures_.end() ==  it)
		{
			textures_[p] = std::make_pair(false, 0);
			lock.unlock();

			unsigned tex = load_texture(p.string(), loading_lock_);
			lock.lock();

			textures_[p].first = true;
			textures_[p].second = tex;

			cv.notify_all();
			/*Uniqe lock unlocked here*/
			return std::make_pair(true, tex);
		}
		/*Fount texture but it is not loaded yet*/
		else if(!it->second.first)
		{
			/*While not loaded wait*/
			cv.wait(lock, [&](){return textures_.find(p)->second.first;});

			auto it1 = textures_.find(p);
			/*uniqe lock unlocked here*/
			return it1->second;
		}
		else
		{
			/*Uniqe lock unlocked here*/
			return it->second;
		}
	}

	std::pair<bool, unsigned> texture_loader::try_to_load(const std::string& path)
	{
		boost::filesystem::path p(path);
		if(!boost::filesystem::exists(p))
		{
			return std::make_pair(false, -1u);
		}
		std::unique_lock<std::mutex> lock(m, std::defer_lock);

		p = boost::filesystem::absolute(p);

		lock.lock();
		auto it = textures_.find(p);
		/*Dose not exist need to load*/
		if(textures_.end() ==  it)
		{
			textures_[p] = std::make_pair(false, 0);
			lock.unlock();

			unsigned tex = load_texture(p.string(), loading_lock_);
			lock.lock();

			textures_[p].first = true;
			textures_[p].second = tex;

			cv.notify_all();
			/*Uniqe lock unlocked here*/
			return std::make_pair(true, tex);
		}
		else if(!it->second.first)
		{
			/*Uniqe lock unlocked here*/
			return std::make_pair(false, -1u);
		}
		else
		{
			/*Uniqe lock unlocked here*/
			return it->second;
		}

	}


	texture_loader::~texture_loader(void)
	{
		std::for_each(textures_.begin(), textures_.end(), [](auto& it){glDeleteTextures(1,&it.second.second);});
	}

}
}
