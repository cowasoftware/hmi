#include "Glm.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>

GlmVec3 Glm::normalize(const GlmVec3& vec3)
{
	glm::vec3&& result = glm::normalize(glm::vec3(vec3.x(), vec3.y(), vec3.z()));
	return GlmVec3(result.x, result.y, result.z);
}

float Glm::dot(const GlmVec3& vec3a, const GlmVec3& vec3b)
{
	return glm::dot(glm::vec3(vec3a.x(), vec3a.y(), vec3a.z()), glm::vec3(vec3b.x(), vec3b.y(), vec3b.z()));
}

GlmVec3 Glm::cross(const GlmVec3& vec3a, const GlmVec3& vec3b)
{
	glm::vec3&& result = glm::cross(glm::vec3(vec3a.x(), vec3a.y(), vec3a.z()), glm::vec3(vec3b.x(), vec3b.y(), vec3b.z()));
	return GlmVec3(result.x, result.y, result.z);
}

GlmVec3 Glm::add(const GlmVec3& vec3a, const GlmVec3& vec3b)
{
	GlmVec3 result = vec3a;
	result.add(vec3b);
	return result;
}

GlmVec3 Glm::minus(const GlmVec3& vec3a, const GlmVec3& vec3b)
{
	GlmVec3 result = vec3a;
	result.minus(vec3b);
	return result;
}

GlmVec3 Glm::scale(const GlmVec3& vec3, float multiple)
{
	GlmVec3 result = vec3;
	result.scale(multiple);
	return result;
}

float Glm::radians(float angle)
{
	return glm::radians(angle);
}

float Glm::angle(float radians)
{
	return radians * 180 / M_PI; //acos(-1)
}