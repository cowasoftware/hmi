#pragma once

#include <QOpenGLFramebufferObject>
#include <QQuickFramebufferObject>
#include <QDebug>
#include <QTimer>
#include <QRectF>

#include <cppgl.h>
#include <three.h>
#include <QImage>
#include <vector>
#include <mutex>
#include <memory>
#include "GlParam.h"

class ModelMeshInfo;
class MeshIdInfo;
class Skybox;

class AutodriveRenderer : public QObject, public QQuickFramebufferObject::Renderer
{
	enum class ObstacleType
	{
		CAR = 3,		   //小轿车
		BUS = 4,		   //大巴车
		TRUCK = 5,		   //卡车
		SPECIAL = 6,	   //特殊车
		CYCLIST = 10,	   //自行车
		TRICYCLE = 11,	   //三轮车
		MOTORCYCLIST = 12, //摩托车
		PEDESTRAIN = 20,   //行人
		ROADBLOCK = 30,	   //路障
		TREETRUNK = 31,	   //树
		POLE = 32,		   //电线杆
		PILES = 33,		   //路桩
		BLOCK = 36,		   //石墩
	};

	Q_OBJECT
public:
	AutodriveRenderer();
	virtual ~AutodriveRenderer();

public:
	QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
	void synchronize(QQuickFramebufferObject* item);
	void render() override;

public Q_SLOTS:
	void resetCamera(QRectF rect);

private:
	//void initCamera();
	//void initScene();
	//void initLights();
	//void initHero();
	//void initObstacles();
	//void initWave();
	//void initTrajectory();
	//void initCloud();
	//void initSkybox();
//
	//bool handleData();
	//void handleHero();
	//void handleObstacles();
	//void handleWave();
	//void handleTrajectory();
	//void handleCamera();
	//void handleLights();
	//void handleCloud();
	//void handleSkybox();

private:
	// hmi
	bool is_render_;
	MemoryUtil memory_;
	three::Object* hero_ = nullptr;
	std::map<uint32_t, vec3> obstacle_size_map_;
	std::map<uint32_t, std::tuple<vec3, std::vector<InstancedMesh*>>> obstacle_map_;
	three::Object* trajectory_ = nullptr;
	three::Object* wave_ = nullptr;
	PointLight* point_light_ = nullptr;
	SpotLight* spot_light_ = nullptr;
	std::vector<three::Object*> particles_;

	three::Object* pcloud_ = nullptr;
	std::map<int, std::vector<three::Object*>> clouds_;
	three::Model* cloud_ = nullptr;
	Skybox* skybox_ = nullptr;
	// three
	InteractiveEventDispatcher dispatcher_;
	PerspectiveCamera camera_;
	Scene scene_;

	three::Renderer* renderer_;
	std::string app_dir_;
	uint64_t current_ms_;
};
