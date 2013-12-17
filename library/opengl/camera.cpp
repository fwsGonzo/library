#include "camera.hpp"

#include "../config.hpp"
#include "../log.hpp"
#include "window.hpp"

namespace library
{
	Camera::Camera(float FOV, float aspect, float znear, float zfar)
	{
		if (znear > zfar) throw std::string("Camera::Camera(): Znear must be less than Zfar");
		if (znear <= 0)   throw std::string("Camera::Camera(): Znear must be greater than zero");
		
		this->FOV = FOV;
		this->znear = znear;
		this->zfar  = zfar;
		
		// projection matrix
		matproj = perspectiveMatrix(FOV, aspect, znear, zfar);
		
		// initialize matrices
		setRotation(0, 0, 0);
		setTranslation(0, 0, 0);
	}
	
	void Camera::calculateFrustum()
	{
		frustum.calculate(matviewproj);
	}
	const Frustum& Camera::getFrustum() const
	{
		return this->frustum;
	}
	
	void Camera::setRotation(float rx, float ry, float rz)
	{
		matrot = rotationMatrix(rx, ry, rz);
	}
	
	void Camera::setTranslation(float tx, float ty, float tz)
	{
		// view matrix = rotation & translation
		matview = matrot;
		matview.translate(tx, ty, tz);
		
		// modelview projection matrix
		matviewproj = matproj * matview;
	}
	
	void Camera::setRotationMatrix(const mat4& rot)
	{
		matrot = rot;
	}
	void Camera::setViewMatrix(const mat4& view)
	{
		matview = view;
		matviewproj = matproj * matview;
	}
	
	const mat4& Camera::getProjection() const
	{
		return matproj;
	}
	const mat4& Camera::getViewMatrix() const
	{
		return matview;
	}
	const mat4& Camera::getRotationMatrix() const
	{
		return matrot;
	}
	const mat4& Camera::getMVP() const
	{
		return matviewproj;
	}
}
