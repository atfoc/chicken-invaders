#include <boost/format.hpp>
#include <glm/vec4.hpp>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/event.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"
#include "engine/support/camera_controler.hpp"

namespace rg
{
namespace engine
{
namespace support
{
	camera_controler::camera_controler(perspective_camera* c, float h_speed, float v_speed, float speed)
		:	camera_{c},
			h_speed_{h_speed},
			v_speed_{v_speed},
			speed_{speed},
			fi_{0},
			thet_{0}
	{}


			
	bool camera_controler::handle_events(const event& e)
	{
		static constexpr float eps{0.001};

		SDL_Event e_;
		if(SDL_MOUSEMOTION == e.type())
		{
			e_ = e.sdl_event();
			
			if(e_.motion.xrel > 0)
			{
				/*move right*/
				fi_ -= h_speed_;
				if(fi_ - eps < -2*M_PI) 
				{
					fi_ = 0;
				}
			}
			else if(e_.motion.xrel < 0)
			{
				/*move left*/
				fi_ += h_speed_;
				if(fi_ + eps > 2*M_PI )
				{
					fi_ = 0;
				}
			}


			if(e_.motion.yrel < 0)
			{
				/*Move up*/
				float old = thet_;

				thet_ += v_speed_;
				if(thet_ + eps > 0)
				{
					thet_ = old;
				}
			}
			else if(e_.motion.yrel > 0)
			{
				/*Move down*/
				float old = thet_;
				thet_ -= v_speed_;
				if(thet_ - eps < -M_PI)
				{
					thet_ = old;
				}
			}

			float px = std::sin(thet_)*std::sin(fi_);
			float py = 	std::cos(thet_);
			float pz = std::sin(thet_)*std::cos(fi_);

			glm::vec3 point{px, py, pz};
			point = point + camera_->eye();
			camera_->point(point);
			
			return true;
		}
		else if(SDL_KEYDOWN == e.type())
		{
			e_ = e.sdl_event();
			float speed;
			if(e_.key.keysym.mod & KMOD_SHIFT)
			{
				speed = 2* speed_;
			}
			else
			{
				speed = speed_;
			}

			if(SDLK_w ==  e_.key.keysym.sym || SDLK_s == e_.key.keysym.sym)
			{
				int direction = 1;
				if(SDLK_s == e_.key.keysym.sym)
				{
					direction = -1;
				}

				glm::vec3 eye_ = camera_->point() - camera_->eye();
				eye_[1] = 0;

				eye_[0] = std::fabs(eye_[0])  < eps ? 0 : eye_[0] ;
				eye_[2] = std::fabs(eye_[2])  < eps ? 0 : eye_[2];

				eye_ *= std::pow(speed,2)/(std::pow(eye_[0], 2) + std::pow(eye_[2], 2));
				eye_ *= direction;
				camera_->eye(camera_->eye() + eye_);
				camera_->point(camera_->point() + eye_);
				return true;
			}
			else if(SDLK_a == e_.key.keysym.sym || SDLK_d == e_.key.keysym.sym)
			{
				int direction{-1};
				if(SDLK_d == e_.key.keysym.sym)
				{
					direction = 1;
				}

				glm::vec3 eye_ = camera_->point() - camera_->eye();
				eye_[1] = 0;
				std::swap(eye_[0], eye_[2]);
				eye_[0] *= -1;

				eye_[0] = std::fabs(eye_[0])  < eps ? 0 : eye_[0] ;
				eye_[2] = std::fabs(eye_[2])  < eps ? 0 : eye_[2];
				

				eye_ *= std::pow(speed,2)/(std::pow(eye_[0], 2) + std::pow(eye_[2], 2));
				eye_ *= direction;
				camera_->eye(camera_->eye() + eye_);
				camera_->point(camera_->point() + eye_);
				
				return true;
			}
			else if(SDLK_SPACE == e_.key.keysym.sym)
			{
				int direction{1};
				if(e_.key.keysym.mod & KMOD_SHIFT)
				{
					direction = -1;
				}

				camera_->eye(camera_->eye() + glm::vec3{0, direction*speed, 0});
				camera_->point(camera_->point() + glm::vec3{0, direction*speed, 0});

				return true;
			}


		}
				

		return false;
	}
	
	game_object* camera_controler::copy(void)
	{
		return new camera_controler(*this);	
	}
	
	box camera_controler::box_mash(void)
	{
		return box();	
	}

	void camera_controler::apply(void)
	{
		float px = std::sin(thet_)*std::sin(fi_);
		float py = 	std::cos(thet_);
		float pz = std::sin(thet_)*std::cos(fi_);

		glm::vec3 point{px, py, pz};
		point = point + camera_->eye();
		camera_->point(point);
	}
}
}
}
