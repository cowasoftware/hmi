#include "LightGL.h"

LightGL::LightGL():
m_type(NONE)
{

}

LightGL::~LightGL()
{

}

void LightGL::setLightColor(const GlmVec3& lightColor)
{
	m_lightColor = lightColor;
}

GlmVec3 LightGL::lightColor()
{
	return m_lightColor;
}

LightGLType LightGL::type()
{
	return m_type;
}