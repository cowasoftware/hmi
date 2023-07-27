#include "SpotLightGL.h"
#include "Glm.h"
#include <math.h>

SpotLightGL::SpotLightGL()
{
	m_type = SPOT;
}

void SpotLightGL::setShineDirection(const GlmVec3& shineDirection)
{
	m_shineDirection = shineDirection;
}

GlmVec3 SpotLightGL::shineDirection()
{
	return m_shineDirection;
}

void SpotLightGL::setCutOffAngle(float cutOffAngle, float outCutOffAngle)
{
	m_cutOffCos = cos(Glm::radians(cutOffAngle));
	if (!(outCutOffAngle > cutOffAngle))
	{
		m_outCutOffCos = m_cutOffCos - 0.000001;
		return;
	}
	m_outCutOffCos = cos(Glm::radians(outCutOffAngle));
}

float SpotLightGL::cutOffCos()
{
	return m_cutOffCos;
}

float SpotLightGL::outCutOffCos()
{
	return m_outCutOffCos;
}