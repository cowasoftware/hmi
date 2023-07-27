#include "AutodriveManager.h"
#include <QOpenGLFramebufferObject>
#include "./qtgles3.h"
//#include "SendToMessageTest.h"
#include "OpenGLManager.h"
#include <chrono>
#include <map>
#include <unordered_map>
#include "ShaderSource.h"
#include "StbImage.h"
#include "GlmMat4.h"
#include "GlmVec3.h"
#include "Glm.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <chrono>
#include <memory>
#include "hdmap.pb.h"
#include <sstream>
#include <unordered_map>
#include <stdint.h>
#include "Util.h"
#include "DataManager.h"
#include <QThread>
#include <three.h>
#include "GlParam.h"
#include "ShaderNameDataManager.h"
#include "AssimpModel.h"
#include "PointLightGL.h"
#include "ParallelLightGL.h"
#include "SpotLightGL.h"
//#include "SendToMessageTest.h"
#include <fmt/core.h>
#include "HdmapData.h"
#include <tuple>
#include "./skybox.h"
//#include <QSize>
//#include <QImage>
//#include "SendToMessageTest.h"
#include "Cini.h"
#include "CTaskThreadManagerAPI.h"
#include "SaveFrameTask.h"
#include "Util.h"
#include "VertexShaderSource.h"
#include "FragmentShaderSource.h"
#include "TextureType.h"
#include "autodrive_renderer.h"
#include "MapConfig.h"

extern int32_t g_windowWidth;
extern int32_t g_windowHeight;
extern int32_t g_perspectiveAngle;
extern float g_perspectiveFrontBegin;
extern float g_perspectiveFrontEnd;

extern GlmVec3 g_lightPos;
extern GlmVec3 g_shineDirection;

extern std::string g_groundTexturePath;

extern double g_heroCarHeight;

extern cppgl::CppGL* g_gl;
extern glm::highp_mat4 g_view;

using namespace fmt;

extern MapConfig g_config;

AutodriveManager::AutodriveManager():
m_isInited(false)
{

}

AutodriveManager& AutodriveManager::instance()
{
	static AutodriveManager s_autodriveManager;
	return s_autodriveManager;
}

void AutodriveManager::initMap()
{
	auto manager = this;

	if (g_config.m_writeFrame)
	{
		std::string commandResult;
		Util::SystemCommand("mkdir " + Util::GetCurrentExePath() + "frame", commandResult);

		int32_t coreCount = Util::GetCPUCoreCount() * 4;
		while (coreCount-- != 0)
		{
			manager->m_vecThreadId.push_back(CTaskThreadManager::Instance().Init());
		}
	}

	//printf("init pre time = %d\n", Util::GetHighTickCountMicroRunTime(initBeginTime));

	//加载地图数据
	std::shared_ptr<COWA::MapData::HdMap> hdMap = LoadHdMap();
	//printf("init2 pre time = %d\n", Util::GetHighTickCountMicroRunTime(initBeginTime));
	ParseHdMap(hdMap);
	//printf("init3 pre time = %d\n", Util::GetHighTickCountMicroRunTime(initBeginTime));

	// RCSend("road.size = %lld", g_roadMap.size());
	//int64_t vecCurveMapSize = 0;
	//for (auto it = g_curveMap.begin(); it != g_curveMap.end(); ++it)
	//{
	//	vecCurveMapSize += it->second.size();
	//}
	CurveMapToCurveMapRelease();
	//int64_t vecCurveMapReleaseSize = 0;
	//for (auto it = g_curveMap.begin(); it != g_curveMap.end(); ++it)
	//{
	//	vecCurveMapReleaseSize += it->second.size();
	//}
	// RCSend("curve.size = %lld, vec.size = %lld, release vec.size = %lld", g_curveMap.size(), vecCurveMapSize, vecCurveMapReleaseSize);
	//
	// RCSend("lane.size = %lld", g_laneMap.size());
	CrosswalkClip();
	manager->m_verticesData = DataToVertices();
}

