#include "MaterialGL.h"

MaterialGL::MaterialGL():
m_shininessStrength(0)
{
	
}

void MaterialGL::setAmbientStrength(const GlmVec3& ambientStrength)
{
	m_ambientStrength = ambientStrength;
}

GlmVec3 MaterialGL::ambientStrength() const
{
	return m_ambientStrength;
}

void MaterialGL::setDiffuseStrength(const GlmVec3& diffuseStrength)
{
	m_diffuseStrength = diffuseStrength;
}

GlmVec3 MaterialGL::diffuseStrength() const
{
	return m_diffuseStrength;
}

void MaterialGL::setSpecularStrength(const GlmVec3& specularStrength)
{
	m_specularStrength = specularStrength;
}

GlmVec3 MaterialGL::specularStrength() const
{
	return m_specularStrength;
}

void MaterialGL::setShininessStrength(float shininessStrength)
{
	m_shininessStrength = shininessStrength;
}

float MaterialGL::shininessStrength() const
{
	return m_shininessStrength;
}