#include <ctime>
#include "engine/log.hpp"
#include "engine/id.hpp"

namespace rg
{
namespace engine
{

	log::log(bool log_to_file, const std::string& file_name)
		:	console_out_{&std::cout},
			file_out_{nullptr},
			log_to_file_{log_to_file},
			p_{priority::info}
	{
		if(log_to_file)
		{
			time_t time;
			std::time(&time);
			struct tm* local_time;
			local_time	= std::localtime(&time);
			
			file_out_ = new std::ofstream((boost::format("%d_%d_%d_%d_%d_%s") 
											% (local_time->tm_mday)
											% (local_time->tm_mon)
											% (local_time->tm_year+ 1900)
											% (local_time->tm_hour) 
											% (local_time->tm_min)
											% file_name).str());
		}
	}


	
	log& operator<<(log& out, const log::priority& p)
	{
		out.p_ = p;		
		return out;
	}

	log& operator<<(log& out, std::ios_base& (*f)(std::ios_base& ))
	{

		f(*out.console_out_);
		f(*out.file_out_);
		return out;
	}

	log& operator<<(log& out, std::ostream& (*f)(std::ostream& ))
	{
		f(*out.console_out_);
		f(*out.file_out_);
		return out;
	}

	log::~log(void)
	{
		if(file_out_)
		{
			file_out_->close();
			delete file_out_;
			file_out_ = nullptr;
		}
	}
}
}
