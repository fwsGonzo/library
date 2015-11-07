#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace library
{
	extern glm::mat4 biasMatrix();
	extern glm::mat4 rotationMatrix(float ax, float ay, float az);
	extern glm::mat4 extractRotation(glm::mat4& matrix);
	
	extern glm::mat4 ortho2dMatrix(float width, float height, float znear, float zfar);
	extern glm::mat4 orthoMatrix(float width, float height, float znear, float zfar);
	extern glm::mat4 perspectiveMatrix(float fov, float aspect, float znear, float zfar);
}
