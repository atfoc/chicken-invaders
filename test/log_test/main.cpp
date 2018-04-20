#include <iostream>
#include "engine/log.hpp"



int main(void)
{
	rg::engine::log l(true, "test_log.log");

	l << rg::engine::log::priority::info << "Hi" << 0 << rg::engine::log::end_log;
	l << rg::engine::log::priority::warning << "Yea about that" << rg::engine::log::end_log;
	return 0;
}
