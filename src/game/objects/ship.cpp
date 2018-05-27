#include "engine/application.hpp"
#include "engine/log.hpp"
#include "game/objects/ship.hpp"
#include "engine/event.hpp"
#include "engine/box.hpp"

ship::ship(rg::engine::model_loader* ml)
{

	auto res =ml->load("./materials/ship/model.obj");
	if(res.first)
	{
		(*rg::engine::application::logger()) << rg::engine::log::priority::info << "Ship model loaded sucessfuly" << rg::engine::log::end_log;	
		model_ = res.second;
	}
	else
	{
		(*rg::engine::application::logger()) << rg::engine::log::priority::warning << "Ship model failed to load" << rg::engine::log::end_log;	
		(*rg::engine::application::logger()) << rg::engine::log::priority::danger<< "No default model expect a creash" << rg::engine::log::end_log;	
		/*Set Default model*/
	}
}

void ship::render(void)
{
	glEnable(GL_TEXTURE_2D);
	model_->render();
	glDisable(GL_TEXTURE_2D);
}

rg::engine::game_object* ship::copy(void)
{
	return new ship(*this);
}

rg::engine::box ship::box_mash(void)
{
	return rg::engine::box();
}

ship::~ship(void)
{

}
