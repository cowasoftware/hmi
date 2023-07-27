#include <QOpenGLFramebufferObject>
#include <QCoreApplication>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include "./autodrive_renderer.h"
#include "./qtgles3.h"
// #include "SendToMessageTest.h"
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
// #include "SendToMessageTest.h"
#include <fmt/core.h>
#include "HdmapData.h"
#include <tuple>
#include "./skybox.h"
// #include <QSize>
// #include <QImage>
// #include "SendToMessageTest.h"
#include "Cini.h"
#include "CTaskThreadManagerAPI.h"
#include "SaveFrameTask.h"
#include "Util.h"
#include "VertexShaderSource.h"
#include "FragmentShaderSource.h"
#include "TextureType.h"
#include "AutodriveManager.h"
#include "MapConfig.h"

extern int32_t g_windowWidth;
extern int32_t g_windowHeight;
extern int32_t g_perspectiveAngle;
extern float g_perspectiveFrontBegin;
extern float g_perspectiveFrontEnd;

extern GlmVec3 g_lightPos;
extern GlmVec3 g_shineDirection;

extern std::string g_groundTexturePath;

using namespace fmt;

extern MapConfig g_config;

static vec3 cameraPosition = vec3(0, 0, 0);
static vec3 cameraTarget = vec3(0, 0, 0);
static int64_t cloudLimit = 0;

//static std::vector<vec4> calcluateColor(size_t len, uint32_t rgba)
//{
//	auto fun = [](float x)
//	{
//		return 1 - 1 / (0.01 * x * x + 0.0001 * x + 1);
//	};
//
//	float opacity = 1.0f;
//	float r = ((rgba >> 24) & 0xff) / 256.0f;
//	float g = ((rgba >> 16) & 0xff) / 256.0f;
//	float b = ((rgba >> 8) & 0xff) / 256.0f;
//	float a = (rgba & 0xff) / 256.0f;
//
//	std::vector<vec4> colors(len);
//	std::vector<float> opacitys(len);
//	int index = 0;
//	for (size_t i = len; i > 0; i--)
//	{
//		opacity = a * fun((float)i);
//
//		opacitys[index] = opacity;
//		colors[index++] = vec4(r, g, b, opacity);
//	}
//
//	return colors;
//}
//
//static std::vector<InstancedMesh*> LoadInstancedMesh(std::string const& file, int32_t count)
//{
//	ObjectLoader loader;
//	std::vector<InstancedMesh*> meshes;
//
//	auto object = loader.Load(file);
//	if (!object)
//	{
//		return meshes;
//	}
//
//	std::vector<Object*> wait_free_objects;
//
//	auto call = [&](Object& obj)
//	{
//		if (obj.IsModel())
//		{
//			auto& model = static_cast<Model&>(obj);
//			auto& mesh = *new InstancedMesh(model.geometry, model.material, count);
//			meshes.push_back(&mesh);
//		}
//		wait_free_objects.push_back(&obj);
//	};
//
//	object->TraverseVisible(call);
//
//	for (auto obj : wait_free_objects)
//	{
//		delete obj;
//	}
//
//	return meshes;
//}
//
//static std::vector<InstancedMesh*> CopyInstancedMesh(std::vector<InstancedMesh*> const& origin, int32_t count)
//{
//	std::vector<InstancedMesh*> meshes(origin.size());
//
//	size_t index = 0;
//
//	for (auto mesh : origin)
//	{
//		meshes[index++] = new InstancedMesh(mesh->geometry, mesh->material, count);
//	}
//
//	return meshes;
//}

AutodriveRenderer::AutodriveRenderer()
{
	AutodriveManager::instance().init();
}

AutodriveRenderer::~AutodriveRenderer()
{
	
}

void AutodriveRenderer::render()
{
	AutodriveManager::instance().render(g_config.m_writeFrame ? framebufferObject() : nullptr);

	// static int32_t imageIndex = 0;
	// frameImage.save(QString::fromStdString("/home/xylsxyls/cowa/tboxhmi/build/bin/image/a" + std::to_string(imageIndex++) + ".png"));
	// SaveFrame();

	if (g_config.m_writeFps)
	{
		printf("fps: %ld\n", ClockUtil::fps());
	}
}

