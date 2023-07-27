#include "ParallelLightGL.h"
#include "Glm.h"

ParallelLightGL::ParallelLightGL()
{
	m_type = PARALLEL;
}

void ParallelLightGL::setLightDirection(const GlmVec3& lightDirection)
{
	m_lightDirection = Glm::normalize(lightDirection);
}

GlmVec3 ParallelLightGL::lightDirection()
{
	return m_lightDirection;
}