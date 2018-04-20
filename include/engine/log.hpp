#ifndef LOG_HPP_SSG4RZ1X
#define LOG_HPP_SSG4RZ1X


#include <iostream>
#include <sstream>
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

			enum delimiter
			{
				end_log=0
			};

			log(bool log_to_file, const std::string& file_name= std::string());
			
			template<typename T>
			friend log& operator<<(log& out, const T& t);
			friend log& operator<<(log& out, const priority& p);
			friend log& operator<<(log& out, const delimiter& p);
			friend log& operator<<(log& out, std::ios_base& (*f)(std::ios_base& ));
			friend log& operator<<(log& out, std::ostream& (*f)(std::ostream& ));

			~log(void);
		private:
			std::ostream* console_out_;
			std::ofstream* file_out_;
			bool log_to_file_;
			priority p_;
			std::recursive_mutex lock_;
			boost::format frmt_console_;
			boost::format time_format_;
			boost::format frmt_file_;
			std::stringstream msg_;
			bool in_progress_;
	};


	template<typename T>
	log& operator<<(log& out, const T& t)
	{
		out.msg_ << t;		
		return out;
	}
}
}

#endif /* end of include guard: LOG_HPP_SSG4RZ1X */
