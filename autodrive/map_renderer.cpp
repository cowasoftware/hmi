
#include <cstdint>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <map>
#include <unordered_map>
#include <fstream>
#include <memory>

#include <QCoreApplication>
#include <QThread>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "skybox.h"

#include "OpenGLManager.h"
#include "DataManager.h"
#include "ShaderSource.h"
#include "StbImage.h"
#include "GlmMat4.h"
#include "GlmVec3.h"
#include "Glm.h"
#include "hdmap.pb.h"
#include "Util.h"
#include "GlParam.h"
#include "ShaderNameDataManager.h"
#include "AssimpModel.h"
#include "PointLightGL.h"
#include "ParallelLightGL.h"
#include "SpotLightGL.h"
#include "HdmapData.h"

#include "CTaskThreadManagerAPI.h"
#include "SaveFrameTask.h"
#include "VertexShaderSource.h"
#include "FragmentShaderSource.h"
#include "TextureType.h"

#include "map_renderer.h"

#include "MapConfig.h"
#include "AutodriveManager.h"
//#include "SendToMessageTest.h"

extern int32_t g_windowWidth;
extern int32_t g_windowHeight;
extern int32_t g_perspectiveAngle;
extern float g_perspectiveFrontBegin;
extern float g_perspectiveFrontEnd;

extern GlmVec3 g_cameraPos;
extern GlmVec3 g_lightPos;
extern GlmVec3 g_shineDirection;

extern std::string g_groundTexturePath;

glm::highp_mat4 g_view;
glm::highp_mat4 g_perspective;
extern MapConfig g_config;
bool g_mapHasInit = false;

MapRenderer::MapRenderer(cppgl::CppGL* gl, QObject* parent):
QObject(parent),
m_GL(gl)
{
	//RCSend("m_GL0 = %p", m_GL);
}

MapRenderer::~MapRenderer()
{
	//RCSend("m_GL = %p", m_GL);
	m_GL = nullptr;
}

void InitMapThreadFun(MapRenderer* mapRenderer)
{
	AutodriveManager::instance().initMap();
	Q_EMIT mapRenderer->mapInited();
}

void MapRenderer::Init()
{
	QObject::connect(this, &MapRenderer::mapInited, this, &MapRenderer::onMapInited, Qt::QueuedConnection);

	auto currentExePath = Util::GetCurrentExePath();



	if (!g_mapHasInit)
	{
		g_mapHasInit = true;
		std::thread initMapThread(InitMapThreadFun, this);
		initMapThread.detach();
	}
}

void MapRenderer::Sync()
{
}

void MapRenderer::Render()
{
	// 设置观察矩阵
	auto hero_xy_position = DataManager::instance().heroCarPos();
	auto hero_position = glm::vec3(std::get<0>(hero_xy_position)- x_min, std::get<1>(hero_xy_position) - y_min, 1.0f);
	auto hero_quat = glm::quat(vec3(0, 0, DataManager::instance().heroCarTheta()));
	auto camera_position = hero_position + hero_quat * g_config.m_cameraPosition;
	auto camera_target = hero_position + hero_quat * g_config.m_cameraTarget;
	g_view = glm::lookAt(camera_position, camera_target, vec3(0, 0, 1));
	g_perspective = glm::perspective(glm::radians((float)g_perspectiveAngle), (float)g_windowWidth / (float)g_windowHeight, g_perspectiveFrontBegin, g_perspectiveFrontEnd);

	AutodriveManager::instance().render(nullptr);

	//RCSend("m_GL2 = %p", m_GL);
	AutodriveManager::instance().reset();
}

void MapRenderer::ResetCamera(QRectF rect)
{
	g_windowWidth = (int32_t)rect.width();
	g_windowHeight = (int32_t)rect.height();
}

void MapRenderer::onMapInited()
{
	AutodriveManager::instance().init();
}