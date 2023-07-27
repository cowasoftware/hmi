#include "GlmVec4.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GlmVec4::GlmVec4():
m_vec4(new glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
m_x(((glm::vec4*)m_vec4)->x),
m_y(((glm::vec4*)m_vec4)->y),
m_z(((glm::vec4*)m_vec4)->z),
m_w(((glm::vec4*)m_vec4)->w)
{
	
}

GlmVec4::GlmVec4(float x, float y, float z, float w):
m_vec4(new glm::vec4(x, y, z, w)),
m_x(((glm::vec4*)m_vec4)->x),
m_y(((glm::vec4*)m_vec4)->y),
m_z(((glm::vec4*)m_vec4)->z),
m_w(((glm::vec4*)m_vec4)->w)
{
	
}

GlmVec4::GlmVec4(const GlmVec4& other):
m_vec4(new glm::vec4(other.x(), other.y(), other.z(), other.w())),
m_x(((glm::vec4*)m_vec4)->x),
m_y(((glm::vec4*)m_vec4)->y),
m_z(((glm::vec4*)m_vec4)->z),
m_w(((glm::vec4*)m_vec4)->w)
{
	
}

GlmVec4& GlmVec4::operator=(const GlmVec4& other)
{
	((glm::vec4*)m_vec4)->x = other.x();
	((glm::vec4*)m_vec4)->y = other.y();
	((glm::vec4*)m_vec4)->z = other.z();
	((glm::vec4*)m_vec4)->w = other.w();
	return *this;
}

GlmVec4::GlmVec4(GlmVec4&& other):
m_vec4(other.m_vec4),
m_x(((glm::vec4*)m_vec4)->x),
m_y(((glm::vec4*)m_vec4)->y),
m_z(((glm::vec4*)m_vec4)->z),
m_w(((glm::vec4*)m_vec4)->w)
{
	other.m_vec4 = nullptr;
}

GlmVec4& GlmVec4::operator=(GlmVec4&& other)
{
	((glm::vec4*)m_vec4)->x = other.x();
	((glm::vec4*)m_vec4)->y = other.y();
	((glm::vec4*)m_vec4)->z = other.z();
	((glm::vec4*)m_vec4)->w = other.w();
	delete (glm::vec4*)other.m_vec4;
	other.m_vec4 = nullptr;
	return *this;
}

GlmVec4::~GlmVec4()
{
	delete (glm::vec4*)m_vec4;
	m_vec4 = nullptr;
}

float GlmVec4::x() const
{
	return ((glm::vec4*)m_vec4)->x;
}

float GlmVec4::y() const
{
	return ((glm::vec4*)m_vec4)->y;
}

float GlmVec4::z() const
{
	return ((glm::vec4*)m_vec4)->z;
}

float GlmVec4::w() const
{
	return ((glm::vec4*)m_vec4)->w;
}

void GlmVec4::scale(float multiple)
{
	(*(glm::vec4*)m_vec4) *= multiple;
}

void GlmVec4::add(const GlmVec4& other)
{
	(*(glm::vec4*)m_vec4) += (*(glm::vec4*)other.m_vec4);
}

void GlmVec4::minus(const GlmVec4& other)
{
	(*(glm::vec4*)m_vec4) -= (*(glm::vec4*)other.m_vec4);
}