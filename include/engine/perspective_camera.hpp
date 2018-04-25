#ifndef PERSPECTIVE_CAMERA_HPP_FL4JBIBP
#define PERSPECTIVE_CAMERA_HPP_FL4JBIBP

#include <glm/vec3.hpp>
#include "engine/camera.hpp"

namespace rg
{
namespace engine
{
	class perspective_camera : public camera
	{
		public:
			perspective_camera(	const glm::vec3& eye, const glm::vec3& point,
								float fovy, float aspect, float near, float far);
			perspective_camera(const perspective_camera& cam) = default;

			inline void eye(const glm::vec3& p);
			inline const glm::vec3& eye(void);

			inline void point(const glm::vec3& p);
			inline const glm::vec3& point(void);

			inline void fovy(float f);
			inline float fovy(void);

			inline void aspect(float f);
			inline float aspect(void);

			inline void near(float f);
			inline float near(void);

			inline void far(float f);
			inline float far(void);

			void apply(int w, int h);

		private:
			glm::vec3 eye_;
			glm::vec3 point_;
			float fovy_, aspect_, near_, far_;
	};


	inline void perspective_camera::eye(const glm::vec3& p)
	{
		eye_ = p;
	}

	inline const glm::vec3& perspective_camera::eye(void)
	{
		return eye_;
	}

	inline void perspective_camera::point(const glm::vec3& p)
	{
		point_ = p;
	}

	inline const glm::vec3& perspective_camera::point(void)
	{
		return point_;
	}

	inline void perspective_camera::fovy(float f)
	{
		fovy_ = f;
	}

	inline float perspective_camera::fovy(void)
	{
		return fovy_;
	}


	inline void perspective_camera::aspect(float f)
	{
		aspect_ = f;
	}

	inline float perspective_camera::aspect(void)
	{
		return aspect_;
	}

	inline void perspective_camera::near(float f)
	{
		near_ = f;
	}

	inline float perspective_camera::near(void)
	{
		return near_;
	}

	inline void perspective_camera::far(float f)
	{
		far_ = f;
	}

	inline float perspective_camera::far(void)
	{
		return far_;
	}
}
}

#endif /* end of include guard: PERSPECTIVE_CAMERA_HPP_FL4JBIBP */
