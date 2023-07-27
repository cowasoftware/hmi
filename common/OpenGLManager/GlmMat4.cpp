#include "GlmMat4.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Glm.h"

GlmMat4::GlmMat4():
m_mat4(nullptr)
{
	m_mat4 = new glm::mat4(1.0f);
}

GlmMat4::~GlmMat4()
{
	delete (glm::mat4*)m_mat4;
	m_mat4 = nullptr;
}

void GlmMat4::initPerspective(float angle, int32_t width, int32_t height, float near, float far)
{
	*(glm::mat4*)m_mat4 = glm::perspective(glm::radians(angle), width / (float)height, near, far);
}

void GlmMat4::initView(const GlmVec3& cameraPos, const GlmVec3& cameraLook, const GlmVec3& cameraUp)
{
	GlmVec3 lookPos = Glm::add(cameraPos, cameraLook);
	*(glm::mat4*)m_mat4 = glm::lookAt(glm::vec3(cameraPos.x(), cameraPos.y(), cameraPos.z()),
		glm::vec3(lookPos.x(), lookPos.y(), lookPos.z()), glm::vec3(cameraUp.x(), cameraUp.y(), cameraUp.z()));
}

void GlmMat4::translate(const GlmVec3& direction)
{
	*(glm::mat4*)m_mat4 = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x(), direction.y(), direction.z())) * (*(glm::mat4*)m_mat4);
}

void GlmMat4::angleRotate(float angle, const GlmVec3& axis)
{
	*(glm::mat4*)m_mat4 = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(axis.x(), axis.y(), axis.z())) * (*(glm::mat4*)m_mat4);
}

void GlmMat4::radiansRotate(float radians, const GlmVec3& axis)
{
	*(glm::mat4*)m_mat4 = glm::rotate(glm::mat4(1.0f), radians, glm::vec3(axis.x(), axis.y(), axis.z())) * (*(glm::mat4*)m_mat4);
}

void GlmMat4::scale(float x, float y, float z)
{
	*(glm::mat4*)m_mat4 = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z)) * (*(glm::mat4*)m_mat4);
}

void GlmMat4::scale(const GlmVec3& multiple)
{
	scale(multiple.x(), multiple.y(), multiple.z());
}

const float* GlmMat4::valuePtr() const
{
	return glm::value_ptr(*(glm::mat4*)m_mat4);
}