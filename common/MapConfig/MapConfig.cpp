#include "MapConfig.h"
#include "Cini.h"
#include "ini_reader.h"

bool g_pointsToLines = false;

MapConfig::MapConfig():
m_writeFps(false),
m_writeFrame(false),
m_debug(false),
m_showSky(false),
m_pointsToLines(false),
m_high(false),
m_isShowTexture(false),
m_textureScale(2.0)
{

}

void MapConfig::load(const std::string& path)
{
	Cini ini(path);
	IniReader reader;
	std::string key;

	key = "writeFps";
	reader.Read(key, ini.readIni(key), m_writeFps);

	key = "writeFrame";
	reader.Read(key, ini.readIni(key), m_writeFrame);

	key = "debug";
	reader.Read(key, ini.readIni(key), m_debug);

	key = "showSky";
	reader.Read(key, ini.readIni(key), m_showSky);

	key = "pointsToLines";
	reader.Read(key, ini.readIni(key), m_pointsToLines);
	g_pointsToLines = m_pointsToLines;

	key = "high";
	reader.Read(key, ini.readIni(key), m_high);

	key = "isShowTexture";
	reader.Read(key, ini.readIni(key), m_isShowTexture);

	key = "textureScale";
	reader.Read(key, ini.readIni(key), m_textureScale);

	key = "cameraPosition";
	reader.Read(key, ini.readIni(key), m_cameraPosition);

	key = "cameraTarget";
	reader.Read(key, ini.readIni(key), m_cameraTarget);

	key = "mapName";
	reader.Read(key, ini.readIni(key), m_mapName);

	key = "spotLightTarget";
	reader.Read(key, ini.readIni(key), m_spotLightTarget);

	key = "heroCarUpdateFreq";
	reader.Read(key, ini.readIni(key), m_heroCarUpdateFreq);
}