#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

struct MapConfig
{
	bool m_writeFps;
	bool m_writeFrame;
	bool m_debug;
	bool m_showSky;
	bool m_pointsToLines;
	bool m_high;
	bool m_isShowTexture;
	float m_textureScale;
	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraTarget;
	std::string m_mapName;
	glm::vec3 m_spotLightTarget;
	int m_heroCarUpdateFreq;

public:
	MapConfig();

	void load(const std::string& path);
};