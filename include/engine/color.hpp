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
			
			/**
			 * @brief construct a color from html color string ex. #aaff00
			 *
			 * @param hex_color html color string 
			 */
			color(const std::string& hex_color);

			/**
			 * @brief construct a color for r,g,b components
			 *
			 * @param r	red component
			 * @param g green component
			 * @param b blue component
			 */
			color(float r = 0.0f, float g = 0.0f, float b = 0.0f);
			color(const color& c);

			/**
			 * @brief sets color from html color string representation of color
			 *
			 * @param hex_color	color to set value to
			 */
			void html_color(const std::string& hex_color);

			/**
			 * @brief set red component
			 *
			 * @param r	red value
			 */
			void red(float r);

			/**
			 * @brief set green component
			 *
			 * @param g	green value
			 */
			void green(float g);

			/**
			 * @brief set blue component
			 *
			 * @param b	blue value
			 */
			void blue(float b);


			/**
			 * @brief get html color representation
			 *
			 * @return html color string
			 */
			std::string html_color(void);	

			/**
			 * @brief Get red component
			 *
			 * @return	red value
			 */
			inline float red(void);

			/**
			 * @brief Get green component
			 *
			 * @return	green value
			 */	
			inline float green(void);
			/**
			 * @brief Get blue component
			 *
			 * @return	blue value
			 */
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
