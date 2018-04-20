#include <iostream>
#include "engine/color.hpp"


int main(void)
{

	rg::engine::color c("#aabb01");

	std::cout << c.red() << std::endl << c.green() << std::endl <<  c.blue() << std::endl;
	std::cout << c.html_color() << std::endl;
	c.red(1);
	std::cout << c.html_color() << std::endl;

	return 0;
}
