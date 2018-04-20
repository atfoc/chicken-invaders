#include <regex>
#include <iomanip>
#include "engine/color.hpp"

namespace rg
{
namespace engine
{
	color::color(const std::string& hex_color)
	{ 
		convert_hex(hex_color);
	}
	
	color::color(float r, float g, float b)
		:	r_{r}, g_{g}, b_{b}
	{
		if(r_ > 1.0f || r_ < 0.0f)
		{
			r_ = 0.0f;
		}

		if(g_ > 1.0f || g_ < 0.0f)
		{
			g_ = 0.0f;
		}

		if(b_ > 1.0f || b_ < 0.0f)
		{
			b_ = 0.0f;
		}
	}
	
	color::color(const color& c)
		:	r_{c.r_}, g_{c.g_}, b_{c.b_}
	{}
	
	void color::html_color(const std::string& hex_color)
	{
		convert_hex(hex_color);
	}
	
	void color::red(float r)
	{
		if(r > 1.0f || r < 0.0f)
		{
			return ;
		}

		r_ = r;
	}
	
	void color::green(float g)
	{
		if(g > 1.0f || g < 0.0f)
		{
			return ;
		}

		g_ = g;
	}
	
	void color::blue(float b)
	{
		if(b > 1.0f || b < 0.0f)
		{
			return ;
		}

		b_ = b;
	}
	
	
	std::string color::html_color(void)
	{
		std::stringstream ss;	
		int r = r_ * 255;
		int g = g_ * 255;
		int b = b_ * 255;

		ss << "#" << std::hex << std::setfill('0') << std::setw(2) << r;
		ss << std::setfill('0') << std::setw(2) << g;
		ss << std::setfill('0') << std::setw(2) << b;
		return ss.str();
	}

	void color::convert_hex(const std::string& hex_color)
	{
		std::regex reg("#([0-9a-fA-F]{2})([0-9a-fA-F]{2})([0-9a-fA-F]{2})");

		std::smatch mr;

		if(std::regex_match(hex_color, mr, reg))
		{
			r_	= std::strtol(mr[1].str().c_str(), nullptr, 16) / 255.0f;
			g_	= std::strtol(mr[2].str().c_str(), nullptr, 16) / 255.0f;
			b_	= std::strtol(mr[3].str().c_str(), nullptr, 16) / 255.0f;
		}
		else
		{
			throw std::runtime_error("String color was in invalid format");
		}
	}
}
}
