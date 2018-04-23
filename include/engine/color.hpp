#ifndef COLOR_HPP_WO7XHKRC
#define COLOR_HPP_WO7XHKRC

#include <string>

namespace rg
{
namespace engine
{
	class color
	{
		public:
			color(const std::string& hex_color);
			color(float r = 0.0f, float g = 0.0f, float b = 0.0f);
			color(const color& c);

			void html_color(const std::string& hex_color);
			void red(float r);
			void green(float g);
			void blue(float b);


			std::string html_color(void);	
			inline float red(void);
			inline float green(void);
			inline float blue(void);

		private:
			float r_, g_, b_;

			void convert_hex(const std::string& hex_color);
	};

	inline float color::red(void)
	{
		return r_;
	}

	inline float color::green(void)
	{
		return g_;
	}

	inline float color::blue(void)
	{
		return b_;
	}

}
}

#endif /* end of include guard: COLOR_HPP_WO7XHKRC */
