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
			p_{priority::info},
			frmt_console_("[%s] (\x1b[%dm%s\x1b[0m) %s\n"),
			time_format_("%d.%d.%d. %d:%d:%d"),
			frmt_file_("[%s] (%s) %s\n"),
			in_progress_{false}
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
		out.lock_.lock();
		if(out.in_progress_)
		{
			throw std::runtime_error(	"rg::engine::log previous log message is not terminited"
										"with rg::engine::log::end_log");
		}
		out.in_progress_ = true;
		out.msg_.str("");
		out.p_ = p;		
		return out;
	}

	log& operator<<(log& out, std::ios_base& (*f)(std::ios_base& ))
	{

		f(out.msg_);
		f(out.msg_);
		return out;
	}

	log& operator<<(log& out, std::ostream& (*f)(std::ostream& ))
	{
		f(out.msg_);
		f(out.msg_);
		return out;
	}

	log& operator<<(log& out, const log::delimiter& p)
	{
		static_cast<void>(p);


		time_t time;
		std::time(&time);
		struct tm* local_time{std::localtime(&time)};
		auto time_string = (out.time_format_
						% (local_time->tm_mday)
						% (local_time->tm_mon)
						% ((local_time->tm_year + 1900) % 100)
						% (local_time->tm_hour)
						% (local_time->tm_min)
						% (local_time->tm_sec))
						.str();

		std::string priority;
		int color{0};

		switch(out.p_)
		{

			case log::priority::danger:
				priority = "Danger";
				color = 31;
				break;
			case log::priority::info:
				priority = "Info";
				color = 34;
				break;
			case log::priority::debug:
				priority = "Debug";
				color = 32;
				break;
			case log::priority::warning:
				priority = "Warning";
				color = 33;
				break;
		}

		
		/*TODO: is t automaticly converted to string*/
		(*out.console_out_) << (out.frmt_console_ % time_string % color % priority  % out.msg_.str()).str();
		if(out.file_out_)
		{
			(*out.file_out_) << (out.frmt_file_ % time_string % priority % out.msg_.str()).str();
		}

		out.in_progress_ = false;
		out.lock_.unlock();

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