void AutodriveManager::init()
{
	if (m_isInited)
	{
		return;
	}

	auto manager = this;

	auto initBeginTime = Util::GetHighTickCount();

	//initMap();

	printf("init4 pre time = %d\n", Util::GetHighTickCountMicroRunTime(initBeginTime));
	// RCSend("crosswalk.size = %lld", g_crosswalkMap.size());
	// RCSend("signal.size = %lld", g_signalMap.size());
	// RCSend("crossroad.size = %lld", g_crossroadMap.size());

	//DataManager::instance().makeTreePoint(g_roadMap);

	//m_GL = new QtGLES3();
	m_GL = g_gl;
	
	//初始化环境
	OpenGLManager::instance().initGL(manager->m_GL);
	OpenGLManager::instance().initEnvironment(g_major, g_minor, g_isES);

	std::string currentExePath = Util::GetCurrentExePath();
	OpenGLManager::instance().setCurrentExePath(currentExePath);

	std::shared_ptr<ShaderNameData> spShaderNameData = ShaderNameDataManager::instance().defaultShaderNameData();
	OpenGLManager::instance().setShaderNameData(spShaderNameData);

	GlmVec3 cameraPos(581.5f, 3202.6f, 5.0f);
	OpenGLManager::instance().initCameraPos(cameraPos);

	std::vector<std::shared_ptr<LightGL>> vecLight;
	std::shared_ptr<ParallelLightGL> spParallelLightGL(new ParallelLightGL);
	spParallelLightGL->setLightDirection({-0.2f, -1.0f, -0.9f});
	spParallelLightGL->setLightColor({0.3, 0.3, 0.3});
	vecLight.push_back(spParallelLightGL);

	std::shared_ptr<SpotLightGL> spSpotLight(new SpotLightGL);
	spSpotLight->setAttenuationDistance(3250);
	spSpotLight->setCutOffAngle(g_cutOff, g_outCutOff);
	spSpotLight->setLightColor({4.0, 4.0, 4.0});
	spSpotLight->setLightPos(cameraPos);
	spSpotLight->setShineDirection({-0.4, 0.9, -0.2});
	vecLight.push_back(spSpotLight);

	MaterialGL material;
	material.setAmbientStrength({0.2f, 0.2f, 0.2f});
	material.setDiffuseStrength({1.0f, 1.0f, 1.0f});
	material.setSpecularStrength({0.4f, 0.4f, 0.4f});
	material.setShininessStrength(32.0f);

	GlmMat4 model;
	GlmMat4 projection;
	projection.initPerspective(g_perspectiveAngle, g_windowWidth, g_windowHeight,
		g_perspectiveFrontBegin, g_perspectiveFrontEnd);

	//创建顶点着色器
	VertexShaderSource vertexShaderSource;
	vertexShaderSource.init(g_major, g_minor, g_isES);
	vertexShaderSource.initShaderNameData(spShaderNameData);
	vertexShaderSource.addPosition();
	vertexShaderSource.addLight();

	//printf("vroad = %s\n", vertexShaderSource.toString().c_str());
	int32_t vertexShaderId = OpenGLManager::instance().createShader(cppgl::CPPGL_VERTEX_SHADER,
		vertexShaderSource.toString().c_str());
	std::string error = OpenGLManager::instance().getCreateShaderError(vertexShaderId);
	if (!error.empty())
	{
		std::cout << error << std::endl;
		assert(0);
	}
	
	FragmentShaderSource fragmentShaderSource;
	fragmentShaderSource.init(g_major, g_minor, g_isES);
	fragmentShaderSource.initShaderNameData(spShaderNameData);
	fragmentShaderSource.addMaterial();
	fragmentShaderSource.addAllLight(vecLight);
	fragmentShaderSource.addObjectColor();
	
	std::string source = fragmentShaderSource.toString();
	//printf("froad = %s\n", source.c_str());
	int32_t fragmentShaderId = OpenGLManager::instance().createShader(cppgl::CPPGL_FRAGMENT_SHADER,
		fragmentShaderSource.toString());
	error = OpenGLManager::instance().getCreateShaderError(fragmentShaderId);
	if (!error.empty())
	{
		std::cout << error << std::endl;
		assert(0);
	}
	
	//创建着色器程序
	manager->m_allRoadInfo.m_programId = OpenGLManager::instance().createProgram();
	OpenGLManager::instance().setProgramId(manager->m_allRoadInfo.m_programId);
	OpenGLManager::instance().addShader(vertexShaderId);
	OpenGLManager::instance().addShader(fragmentShaderId);
	OpenGLManager::instance().link();
	error = OpenGLManager::instance().getLinkShaderError();
	if (!error.empty())
	{
		std::cout << error << std::endl;
		assert(0);
	}
	
	//激活程序
	OpenGLManager::instance().activeProgram();
	
	//删除着色器
	OpenGLManager::instance().destroyShader(vertexShaderId);
	OpenGLManager::instance().destroyShader(fragmentShaderId);
	
	//创建顶点数据对象
	// uint32_t VAOId = OpenGLManager::instance().createVertexObject();
	// OpenGLManager::instance().selectVertexObject(VAOId);
	manager->m_allRoadInfo.m_VAOId = OpenGLManager::instance().createVertexObject();
	OpenGLManager::instance().selectVertexObject(manager->m_allRoadInfo.m_VAOId);
	
	//创建顶点数据对象的缓冲区
	manager->m_allRoadInfo.m_VBOId = OpenGLManager::instance().createVertexBuffer();
	OpenGLManager::instance().selectVertexBuffer(manager->m_allRoadInfo.m_VBOId);

	printf("init5 pre time = %d\n", Util::GetHighTickCountMicroRunTime(initBeginTime));
	
	OpenGLManager::instance().vertexDataCopy((void*)&manager->m_verticesData.first[0],
		manager->m_verticesData.first.size() * sizeof(float), GL_STATIC_DRAW);

	printf("init size = %d\n", (int32_t)(manager->m_verticesData.first.size() * sizeof(float)));

	printf("init6 pre time = %d\n", Util::GetHighTickCountMicroRunTime(initBeginTime));

	OpenGLManager::instance().vertexDataExplain(0, 3, cppgl::CPPGL_FLOAT, true, 6 * sizeof(float), 0);
	OpenGLManager::instance().useVertexData(0);
	OpenGLManager::instance().vertexDataExplain(1, 3, cppgl::CPPGL_FLOAT, true, 6 * sizeof(float), 3 * sizeof(float));
	OpenGLManager::instance().useVertexData(1);

	//设置绘制类型
	OpenGLManager::instance().setDrawMode(cppgl::CPPGL_FILL);
	OpenGLManager::instance().openDepthTest();

	OpenGLManager::instance().searchModifyModel(model);
	OpenGLManager::instance().searchModifyProjection(projection);
	
	//材质相关系数
	OpenGLManager::instance().searchSetMaterial(material);

	//光源
	OpenGLManager::instance().searchSetAllLight(vecLight);

	VertexShaderSource groundVertexSource;
	groundVertexSource.init(g_major, g_minor, g_isES);
	groundVertexSource.initShaderNameData(spShaderNameData);
	groundVertexSource.addPosition();
	groundVertexSource.addLight();
	if (g_config.m_isShowTexture)
	{
		groundVertexSource.addTextureCoords(1);
	}

	//printf("vground = %s\n", groundVertexSource.toString().c_str());
	vertexShaderId = OpenGLManager::instance().createShader(cppgl::CPPGL_VERTEX_SHADER,
		groundVertexSource.toString().c_str());
	if (vertexShaderId == 0)
	{
		printf("ground vertexShaderId = %d\n", vertexShaderId);
		assert(0);
	}
	error = OpenGLManager::instance().getCreateShaderError(vertexShaderId);
	if (!error.empty())
	{
		std::cout << error << std::endl;
		assert(0);
	}
	
	FragmentShaderSource groundFragmentSource;
	groundFragmentSource.init(g_major, g_minor, g_isES);
	groundFragmentSource.initShaderNameData(spShaderNameData);
	groundFragmentSource.addMaterial();
	groundFragmentSource.addAllLight(vecLight);
	if (g_config.m_isShowTexture)
	{
		std::map<int32_t, std::vector<std::string>> texturePathMap;
		texturePathMap[TextureType::TextureType_DIFFUSE].push_back(currentExePath + "resource/3d/obj/ground.jpg");
		groundFragmentSource.addTextureCoords(texturePathMap);
		groundFragmentSource.addObjectColor();
	}
	else
	{
		groundFragmentSource.addObjectColor();
	}
	
	//printf("fground = %s\n", groundFragmentSource.toString().c_str());
	fragmentShaderId = OpenGLManager::instance().createShader(GL_FRAGMENT_SHADER, groundFragmentSource.toString().c_str());
	if (fragmentShaderId == 0)
	{
		printf("ground fragmentShaderId = %d\n", fragmentShaderId);
		assert(0);
	}
	error = OpenGLManager::instance().getCreateShaderError(fragmentShaderId);
	if (!error.empty())
	{
		std::cout << error << std::endl;
		assert(0);
	}
	
	//创建着色器程序
	manager->m_groundInfo.m_programId = OpenGLManager::instance().createProgram();
	if (manager->m_groundInfo.m_programId == 0)
	{
		printf("ground programId = %d\n", manager->m_groundInfo.m_programId);
		assert(0);
	}
	OpenGLManager::instance().setProgramId(manager->m_groundInfo.m_programId);
	OpenGLManager::instance().addShader(vertexShaderId);
	OpenGLManager::instance().addShader(fragmentShaderId);
	OpenGLManager::instance().link();
	error = OpenGLManager::instance().getLinkShaderError();
	if (!error.empty())
	{
		std::cout << error << std::endl;
		assert(0);
	}
	
	//激活程序
	OpenGLManager::instance().activeProgram();
	
	//删除着色器
	OpenGLManager::instance().destroyShader(vertexShaderId);
	OpenGLManager::instance().destroyShader(fragmentShaderId);
	
	//创建顶点数据对象
	manager->m_groundInfo.m_VAOId = OpenGLManager::instance().createVertexObject();
	if (manager->m_groundInfo.m_VAOId == 0)
	{
		printf("ground VAOId = %d\n", manager->m_groundInfo.m_VAOId);
		assert(0);
	}
	OpenGLManager::instance().selectVertexObject(manager->m_groundInfo.m_VAOId);

	float viewScale = 1.0f;
	if (g_config.m_isShowTexture)
	{
		viewScale = 1.5f;
	}

	GlmVec3 center;
	std::vector<float> vecData;
	vecData.push_back(center.x() - g_perspectiveFrontEnd * viewScale);
	vecData.push_back(center.y() - g_perspectiveFrontEnd * viewScale);
	vecData.push_back(g_groundHeight);

	vecData.push_back(0.0f);
	vecData.push_back(0.0f);
	vecData.push_back(1.0f);

	if (g_config.m_isShowTexture)
	{
		vecData.push_back(0);
		vecData.push_back(0);
	}

	vecData.push_back(center.x() - g_perspectiveFrontEnd * viewScale);
	vecData.push_back(center.y() + g_perspectiveFrontEnd * viewScale);
	vecData.push_back(g_groundHeight);

	vecData.push_back(0.0f);
	vecData.push_back(0.0f);
	vecData.push_back(1.0f);

	if (g_config.m_isShowTexture)
	{
		vecData.push_back((g_perspectiveFrontEnd * viewScale * 2) / g_config.m_textureScale);
		vecData.push_back(0);
	}

	vecData.push_back(center.x() + g_perspectiveFrontEnd * viewScale);
	vecData.push_back(center.y() + g_perspectiveFrontEnd * viewScale);
	vecData.push_back(g_groundHeight);

	vecData.push_back(0.0f);
	vecData.push_back(0.0f);
	vecData.push_back(1.0f);

	if (g_config.m_isShowTexture)
	{
		vecData.push_back((g_perspectiveFrontEnd * viewScale * 2) / g_config.m_textureScale);
		vecData.push_back((g_perspectiveFrontEnd * viewScale * 2) / g_config.m_textureScale);
	}

	vecData.push_back(center.x() + g_perspectiveFrontEnd * viewScale);
	vecData.push_back(center.y() - g_perspectiveFrontEnd * viewScale);
	vecData.push_back(g_groundHeight);

	vecData.push_back(0.0f);
	vecData.push_back(0.0f);
	vecData.push_back(1.0f);

	if (g_config.m_isShowTexture)
	{
		vecData.push_back(0);
		vecData.push_back((g_perspectiveFrontEnd * viewScale * 2) / g_config.m_textureScale);
	}
	
	//创建顶点数据对象的缓冲区
	manager->m_groundInfo.m_VBOId = OpenGLManager::instance().createVertexBuffer();
	if (manager->m_groundInfo.m_VBOId == 0)
	{
		printf("ground VBOId = %d\n", manager->m_groundInfo.m_VBOId);
		assert(0);
	}
	OpenGLManager::instance().selectVertexBuffer(manager->m_groundInfo.m_VBOId);
	OpenGLManager::instance().vertexDataCopy((void*)&vecData[0], vecData.size() * sizeof(float), cppgl::CPPGL_STATIC_DRAW);
	OpenGLManager::instance().vertexDataExplain(0, 3, cppgl::CPPGL_FLOAT, true,
		(g_config.m_isShowTexture ? 8 : 6) * sizeof(float), 0);
	OpenGLManager::instance().useVertexData(0);
	OpenGLManager::instance().vertexDataExplain(1, 3, cppgl::CPPGL_FLOAT, true,
		(g_config.m_isShowTexture ? 8 : 6) * sizeof(float),
		3 * sizeof(float));
	OpenGLManager::instance().useVertexData(1);
	if (g_config.m_isShowTexture)
	{
		OpenGLManager::instance().vertexDataExplain(2, 2, cppgl::CPPGL_FLOAT, true, 8 * sizeof(float), 6 * sizeof(float));
		OpenGLManager::instance().useVertexData(2);
	}
	
	manager->m_groundTextureId = 0;
	if (g_config.m_isShowTexture)
	{
		//加载图片
		int32_t imageWidth = 0;
		int32_t imageHeight = 0;
		int32_t imageChannels = 0;
		unsigned char* imageData = StbImage::loadImage(currentExePath + g_groundTexturePath, imageWidth, imageHeight,
			imageChannels);
		if (imageData == nullptr)
		{
			std::cout << "Failed to load image" << std::endl;
			assert(0);
			return;
		}

		//创建纹理
		manager->m_groundTextureId = OpenGLManager::instance().createTexture();
		OpenGLManager::instance().selectTextureAndType(manager->m_groundTextureId, cppgl::CPPGL_TEXTURE_2D,
			"texture_0", 0);
		OpenGLManager::instance().setTextureWrapTypeX(cppgl::CPPGL_REPEAT);
		OpenGLManager::instance().setTextureWrapTypeY(cppgl::CPPGL_REPEAT);
		OpenGLManager::instance().setMinFilterType(cppgl::CPPGL_LINEAR);
		OpenGLManager::instance().setMagFilterType(cppgl::CPPGL_NEAREST);
		OpenGLManager::instance().loadTexture(imageWidth, imageHeight, imageData, imageChannels);

		//销毁图片资源
		StbImage::freeImage(imageData);
	}
	
	OpenGLManager::instance().searchSetObjectColor({g_groundColor.m_r / 255.0f, g_groundColor.m_g / 255.0f,
		g_groundColor.m_b / 255.0f});
	
	OpenGLManager::instance().openDepthTest();
	OpenGLManager::instance().searchModifyModel(model);
	OpenGLManager::instance().searchModifyProjection(projection);
	OpenGLManager::instance().searchSetAllLight(vecLight);
	OpenGLManager::instance().searchSetMaterial(material);
	

	OpenGLManager::instance().initCameraPos({ (float)(x_max - x_min) / 2, (float)(y_max - y_min) / 2 + 340, 5.0f });
	// OpenGLManager::instance().initCameraPos({(float)(x_max - x_min) / 2, (float)(y_max - y_min) / 2, (float)(z_max - z_min) / 2});
	OpenGLManager::instance().initCameraUp({ 0.0f, 0.0f, 1.0f });
	OpenGLManager::instance().initCameraFront({ 0.0f, 1.0f, 0.0f });

	//m_autodriveRenderer->initCamera();
	//m_autodriveRenderer->initScene();

	manager->m_isInited = true;

	printf("init7 pre time = %d\n", Util::GetHighTickCountMicroRunTime(initBeginTime));
	//std::thread autodriveInitThread(AutodriveInitThreadFun, this);
	//autodriveInitThread.detach();
}

