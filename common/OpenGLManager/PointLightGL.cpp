#include "PointLightGL.h"

PointLightGL::PointLightGL():
m_attenuationConstant(0),
m_attenuationLinear(0),
m_attenuationQuadratic(0)
{
	m_type = POINT;
}

void PointLightGL::setLightPos(const GlmVec3& lightPos)
{
	m_lightPos = lightPos;
}

GlmVec3 PointLightGL::lightPos()
{
	return m_lightPos;
}

void PointLightGL::setAttenuationDistance(int32_t distanceType)
{
	if (distanceType == 7)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.7);
		setAttenuationQuadratic(1.8);
	}
	else if (distanceType == 13)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.35);
		setAttenuationQuadratic(0.44);
	}
	else if (distanceType == 20)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.22);
		setAttenuationQuadratic(0.20);
	}
	else if (distanceType == 32)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.14);
		setAttenuationQuadratic(0.07);
	}
	else if (distanceType == 50)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.09);
		setAttenuationQuadratic(0.032);
	}
	else if (distanceType == 65)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.07);
		setAttenuationQuadratic(0.017);
	}
	else if (distanceType == 100)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.045);
		setAttenuationQuadratic(0.0075);
	}
	else if (distanceType == 160)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.027);
		setAttenuationQuadratic(0.0028);
	}
	else if (distanceType == 200)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.022);
		setAttenuationQuadratic(0.0019);
	}
	else if (distanceType == 325)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.014);
		setAttenuationQuadratic(0.0007);
	}
	else if (distanceType == 600)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.007);
		setAttenuationQuadratic(0.0002);
	}
	else if (distanceType == 3250)
	{
		setAttenuationConstant(1.0);
		setAttenuationLinear(0.0014);
		setAttenuationQuadratic(0.000007);
	}
}

void PointLightGL::setAttenuationConstant(float attenuationConstant)
{
	m_attenuationConstant = attenuationConstant;
}

void PointLightGL::setAttenuationLinear(float attenuationLinear)
{
	m_attenuationLinear = attenuationLinear;
}

void PointLightGL::setAttenuationQuadratic(float attenuationQuadratic)
{
	m_attenuationQuadratic = attenuationQuadratic;
}

float PointLightGL::attenuationConstant()
{
	return m_attenuationConstant;
}

float PointLightGL::attenuationLinear()
{
	return m_attenuationLinear;
}

float PointLightGL::attenuationQuadratic()
{
	return m_attenuationQuadratic;
}