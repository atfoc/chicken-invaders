#ifndef LOG_HPP_SSG4RZ1X
#define LOG_HPP_SSG4RZ1X


#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <mutex>
#include <boost/format.hpp>

namespace rg
{
namespace engine
{
	/*TODO: MOVE SEMANTICS*/
	class log
	{
		public:
			enum class priority
			{
				danger, info, debug, warning
			};

			log(bool log_to_file, const std::string& file_name= std::string());

			template<typename T>
			friend log& operator<<(log& out, const T& t);

			friend log& operator<<(log& out, const priority& p);
			friend log& operator<<(log& out, std::ios_base& (*f)(std::ios_base& ));
			friend log& operator<<(log& out, std::ostream& (*f)(std::ostream& ));

			~log(void);
			private:
				std::ostream* console_out_;
				std::ofstream* file_out_;
				bool log_to_file_;
				priority p_;
				std::mutex lock_;
	};

	template<typename T>
	log& operator<<(log& out, const T& t)
	{
		boost::format frmt_console("[%s] (\x1b[%dm%s\x1b[0m) %s\n");
		
		time_t time;
		std::time(&time);
		struct tm* local_time{std::localtime(&time)};
		boost::format time_format("%d.%d.%d. %d:%d");
		auto time_string = (time_format 
						% (local_time->tm_mday)
						% (local_time->tm_mon)
						% ((local_time->tm_year + 1900) % 100)
						% (local_time->tm_hour)
						% (local_time->tm_min))
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

		
		out.lock_.lock();
		/*TODO: is t automaticly converted to string*/
		(*out.console_out_) << (frmt_console % time_string % color % priority  % t).str();
		if(out.file_out_)
		{
			(*out.file_out_) << (boost::format("[%s] (%s) %s\n") % time_string % priority % t).str();
		}
		out.lock_.unlock();

		return out;
	}
	

}
}

#endif /* end of include guard: LOG_HPP_SSG4RZ1X */