bool AutodriveManager::isInited()
{
	return m_isInited;
}

void AutodriveManager::render(QOpenGLFramebufferObject* frameBuffer)
{
	if (!m_isInited)
	{
		return;
	}

	OpenGLManager::instance().openDepthTest();

	//设置背景颜色
	OpenGLManager::instance().setBackgroundColor(g_skyColor.m_r, g_skyColor.m_g, g_skyColor.m_b, g_skyColor.m_a);
	// OpenGLManager::instance().setBackgroundColor(19, 27, 39, 100);
	// OpenGLManager::instance().setBackgroundColor(140, 162, 170, 100);
	OpenGLManager::instance().brushBackground();

	OpenGLManager::instance().selectProgram(m_groundInfo.m_programId);
	OpenGLManager::instance().selectVertexObject(m_groundInfo.m_VAOId);
	

	//设置观察矩阵
	//auto& camera = camera_;
	//
	//camera.UpdateWorldMatrix();
	//auto view = camera.world_matrix_inverse;
	//auto projection = camera.projection_matrix;
	//auto camera_position = camera_.WorldPosition();
	auto heroPos = DataManager::instance().heroCarPos();
	glm::vec3 hero_position = glm::vec3(std::get<0>(heroPos) - x_min,std::get<1>(heroPos) - y_min, 1.0f);
	auto quat = DataManager::instance().heroCarQuaternion();
	auto hero_quat = glm::quat(quat.w(), quat.x(), quat.y(), quat.z());
	auto camera_position = hero_quat * g_config.m_cameraPosition + hero_position;
	auto light_pos = hero_quat * g_config.m_spotLightTarget + hero_position;
	auto spot_light_direction = glm::normalize(light_pos  - camera_position);
	GlmVec3 shineDirection = Glm::normalize({spot_light_direction.x, spot_light_direction.y, spot_light_direction.z});
	OpenGLManager::instance().setCameraPos({camera_position.x, camera_position.y, camera_position.z});
	OpenGLManager::instance().setCameraLook(shineDirection);

	//摄像机和观察位置
	GlmVec3 cameraPos = OpenGLManager::instance().getCameraPos();
	GlmVec3 cameraLook = OpenGLManager::instance().getCameraLook();
	GlmVec3 cameraUp = OpenGLManager::instance().getCameraUp();

	if (g_config.m_isShowTexture)
	{
		OpenGLManager::instance().selectTextureAndType(m_groundTextureId, GL_TEXTURE_2D, "texture_0", 0);
	}
	
	//OpenGLManager::instance().searchUpdateView();
	OpenGLManager::instance().searchSetUniformValue("view", glm::value_ptr(g_view));
	//OpenGLManager::instance().searchSetUniformValue("projection", glm::value_ptr(projection));
	OpenGLManager::instance().searchUpdateCameraPos();
	
	GlmMat4 groundModel;
	if (g_config.m_isShowTexture)
	{
		groundModel.translate({(((int32_t)(camera_position.x / g_perspectiveFrontEnd)) +
			0.5f * (int32_t)(camera_position.x > 0)) * g_perspectiveFrontEnd,
			(((int32_t)(camera_position.y / g_perspectiveFrontEnd)) +
			0.5f * (int32_t)(camera_position.y > 0)) * g_perspectiveFrontEnd,
			0.0f});
	}
	else
	{
		groundModel.translate({camera_position.x, camera_position.y, 0.0f});
	}
	
	OpenGLManager::instance().searchModifyModel(groundModel);
	OpenGLManager::instance().searchModifyLightPos(1, cameraPos);
	OpenGLManager::instance().searchModifyShineDirection(1, shineDirection);

	//OpenGLManager::instance().draw(GL_TRIANGLE_FAN, 0, 4);	

	OpenGLManager::instance().selectProgram(m_allRoadInfo.m_programId);
	OpenGLManager::instance().selectVertexObject(m_allRoadInfo.m_VAOId);

	//OpenGLManager::instance().searchUpdateView();
	OpenGLManager::instance().searchSetUniformValue("view", glm::value_ptr(g_view));
	//OpenGLManager::instance().searchSetUniformValue("projection", glm::value_ptr(projection));
	OpenGLManager::instance().searchUpdateCameraPos();
	OpenGLManager::instance().searchModifyLightPos(1, cameraPos);
	OpenGLManager::instance().searchModifyShineDirection(1, shineDirection);

	std::set<std::string> drawLaneId;
	std::set<std::string> drawRoadId;
	std::set<std::string> drawCrossroadId;
	std::set<std::string> drawCrosswalkId;
	std::set<std::string> drawSignalId;
	DataManager::instance().map(drawLaneId, drawRoadId, drawCrossroadId, drawCrosswalkId, drawSignalId);

	std::set<std::string> drawLaneCurveId = LaneIdToLaneCurveId(drawLaneId);
	drawLaneCurveId.insert("ground");
	// printf("curve size = %d\n", (int32_t)drawLaneCurveId.size());
	// for (auto it = drawLaneCurveId.begin(); it != drawLaneCurveId.end(); ++it)
	// {
	// 	printf("%s, ", it->c_str());
	// }
	// printf("\n");

	// printf("m_verticesData.second.size = %d\n", (int32_t)m_verticesData.second.size());
	//绘制图形
	int32_t drawLineIndex = 0;
	std::size_t index = -1;
	while (index++ != m_verticesData.second.size() - 1)
	{
		const DrawInfo& drawInfo = m_verticesData.second[index];
		// if (drawInfo.m_mapElementType == MAP_GROUND)
		// {
		// 	printf("1111111111111111111111111111111111111111111111111\n");
		// }
		switch (drawInfo.m_mapElementType)
		{
		case MAP_LANE_CURVE:
		{
			if (drawLaneCurveId.find(drawInfo.m_mapElementId) == drawLaneCurveId.end())
			{
				drawLineIndex += drawInfo.m_size;
				continue;
			}
		}
		break;
		case MAP_ROAD:
		{
			if (drawRoadId.find(drawInfo.m_mapElementId) == drawRoadId.end())
			{
				drawLineIndex += drawInfo.m_size;
				continue;
			}
		}
		break;
		case MAP_CROSSROAD:
		{
			if (drawCrossroadId.find(drawInfo.m_mapElementId) == drawCrossroadId.end())
			{
				drawLineIndex += drawInfo.m_size;
				continue;
			}
		}
		break;
		case MAP_CROSSWALK:
		{
			if (drawCrosswalkId.find(drawInfo.m_mapElementId) == drawCrosswalkId.end())
			{
				drawLineIndex += drawInfo.m_size;
				continue;
			}
		}
		break;
		case MAP_SIGNAL:
		{
			if (drawSignalId.find(drawInfo.m_mapElementId) == drawSignalId.end())
			{
				drawLineIndex += drawInfo.m_size;
				continue;
			}
		}
		break;
		default:
			break;
		}

		// printf("elementId = %s, elementType = %d, lineIndex = %d, size = %d\n",
		// 	drawInfo.m_mapElementId.c_str(), (int32_t)drawInfo.m_mapElementType, drawLineIndex, drawInfo.m_size);
		OpenGLManager::instance().searchSetObjectColor({drawInfo.m_color.m_r / 255.0f, drawInfo.m_color.m_g / 255.0f,
			drawInfo.m_color.m_b / 255.0f});
		OpenGLManager::instance().draw(drawInfo.m_drawType, drawLineIndex, drawInfo.m_size);
		drawLineIndex += drawInfo.m_size;
	}

	

	m_GL->UseProgram(0);
	OpenGLManager::instance().selectVertexObject(0);

	if (g_config.m_writeFrame)
	{
		std::shared_ptr<QImage> spImage(new QImage);
		*spImage = frameBuffer->toImage();
		std::shared_ptr<SaveFrameTask> spSaveFrameTask(new SaveFrameTask);
		uint64_t currentTimestamp = DataManager::instance().timestamp();
		if (currentTimestamp == m_oldTimestamp)
		{
			return;
		}
		m_oldTimestamp = currentTimestamp;
		spSaveFrameTask->setParam(currentTimestamp, m_frameId, spImage);
		CTaskThreadManager::Instance().GetThreadInterface(m_vecThreadId[m_frameId % m_vecThreadId.size()])->PostTask(spSaveFrameTask);
		++m_frameId;
	}
}

