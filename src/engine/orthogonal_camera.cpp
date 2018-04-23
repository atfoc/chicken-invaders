#include <GL/gl.h>
#include "engine/orthogonal_camera.hpp"

namespace rg
{
namespace engine
{
	orthogonal_camera::orthogonal_camera(	float left, float right, float up,
											float down, float near, float far)
		:	left_{left}, right_{right}, up_{up},
			down_{down}, near_{near}, far_{far}
	{
	
	}

	orthogonal_camera::orthogonal_camera(const orthogonal_camera& cam)
		:	left_{cam.left_}, right_{cam.right_}, up_{cam.up_},
			down_{cam.down_}, near_{cam.near_}, far_{cam.far_}
	{

	}

	void orthogonal_camera::move(float x, float y)
	{
		left_ += x;
		right_ += x;
		up_ += y;
		down_ += y;
	}

	void orthogonal_camera::zoom(float z)
	{
		float left_tmp {left_ + z};
		float right_tmp{right_ - z};

		if(left_tmp < right_tmp)
		{
			left_ = left_tmp;
			right_ = right_tmp;
		}

		float up_tmp {up_- z};
		float down_tmp{down_+ z};

		if(down_tmp < up_tmp)
		{
			down_ = down_tmp;
			up_ = up_tmp;
		}
	}
	
	void orthogonal_camera::apply(void)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left_, right_, down_, up_, near_, far_);
		glMatrixMode(GL_MODELVIEW);
	}
}
}