QOpenGLFramebufferObject *AutodriveRenderer::createFramebufferObject(const QSize &size)
{
	QOpenGLFramebufferObjectFormat format;
	format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil); // attach后需要开启gl.DEPTH_TEST
	format.setSamples(4);
	return new QOpenGLFramebufferObject(size, format);
}

void AutodriveRenderer::synchronize(QQuickFramebufferObject *item)
{
	//current_ms_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//is_render_ = handleData();
}

void AutodriveRenderer::resetCamera(QRectF rect)
{
	//auto& camera = camera_;

	//camera.aspect = rect.width() / rect.height();
	//camera.UpdateProjectionMatrix();
}

//void AutodriveRenderer::initCamera()
//{
//	auto& camera = camera_;
//	camera.fov = glm::radians(45.0f);
//	camera.up = vec3(0, 0, 1);
//	camera.TranslateTo(vec3(1, 1, 1));
//	camera.LookAt(vec3(0.0, 0.0, 0.0));
//	camera.UpdateWorldMatrix();
//	camera.UpdateProjectionMatrix();
//
//	std::string key;
//	std::string value;
//
//	key = "cameraPosition";
//	value = StringUtil::Replace(iniConfig.readIni(key), std::regex("\\s*"), [](auto iter)
//		{ return std::string(); });
//
//	if (std::sscanf(value.c_str(), "%f,%f,%f", &cameraPosition.x, &cameraPosition.y, &cameraPosition.z) != 3)
//	{
//		std::cerr << "invalid ini format, please check it: " << key << std::endl;
//		cameraPosition = vec3(-12, 0, 5);
//	}
//
//	key = "cameraTarget";
//	value = StringUtil::Replace(iniConfig.readIni(key), std::regex("\\s*"), [](auto iter)
//		{ return std::string(); });
//
//	if (std::sscanf(value.c_str(), "%f,%f,%f", &cameraTarget.x, &cameraTarget.y, &cameraTarget.z) != 3)
//	{
//		std::cerr << "invalid ini format, please check it: " << key << std::endl;
//		cameraTarget = vec3(8, 0, 0);
//	}
//}
//
//void AutodriveRenderer::initScene()
//{
//	initLights();
//	initHero();
//	initObstacles();
//	initWave();
//	initTrajectory();
//	initCloud();
//	initSkybox();
//}
//
//void AutodriveRenderer::initLights()
//{
//	auto& ambient_light = *new AmbientLight(0xffffff, 1);
//	scene_.Add(ambient_light);
//	memory_.Add(ambient_light);
//
//	spot_light_ = new SpotLight(0xffffff, 2, 500, glm::radians(40.0f), 1);
//	scene_.Add(*spot_light_);
//	memory_.Add(*spot_light_);
//}
//
//void AutodriveRenderer::initHero()
//{
//	ObjectLoader loader;
//
//	if ((hero_ = loader.Load(app_dir_ + "/resource/3d/obj/passenger-car/passenger-car.obj")) != nullptr)
//	{
//		scene_.Add(*hero_);
//		memory_.Add(*hero_);
//	}
//}
//
//void AutodriveRenderer::initObstacles()
//{
//	std::string high;
//	if (g_high)
//	{
//		high = "high/";
//	}
//	std::map<ObstacleType, std::tuple<vec3, std::string>> obstacle_file_map{
//		{ObstacleType::CAR, {vec3(3.8f, 1.7f, 1.3f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/trolley/trolley.obj"}},					   //小轿车
//		{ObstacleType::BUS, {vec3(6.2f, 2.2f, 2.0f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/bus/bus.obj"}},							   //大巴车
//		{ObstacleType::TRUCK, {vec3(5.2f, 2.0f, 2.0f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/truck/truck.obj"}},					   //卡车
//		{ObstacleType::SPECIAL, {vec3(5.3f, 2.0f, 2.3f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/special-vehicle/special-vehicle.obj"}}, //特殊车
//		{ObstacleType::CYCLIST, {vec3(0.0f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/bike/bike.obj"}},								   //自行车
//		{ObstacleType::TRICYCLE, {vec3(0.0f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/tricycle/tricycle.obj"}},						   //三轮车
//		{ObstacleType::MOTORCYCLIST, {vec3(0.0f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/motorcycle/motorcycle.obj"}},				   //摩托车
//		{ObstacleType::PEDESTRAIN, {vec3(), app_dir_ + "/resource/3d/obj/" + high + "obstacle/people/people2/people2.obj"}},					   //行人
//		{ObstacleType::ROADBLOCK, {vec3(0.47f, 0.47f, 0.47f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/roadblock/roadblock.obj"}},		   //路障
//		{ObstacleType::TREETRUNK, {vec3(1.0f, 1.0f, 3.5f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/trees/trees.obj"}},				   //树
//		{ObstacleType::POLE, {vec3(0.3f, 0.3f, 0.75f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/light-pole/light-pole.obj"}},			   //电线杆
//		{ObstacleType::PILES, {vec3(0.15f, 0.15f, 0.75f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/stone-pier/stone-pier.obj"}},		   //路桩
//		{ObstacleType::BLOCK, {vec3(0.4f, 0.4f, 0.5f), app_dir_ + "/resource/3d/obj/" + high + "obstacle/road-stakes/road-stakes.obj"}},		   //石墩
//	};
//
//	for (auto& file_pair : obstacle_file_map)
//	{
//		auto obstacle_size = std::get<0>(file_pair.second);
//		auto obstacle = LoadInstancedMesh(std::get<1>(file_pair.second), 100);
//		if (obstacle.empty())
//		{
//			continue;
//		}
//
//		for (auto part : obstacle)
//		{
//			scene_.Add(*part);
//			memory_.Add(*part);
//			part->draw_count = 0;
//		}
//
//		obstacle_map_.emplace((uint32_t)file_pair.first, std::move(std::make_tuple(obstacle_size, std::move(obstacle))));
//	}
//}
//
//void AutodriveRenderer::initWave()
//{
//	// 雷达探测波
//	auto& geometry = *new CircleGeometry(1, 36);
//	auto& material = *new MeshBasicMaterial(0x707070, true, 0.3);
//	wave_ = new Mesh(geometry, material);
//
//	memory_.Add(*wave_);
//	scene_.Add(*wave_);
//}
//
//void AutodriveRenderer::initTrajectory()
//{
//	// 轨迹线
//	uint32_t max_len = 2000;
//	auto& trajectory_geometry = *new Geometry();
//	trajectory_geometry.SetAttribute("position", *new GeometryAttribute(Array(std::vector<float>(3 * max_len)), 3, false, Usage::DYNAMIC_DRAW));
//	trajectory_geometry.SetAttribute("color", *new GeometryAttribute(Array(std::vector<float>(4 * max_len)), 4, false, Usage::DYNAMIC_DRAW));
//	trajectory_geometry.SetIndex(*new GeometryAttribute(Array(std::vector<uint32_t>(6 * max_len)), 1, false, Usage::DYNAMIC_DRAW));
//	auto& trajectory_material = *new MeshBasicMaterial(0xffffff, true);
//	trajectory_material.vertex_colors = true;
//	trajectory_ = new Mesh(trajectory_geometry, trajectory_material);
//	scene_.Add(*trajectory_);
//	memory_.Add(*trajectory_);
//}
//
//void AutodriveRenderer::initCloud()
//{
//	// // 加载点云
//	// auto origin_clouds_map = DataManager::instance().objectPointList();
//	// auto origin_clouds_positions = DataManager::instance().treePoint();
//
//	// uint32_t clouds_count = 0;
//
//	// for(auto& road_clouds_positions: origin_clouds_positions)
//	// {
//	// 	for(auto& cloud_position: road_clouds_positions)
//	// 	{
//	// 		clouds_count++;
//	// 	}
//	// }
//
//	// std::cout <<"init point cloud: " << origin_clouds_map.size() << std::endl;
//	// std::vector<float> clouds_vertices;
//
//	// for (auto &clouds : origin_clouds_map)
//	// {
//	// 	for (auto &cloud : clouds.second)
//	// 	{
//	// 		std::vector<float> cloud_vertices(cloud.size() * 3);
//	// 		int index = 0;
//	// 		for (auto &p : cloud)
//	// 		{
//	// 			cloud_vertices[index++] = p.m_x;
//	// 			cloud_vertices[index++] = p.m_y;
//	// 			cloud_vertices[index++] = p.m_z;
//	// 		}
//	// 		auto &cloud_geometry = *new Geometry();
//	// 		cloud_geometry.SetAttribute("position", *new GeometryAttribute(Array(cloud_vertices), 3, false));
//	// 		auto &cloud_material = *new PointsMaterial(0xFFFFFF, 1);
//	// 		auto &point = *new InstancedMesh(cloud_geometry, cloud_material,clouds_count);
//	// 		point.draw_mode = DrawMode::Points;
//
//	// 		uint32_t i = 0;
//
//	// 		for(auto& road_clouds_positions: origin_clouds_positions)
//	// 		{
//	// 			for(auto& cloud_position: road_clouds_positions)
//	// 			{
//	// 				auto m = glm::translate(mat4(1.0f), vec3(cloud_position.m_x, cloud_position.m_y,cloud_position.m_z));
//	// 				point.UpdateMatrixAt(i++, m);
//	// 			}
//	// 		}
//
//	// 		clouds_[clouds.first].push_back(&point);
//	// 		memory_.Add(point);
//	// 	}
//	// }
//
//	// if (!clouds_.empty() && !clouds_.begin()->second.empty())
//	// {
//	// 	auto &cloud = *clouds_.begin()->second.front();
//	// 	pcloud_ = &cloud;
//	// 	scene_.Add(cloud);
//	// }
//
//	auto value = iniConfig.readIni("cloudLimit");
//	cloudLimit = atoll(value.c_str());
//
//	auto cloud = DataManager::instance().cloud();
//
//	auto vertices = std::vector<float>(cloudLimit * 3);
//	std::transform(cloud.begin(), cloud.begin() + std::min(vertices.size(), cloud.size()), vertices.begin(), [](auto& v)
//		{ return v; });
//	auto& geometry = *new Geometry();
//	auto& position = *new GeometryAttribute(Array(std::move(vertices)), 3, false, Usage::STATIC_DRAW);
//	position.update_range.count = cloud.size();
//	geometry.SetAttribute("position", position);
//	auto& material = *new PointsMaterial;
//	std::string pointColor = iniConfig.readIni("PointColor");
//	int32_t r = 0;
//	int32_t g = 0;
//	int32_t b = 0;
//	sscanf(pointColor.c_str(), "%d,%d,%d", &r, &g, &b);
//	material.color.r = r / 255.0f;
//	material.color.g = g / 255.0f;
//	material.color.b = b / 255.0f;
//	material.transparent = true;
//	cloud_ = new Points(geometry, material);
//	scene_.Add(*cloud_);
//	memory_.Add(*cloud_);
//}
//
//void AutodriveRenderer::initSkybox()
//{
//	std::vector<std::string> files{
//		app_dir_ + "/resource/3d/texture/skybox/right.jpg",
//		app_dir_ + "/resource/3d/texture/skybox/left.jpg",
//		app_dir_ + "/resource/3d/texture/skybox/top.jpg",
//		app_dir_ + "/resource/3d/texture/skybox/bottom.jpg",
//		app_dir_ + "/resource/3d/texture/skybox/front.jpg",
//		app_dir_ + "/resource/3d/texture/skybox/back.jpg",
//
//	};
//
//	skybox_->Init(files);
//}
//
//bool AutodriveRenderer::handleData()
//{
//	handleHero();
//	handleWave();
//	handleTrajectory();
//	handleObstacles();
//	handleCamera();
//	handleLights();
//	handleCloud();
//	return true;
//}
//
//void AutodriveRenderer::handleHero()
//{
//	// 更新主车位置和角度
//	if (!hero_)
//	{
//		return;
//	}
//
//	auto here_position = DataManager::instance().heroCarPos();
//	vec3 tranform = vec3(here_position.first - x_min, here_position.second - y_min, 1.0f);
//	double radians = DataManager::instance().heroCarTheta();
//	hero_->TranslateTo(tranform);
//	hero_->RotateTo(quat(vec3(0.0f, 0.0f, radians)));
//	hero_->UpdateWorldMatrix();
//}
//
//void AutodriveRenderer::handleObstacles()
//{
//	auto origin_obstacle_map = DataManager::instance().obstacleMap();
//	auto obstacle_matrix_map = std::map<uint32_t, std::vector<std::tuple<vec3, float, vec3>>>();
//
//	// 计算障碍物世界矩阵
//	for (auto& obstacle_pair : origin_obstacle_map)
//	{
//		auto& obstacle = obstacle_pair.second;
//		obstacle_matrix_map[obstacle_pair.second.m_type].emplace_back(std::move(std::make_tuple(
//			vec3(obstacle.m_position.m_x - x_min, obstacle.m_position.m_y - y_min, 1.0f),
//			obstacle.m_theta,
//			vec3(obstacle.m_length, obstacle.m_width, obstacle.m_height))));
//	}
//
//	//扩大实例化最大个数
//	for (auto& matrix_pair : obstacle_matrix_map)
//	{
//		auto obstacle_iter = obstacle_map_.find(matrix_pair.first);
//		if (obstacle_iter == obstacle_map_.end())
//		{
//			continue;
//		}
//
//		auto& obstacle = std::get<1>(obstacle_iter->second);
//
//		if (matrix_pair.second.size() > obstacle.front()->instance_matrices.count)
//		{
//			auto new_obstacle = CopyInstancedMesh(obstacle, matrix_pair.second.size());
//
//			for (auto part : new_obstacle)
//			{
//				scene_.Add(*part);
//				memory_.Add(*part);
//				part->draw_count = 0;
//			}
//
//			for (auto part : obstacle)
//			{
//				scene_.Remove(*part);
//				memory_.Remove(*part);
//			}
//
//			obstacle = std::move(new_obstacle);
//		}
//	}
//
//	for (auto& obstacle_pair : obstacle_map_)
//	{
//		auto matrix_iter = obstacle_matrix_map.find(obstacle_pair.first);
//
//		if (matrix_iter == obstacle_matrix_map.end())
//		{
//			auto& obstacle = std::get<1>(obstacle_pair.second);
//			for (auto& part : obstacle)
//			{
//				part->draw_count = 0;
//			}
//		}
//		else
//		{
//			auto& obstacle_size = std::get<0>(obstacle_pair.second);
//
//			int32_t index = 0;
//
//			for (auto& m : matrix_iter->second)
//			{
//				auto instance_matrix = mat4(1.0f);
//				auto& scale = std::get<2>(m);
//				instance_matrix = glm::translate(mat4(1.0f), std::get<0>(m)) * glm::rotate(mat4(1.0f), std::get<1>(m), vec3(0.0f, 0.0f, 1.0f));
//
//				if (obstacle_size.x > 0 && obstacle_size.y > 0 && obstacle_size.z > 0)
//				{
//					instance_matrix = instance_matrix * glm::scale(mat4(1.0f), vec3(scale.x / obstacle_size.x, scale.y / obstacle_size.y, scale.z / obstacle_size.z));
//				}
//
//				auto& obstacle = std::get<1>(obstacle_pair.second);
//
//				for (auto& part : obstacle)
//				{
//					part->UpdateMatrixAt(index, instance_matrix);
//					part->instance_matrices.NeedUpdate(true);
//					part->draw_count = matrix_iter->second.size();
//				}
//
//				index++;
//			}
//		}
//	}
//}
//
//void AutodriveRenderer::handleWave()
//{
//	if (!hero_ || !wave_)
//	{
//		return;
//	}
//
//	static auto animate = [](uint64_t ms)
//	{
//		const auto speed = 5.0f;			  // 单位m/s;
//		const auto duration = uint64_t(3500); //单位ms
//		const auto interval = uint64_t(1500); //单位ms
//
//		auto progress = ms % (duration + interval);
//
//		if (progress < duration)
//		{
//			return speed * progress / 1000.0f;
//		}
//		else
//		{
//			return 0.0f;
//		}
//	};
//
//	wave_->TranslateTo(hero_->WorldPosition() + vec3(0.0f, 0.0f, 0.01));
//	wave_->ScaleTo(animate(current_ms_));
//	wave_->UpdateWorldMatrix();
//}
//
//void AutodriveRenderer::handleTrajectory()
//{
//	if (!hero_ || !trajectory_)
//	{
//		return;
//	}
//
//	auto origin_trajectory_points = DataManager::instance().trajectoryPoints();
//
//	auto max_count = std::min(origin_trajectory_points.size(), (size_t)2000);
//	auto trajectory_points = std::vector<vec3>();
//	auto direction = hero_->quaternion * vec3(1.0f, 0.0f, 0.0f);
//	auto v = vec3(0.0f);
//
//	for (size_t i = 1; i < max_count; i++)
//	{
//		v.x = origin_trajectory_points[i].m_x - origin_trajectory_points[i - 1].m_x;
//		v.y = origin_trajectory_points[i].m_y - origin_trajectory_points[i - 1].m_y;
//		v.z = origin_trajectory_points[i].m_z - origin_trajectory_points[i - 1].m_z;
//
//		if (glm::dot(direction, v) > 0)
//		{
//			trajectory_points.emplace_back(vec3(origin_trajectory_points[i].m_x - x_min, origin_trajectory_points[i].m_y - y_min, g_trajectoryHeight));
//			direction = v;
//		}
//	}
//
//	max_count = trajectory_points.size();
//
//	if (max_count < 3)
//	{
//		return;
//	}
//
//	auto make_point = [](vec3 const& p1, vec3 const& p2, float width)
//	{
//		auto offset = glm::normalize(glm::cross(vec3(0.0f, 0.0, 1.0f), p2 - p1));
//		return std::make_pair(p1 + offset * 0.5f * width, p1 - offset * 0.5f * width);
//	};
//
//	std::vector<float> trajectory_positions;
//	std::vector<uint32_t> trajectory_indices;
//	std::vector<float> trajectory_colors;
//
//	auto colors = calcluateColor(max_count, 0x087ff290);
//
//	for (size_t i = 1; i < max_count; i++)
//	{
//		auto& p1 = trajectory_points[i - 1];
//		auto& p2 = trajectory_points[i];
//
//		auto p12 = make_point(p1, p2, (float)g_trajectoryWidth);
//		trajectory_positions.push_back(p12.first.x);
//		trajectory_positions.push_back(p12.first.y);
//		trajectory_positions.push_back(p12.first.z);
//		trajectory_positions.push_back(p12.second.x);
//		trajectory_positions.push_back(p12.second.y);
//		trajectory_positions.push_back(p12.second.z);
//
//		trajectory_colors.push_back(colors[i].r);
//		trajectory_colors.push_back(colors[i].g);
//		trajectory_colors.push_back(colors[i].b);
//		trajectory_colors.push_back(colors[i].a);
//		trajectory_colors.push_back(colors[i].r);
//		trajectory_colors.push_back(colors[i].g);
//		trajectory_colors.push_back(colors[i].b);
//		trajectory_colors.push_back(colors[i].a);
//	}
//
//	for (size_t i = 0; i < max_count - 2; i++)
//	{
//		trajectory_indices.push_back(2 * i);
//		trajectory_indices.push_back(2 * i + 1);
//		trajectory_indices.push_back(2 * i + 2);
//		trajectory_indices.push_back(2 * i + 1);
//		trajectory_indices.push_back(2 * i + 2);
//		trajectory_indices.push_back(2 * i + 3);
//	}
//
//	auto& trajetory = static_cast<Mesh&>(*trajectory_);
//	auto& geometry = trajetory.geometry;
//
//	auto& position = *geometry.GetAttribute("position");
//	position.array = trajectory_positions;
//	position.count = trajectory_positions.size() / 3;
//	position.update_range.count = trajectory_positions.size();
//	position.NeedUpdate(true);
//
//	auto& color = *geometry.GetAttribute("color");
//	color.array = trajectory_colors;
//	color.count = trajectory_colors.size() / 4;
//	color.update_range.count = trajectory_colors.size();
//	color.NeedUpdate(true);
//
//	auto& index = *geometry.GetIndex();
//	index.array = trajectory_indices;
//	index.count = trajectory_indices.size();
//	index.update_range.count = trajectory_indices.size();
//	index.NeedUpdate(true);
//
//	// print("position: {}\n",trajectory_positions.size());
//}
//
//void AutodriveRenderer::handleCamera()
//{
//	if (!hero_)
//	{
//		return;
//	}
//
//	auto target_position = hero_->WorldPosition();
//	auto qua = hero_->WorldQuaternion();
//
//	camera_.TranslateTo(qua * cameraPosition + target_position);
//	camera_.LookAt(target_position + qua * cameraTarget);
//	camera_.UpdateWorldMatrix();
//}
//
//void AutodriveRenderer::handleLights()
//{
//	if (!hero_ || !spot_light_)
//	{
//		return;
//	}
//
//	spot_light_->TranslateTo( camera_.position);
//	spot_light_->target = hero_->position + hero_->quaternion  * vec3(1.0f, 0.0f, 0.0f);
//	spot_light_->UpdateWorldMatrix();
//}
//
//void AutodriveRenderer::handleCloud()
//{
//	if (!hero_ || !cloud_)
//	{
//		return;
//	}
//
//	static bool update_data = true;
//	static auto animate = [&](uint64_t ms)
//	{
//		const auto show_duration = uint64_t(1000); //单位ms
//		const auto stay = uint64_t(2500); //单位ms
//		const auto hide_duration = uint64_t(500); //单位ms
//		const auto interval = uint64_t(1000);	   //单位ms
//
//		auto progress = ms % (show_duration + stay + hide_duration + interval);
//
//		if (progress <= show_duration)
//		{
//			update_data = false;
//			return progress / (float)show_duration;
//		}
//		else if (progress <= show_duration + stay)
//		{
//			update_data = false;
//			return 1.0f;
//		}
//		else if (progress <= (show_duration + stay + hide_duration))
//		{
//			update_data = false;
//			return 1.0f - (progress - show_duration - stay) / (float)hide_duration;
//		}
//		else
//		{
//			update_data = true;
//			return 0.0f;
//		}
//	};
//
//
//	if (update_data)
//	{
//		//auto vertices = std::vector<float>();
//		//auto clouds = vertices = DataManager::instance().cloud();
//		//auto t_q = DataManager::instance().heroCarQuaternion();
//		//auto q = quat(t_q.w(),t_q.x(),t_q.y(),t_q.z());
//////
//		//for(size_t i = 0;i < clouds.size(); i+=3)
//		//{
//		//	auto tmp = q * vec3(clouds[i],clouds[i+1],clouds[i+2]) + hero_->position;
//		//	vertices.push_back(tmp.x);
//		//	vertices.push_back(tmp.y);
//		//	vertices.push_back(tmp.z);
//		//}
//
//		auto vertices = DataManager::instance().cloud();
//
//		// auto vertices = std::vector<float>();
//
//		// for (int i = 0;i < 20000;i++)
//		// {
//		// 	std::srand(i);
//		// 	vertices.push_back(hero_->position.x + std::rand() % 10000 / 1000.0f);
//		// 	vertices.push_back(hero_->position.y + std::rand() % 10000 / 1000.0f);
//		// 	vertices.push_back(hero_->position.z + std::rand() % 10000 / 1000.0f);
//		// }
//
//
//		vertices.resize(std::min((int64_t)vertices.size(), cloudLimit * 3));
//
//		auto& geometry = cloud_->geometry;
//
//		auto& position = *geometry.GetAttribute("position");
//		position.count = vertices.size() / 3;
//		position.update_range.count = vertices.size();
//		position.array = Array(std::move(vertices));
//		position.NeedUpdate(true);
//	}
//
//	auto& material = static_cast<PointsMaterial&>(cloud_->material);
//	material.opacity = animate(current_ms_);
//}