void AutodriveManager::reset()
{
	if (!m_isInited)
	{
		return;
	}
	
	m_GL->UseProgram(0);
	OpenGLManager::instance().selectVertexObject(0);
}

void AutodriveManager::uninit()
{
	m_isInited = false;
	
	if (g_config.m_writeFrame)
	{
		std::size_t index = -1;
		while (index++ != m_vecThreadId.size() - 1)
		{
			CTaskThreadManager::Instance().Uninit(m_vecThreadId[index]);
		}
	}
	
	//销毁地面纹理
	if (g_config.m_isShowTexture)
	{
		OpenGLManager::instance().destroyTexture(m_groundTextureId);
	}
	//销毁顶点对象缓冲区
	OpenGLManager::instance().destroyVertexBuffer(m_allRoadInfo.m_VBOId);
	m_allRoadInfo.m_VBOId = 0;
	OpenGLManager::instance().destroyVertexBuffer(m_groundInfo.m_VBOId);
	m_groundInfo.m_VBOId = 0;
	//销毁顶点对象
	OpenGLManager::instance().destroyVertexObject(m_allRoadInfo.m_VAOId);
	m_allRoadInfo.m_VAOId = 0;
	OpenGLManager::instance().destroyVertexBuffer(m_groundInfo.m_VAOId);
	m_groundInfo.m_VAOId = 0;
	//销毁顶点对象程序
	OpenGLManager::instance().destroyProgram(m_allRoadInfo.m_programId);
	m_allRoadInfo.m_programId = 0;
	OpenGLManager::instance().destroyVertexBuffer(m_groundInfo.m_programId);
	m_groundInfo.m_programId = 0;

	//delete skybox_;
	//memory_.Free();
	
	//delete renderer_;
	//renderer_ = nullptr;

	delete m_GL;
	m_GL = nullptr;
}