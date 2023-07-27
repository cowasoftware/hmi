#pragma once
#include <stdint.h>
#include <vector>

struct Point3DGL
{
	Point3DGL() : m_x(0), m_y(0), m_z(0)
	{
	}

	Point3DGL(double x, double y, double z) : m_x(x), m_y(y), m_z(z)
	{
	}

	double m_x;
	double m_y;
	double m_z;
};

struct ColorInfo
{
	int32_t m_r;
	int32_t m_g;
	int32_t m_b;
	int32_t m_a;

	ColorInfo():
	m_r(0),
	m_g(0),
	m_b(0),
	m_a(0)
	{

	}

	ColorInfo(int32_t r, int32_t g, int32_t b, int32_t a):
	m_r(r),
	m_g(g),
	m_b(b),
	m_a(a)
	{
	}
};

enum MapElementType
{
	MAP_ELEMENT_INIT,
	MAP_LANE_CURVE,
	MAP_ROAD,
	MAP_CROSSROAD,
	MAP_CROSSWALK,
	MAP_SIGNAL,
	MAP_GROUND
};

struct DrawInfo
{
	MapElementType m_mapElementType;
	std::string m_mapElementId;
	int32_t m_drawType;
	int32_t m_size;
	ColorInfo m_color;

	DrawInfo():
		m_mapElementType(MAP_ELEMENT_INIT),
		m_drawType(0),
		m_size(0)
	{

	}
};

struct DrawMemoryInfo
{
	int32_t m_programId;
	int32_t m_VAOId;
	int32_t m_VBOId;

	DrawMemoryInfo():
		m_programId(0),
		m_VAOId(0),
		m_VBOId(0)
	{

	}
};