#include "GlmVec3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GlmVec3::GlmVec3():
m_vec3(new glm::vec3(0.0f, 0.0f, 0.0f)),
m_x(((glm::vec3*)m_vec3)->x),
m_y(((glm::vec3*)m_vec3)->y),
m_z(((glm::vec3*)m_vec3)->z)
{
	
}

GlmVec3::GlmVec3(float x, float y, float z):
m_vec3(new glm::vec3(x, y, z)),
m_x(((glm::vec3*)m_vec3)->x),
m_y(((glm::vec3*)m_vec3)->y),
m_z(((glm::vec3*)m_vec3)->z)
{
	
}

GlmVec3::GlmVec3(const GlmVec3& other):
m_vec3(new glm::vec3(other.x(), other.y(), other.z())),
m_x(((glm::vec3*)m_vec3)->x),
m_y(((glm::vec3*)m_vec3)->y),
m_z(((glm::vec3*)m_vec3)->z)
{
	
}

GlmVec3& GlmVec3::operator=(const GlmVec3& other)
{
	((glm::vec3*)m_vec3)->x = other.x();
	((glm::vec3*)m_vec3)->y = other.y();
	((glm::vec3*)m_vec3)->z = other.z();
	return *this;
}

GlmVec3::GlmVec3(GlmVec3&& other):
m_vec3(other.m_vec3),
m_x(((glm::vec3*)m_vec3)->x),
m_y(((glm::vec3*)m_vec3)->y),
m_z(((glm::vec3*)m_vec3)->z)
{
	other.m_vec3 = nullptr;
}

GlmVec3& GlmVec3::operator=(GlmVec3&& other)
{
	((glm::vec3*)m_vec3)->x = other.x();
	((glm::vec3*)m_vec3)->y = other.y();
	((glm::vec3*)m_vec3)->z = other.z();
	delete (glm::vec3*)other.m_vec3;
	other.m_vec3 = nullptr;
	return *this;
}

GlmVec3::~GlmVec3()
{
	delete (glm::vec3*)m_vec3;
	m_vec3 = nullptr;
}

float GlmVec3::x() const
{
	return ((glm::vec3*)m_vec3)->x;
}

float GlmVec3::y() const
{
	return ((glm::vec3*)m_vec3)->y;
}

float GlmVec3::z() const
{
	return ((glm::vec3*)m_vec3)->z;
}

void GlmVec3::scale(float multiple)
{
	(*(glm::vec3*)m_vec3) *= multiple;
}

void GlmVec3::add(const GlmVec3& other)
{
	(*(glm::vec3*)m_vec3) += (*(glm::vec3*)other.m_vec3);
}

void GlmVec3::minus(const GlmVec3& other)
{
	(*(glm::vec3*)m_vec3) -= (*(glm::vec3*)other.m_vec3);
}