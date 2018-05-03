#include <iostream>
#include "bundle.hpp"



int main(int argc, char *argv[])
{
	
	namespace id = rg::engine::uuids;
	auto b1 = rg::engine::support::make_bundle_event(id::null_id, id::null_id, 1, "a");
	auto b2 = rg::engine::support::make_bundle_event(id::null_id, id::null_id, 1.2f, 3, "cao");
	auto b3 = rg::engine::support::make_bundle_event(id::null_id, id::null_id, 7, "jel sam isti kao malo pre");

	std::cout << std::get<0>(b1) << " " << std::get<1>(b1) << " " << b1.code() << std::endl;
	std::cout << std::get<0>(b2) << " " << std::get<1>(b2) << " " << std::get<2>(b2) << " "<< b2.code() << std::endl;
	std::cout << std::get<0>(b3) << " " << std::get<1>(b3) << " " << b3.code() << std::endl;


	std::cout << rg::engine::user_event_code<int>::value << std::endl;
	std::cout << rg::engine::user_event_code<float>::value << std::endl;
	return 0;
}
