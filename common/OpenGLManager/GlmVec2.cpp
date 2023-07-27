#include "GlmVec2.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GlmVec2::GlmVec2():
m_vec2(new glm::vec2(0.0f, 0.0f)),
m_x(((glm::vec2*)m_vec2)->x),
m_y(((glm::vec2*)m_vec2)->y)
{
	
}

GlmVec2::GlmVec2(float x, float y):
m_vec2(new glm::vec2(x, y)),
m_x(((glm::vec2*)m_vec2)->x),
m_y(((glm::vec2*)m_vec2)->y)
{
	
}

GlmVec2::GlmVec2(const GlmVec2& other):
m_vec2(new glm::vec2(other.x(), other.y())),
m_x(((glm::vec2*)m_vec2)->x),
m_y(((glm::vec2*)m_vec2)->y)
{
	
}

GlmVec2& GlmVec2::operator=(const GlmVec2& other)
{
	((glm::vec2*)m_vec2)->x = other.x();
	((glm::vec2*)m_vec2)->y = other.y();
	return *this;
}

GlmVec2::GlmVec2(GlmVec2&& other):
m_vec2(other.m_vec2),
m_x(((glm::vec2*)m_vec2)->x),
m_y(((glm::vec2*)m_vec2)->y)
{
	other.m_vec2 = nullptr;
}

GlmVec2& GlmVec2::operator=(GlmVec2&& other)
{
	((glm::vec2*)m_vec2)->x = other.x();
	((glm::vec2*)m_vec2)->y = other.y();
	delete (glm::vec2*)other.m_vec2;
	other.m_vec2 = nullptr;
	return *this;
}

GlmVec2::~GlmVec2()
{
	delete (glm::vec2*)m_vec2;
	m_vec2 = nullptr;
}

float GlmVec2::x() const
{
	return ((glm::vec2*)m_vec2)->x;
}

float GlmVec2::y() const
{
	return ((glm::vec2*)m_vec2)->y;
}

void GlmVec2::scale(float multiple)
{
	(*(glm::vec2*)m_vec2) *= multiple;
}

void GlmVec2::add(const GlmVec2& other)
{
	(*(glm::vec2*)m_vec2) += (*(glm::vec2*)other.m_vec2);
}

void GlmVec2::minus(const GlmVec2& other)
{
	(*(glm::vec2*)m_vec2) -= (*(glm::vec2*)other.m_vec2);
}