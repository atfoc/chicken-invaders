#ifndef ORTHOGONAL_CAMERA_HPP_CAZIVR2N
#define ORTHOGONAL_CAMERA_HPP_CAZIVR2N

namespace rg
{
namespace engine
{
	class orthogonal_camera
	{
		public:
			orthogonal_camera(	float left, float right, float up,
								float down, float near, float far);
			orthogonal_camera(const orthogonal_camera& cam);

			void move(float x, float y);

			inline void near(float near);
			inline float near(void);

			inline void far(float far);
			inline float far(void);

			void zoom(float z);

			void apply(void);

		private:
			float left_, right_, up_, down_, near_, far_;

	};


	inline void orthogonal_camera::near(float near)
	{
		near_ = near;
	}

	inline float orthogonal_camera::near(void)
	{
		return near_;
	}

	inline void orthogonal_camera::far(float far)
	{
		far_ = far;
	}

	inline float orthogonal_camera::far(void)
	{
		return far_;
	}

}
}

#endif /* end of include guard: ORTHOGONAL_CAMERA_HPP_CAZIVR2N */

