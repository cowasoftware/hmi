#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <QDebug>

#include <fmt/core.h>
using namespace fmt;

#include "Cini.h"
#include "ini_reader.h"
#include "object_renderer.h"

extern double z_min;
extern glm::highp_mat4 g_view;
extern glm::highp_mat4 g_perspective;

void ObjectRendererConfig::Load(std::string const &path)
{
    Cini ini(path);

    IniReader reader;
    std::string key;

    key = "high";
    reader.Read(key, ini.readIni(key), high);

    key = "trajectoryLimit";
    reader.Read(key, ini.readIni(key), trajectory_limit);

    key = "trajectoryWidth";
    reader.Read(key, ini.readIni(key), trajectory_width);

    key = "cloudLimit";
    reader.Read(key, ini.readIni(key), cloud_limit);

    key = "cloudColor";
    reader.Read(key, ini.readIni(key), cloud_color);

    key = "cameraPosition";
    reader.Read(key, ini.readIni(key), camera_position);

    key = "cameraTarget";
    reader.Read(key, ini.readIni(key), camera_target);

    key = "spotLightTarget";
    reader.Read(key, ini.readIni(key), spot_light_target);

    key = "obstacleLimits";
    reader.Read(key, ini.readIni(key), obstacle_limits);

    key = "vehicleType";
    reader.Read(key, ini.readIni(key), vehicle_type);

    key = "vehicleModel";
    reader.Read(key, ini.readIni(key), vehicle_model);
}

ObjectRenderer::ObjectRenderer(cppgl::CppGL &gl)
    : gl_(gl)
{
}

ObjectRenderer::~ObjectRenderer()
{
}

void ObjectRenderer::Init()
{
    ObjectManager::ins().SetConfig(config_);
    ObjectManager::ins().Init(gl_);
}

void ObjectRenderer::Sync()
{
    if (ObjectManager::ins().IsLoaded() && source_)
    {
        source_(data_);
        HandleHero();
        HandleWave();
        HandleTrajectory();
        HandleObstacles();
        HandleCamera();
        HandleLights();
        HandleCloud();
    }
}

void ObjectRenderer::Render()
{
    if (ObjectManager::ins().IsLoaded())
    {
        ObjectManager::ins().Renderer()->Render(*ObjectManager::ins().Scene(), *ObjectManager::ins().Camera());
        if (ObjectManager::ins().skybox)
        {
            ObjectManager::ins().skybox->Render(g_view, g_perspective);
        }
    }
}

void ObjectRenderer::ResetCamera(size_t width, size_t height, float angle)
{
    width_ = width;
    height_ = height;
    fov_ = angle;
}

Mesh *mesh{nullptr};

void ObjectRenderer::HandleHero()
{
    // 更新主车位置和角度
    auto hero = ObjectManager::ins().Hero();
    hero->position = data_.hero_world_matrix.translation;
    hero->position.z = 1.0f;
    hero->quaternion = data_.hero_world_matrix.quaternion;
    hero->UpdateWorldMatrix();
}

void ObjectRenderer::HandleObstacles()
{
    auto obstacles = ObjectManager::ins().Obstacles();
    auto scene = ObjectManager::ins().Scene();
    auto &memory = ObjectManager::ins().Memory();

    // for (auto &obstacle_parts : obstacles)
    // {
    //     auto iter = data_.obstacle_world_matrices.find(obstacle_parts.first);

    //     if (iter != data_.obstacle_world_matrices.end() && obstacle_parts.second.limit < iter->second.size())
    //     {
    //         auto new_obstacle = ObjectManager::CopyInstancedMesh(obstacle_parts.second.parts, iter->second.size());

    //         for (auto part : new_obstacle)
    //         {
    //             scene->Add(*part);
    //             memory.Add(*part);
    //             part->draw_count = 0;
    //         }

    //         for (auto part : obstacle_parts.second.parts)
    //         {
    //             scene->Remove(*part);
    //             memory.Remove(*part);
    //         }

    //         print("obstacle[{}] limit: {} -> {}\n", iter->first, obstacle_parts.second.limit, iter->second.size());
    //         obstacle_parts.second.parts = std::move(new_obstacle);
    //         obstacle_parts.second.limit = iter->second.size();
    //     }
    // }
    auto m = mat4(1.0f);
    auto s = vec3(0.0f);
    auto t = vec3(0.0f);
    auto i = size_t(0);

    for (auto &obstacle_parts : obstacles)
    {

        auto iter = data_.obstacle_world_matrices.find(obstacle_parts.first);

        if (iter != data_.obstacle_world_matrices.end())
        {
            i = 0;
            iter->second.resize(obstacle_parts.second.limit);
            for (auto &world : iter->second)
            {
                if (obstacle_parts.second.size.x == 0)
                {
                    s = vec3(1.0f);
                }
                else
                {
                    s = world.scale / obstacle_parts.second.size;
                }

                t = vec3(world.translation.x, world.translation.y, 1.0f);
                m = glm::translate(mat4(1.0f), t) * glm::mat4(world.quaternion) * glm::scale(mat4(1.0f), s);

                for (auto &part : obstacle_parts.second.parts)
                {
                    part->UpdateMatrixAt(i++, m);
                    part->draw_count = iter->second.size();
                    part->instance_matrices.NeedUpdate(true);
                }
            }
        }
        else
        {
            for (auto &part : obstacle_parts.second.parts)
            {
                part->draw_count = 0;
            }
        }
    }
}

void ObjectRenderer::HandleWave()
{
    static auto animate = [](uint64_t ms)
    {
        const auto speed = 5.0f;              // 单位m/s;
        const auto duration = uint64_t(3500); // 单位ms
        const auto interval = uint64_t(1500); // 单位ms

        auto progress = ms % (duration + interval);

        if (progress < duration)
        {
            return speed * progress / 1000.0f;
        }
        else
        {
            return 0.0f;
        }
    };

    auto wave = ObjectManager::ins().Wave();
    auto hero = ObjectManager::ins().Hero();
    wave->TranslateTo(hero->WorldPosition() + vec3(0.0f, 0.0f, 0.01));
    wave->ScaleTo(animate(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
    wave->UpdateWorldMatrix();
}

void ObjectRenderer::HandleTrajectory()
{
    auto make_point = [](vec3 const &p1, vec3 const &p2, float width)
    {
        auto offset = glm::normalize(glm::cross(vec3(0.0f, 0.0, 1.0f), p2 - p1));
        return std::make_pair(p1 + offset * 0.5f * width, p1 - offset * 0.5f * width);
    };

    auto hero = ObjectManager::ins().Hero();
    auto trajectory = ObjectManager::ins().Trajectory();

    auto trajectory_points = std::vector<vec3>();
    auto max_count = std::min(data_.trajectory.size(), config_.trajectory_limit);

    auto direction = hero->quaternion * vec3(1.0f, 0.0f, 0.0f);
    auto v = vec3(0.0f);

    if (max_count > 0)
    {
        trajectory_points.push_back(data_.trajectory.front());
    }

    for (size_t i = 1; i < max_count; i++)
    {
        if (glm::distance(data_.trajectory[i], trajectory_points.back()) > 0.1f)
        {
            trajectory_points.emplace_back(data_.trajectory[i]);
        }
    }

    max_count = trajectory_points.size();

    if (max_count < 3)
    {
        return;
    }

    std::vector<float> trajectory_positions;
    std::vector<uint32_t> trajectory_indices;
    std::vector<float> trajectory_colors;

    auto colors = ObjectManager::CalcluateColor(max_count, 0x087ff290);

    for (size_t i = 1; i < max_count; i++)
    {
        auto &p1 = trajectory_points[i - 1];
        auto &p2 = trajectory_points[i];

        auto p12 = make_point(p1, p2, config_.trajectory_width);
        trajectory_positions.push_back(p12.first.x);
        trajectory_positions.push_back(p12.first.y);
        trajectory_positions.push_back(p12.first.z);
        trajectory_positions.push_back(p12.second.x);
        trajectory_positions.push_back(p12.second.y);
        trajectory_positions.push_back(p12.second.z);

        trajectory_colors.push_back(colors[i].r);
        trajectory_colors.push_back(colors[i].g);
        trajectory_colors.push_back(colors[i].b);
        trajectory_colors.push_back(colors[i].a);
        trajectory_colors.push_back(colors[i].r);
        trajectory_colors.push_back(colors[i].g);
        trajectory_colors.push_back(colors[i].b);
        trajectory_colors.push_back(colors[i].a);
    }

    for (size_t i = 0; i < max_count - 2; i++)
    {
        trajectory_indices.push_back(2 * i);
        trajectory_indices.push_back(2 * i + 1);
        trajectory_indices.push_back(2 * i + 2);
        trajectory_indices.push_back(2 * i + 1);
        trajectory_indices.push_back(2 * i + 2);
        trajectory_indices.push_back(2 * i + 3);
    }

    auto &trajetory = static_cast<Mesh &>(*trajectory);
    auto &geometry = trajetory.geometry;

    auto &position = *geometry.GetAttribute("position");
    position.array = trajectory_positions;
    position.count = trajectory_positions.size() / 3;
    position.update_range.count = trajectory_positions.size();
    position.NeedUpdate(true);

    auto &color = *geometry.GetAttribute("color");
    color.array = trajectory_colors;
    color.count = trajectory_colors.size() / 4;
    color.update_range.count = trajectory_colors.size();
    color.NeedUpdate(true);

    auto &index = *geometry.GetIndex();
    index.array = trajectory_indices;
    index.count = trajectory_indices.size();
    index.update_range.count = trajectory_indices.size();
    index.NeedUpdate(true);
}

void ObjectRenderer::HandleCamera()
{
    auto hero = ObjectManager::ins().Hero();
    auto camera = ObjectManager::ins().Camera();

    auto target_position = hero->position;
    auto qua = hero->quaternion;
    camera->aspect = (float)width_ / (float)height_;
    camera->TranslateTo(qua * config_.camera_position + target_position);
    camera->LookAt(qua * config_.camera_target + target_position);
    camera->UpdateWorldMatrix();
}

void ObjectRenderer::HandleLights()
{
    auto spot_light = ObjectManager::ins().SpotLight();
    auto hero = ObjectManager::ins().Hero();
    auto camera = ObjectManager::ins().Camera();

    spot_light->TranslateTo(camera->position);
    spot_light->target = hero->position + hero->quaternion * config_.spot_light_target;
    spot_light->UpdateWorldMatrix();
}

void ObjectRenderer::HandleCloud()
{
    auto animate = [&](uint64_t ms, float &opacity)
    {
        const auto show_duration = uint64_t(1000); // 单位ms
        const auto stay = uint64_t(2500);          // 单位ms
        const auto hide_duration = uint64_t(500);  // 单位ms
        const auto interval = uint64_t(1000);      // 单位ms

        auto progress = ms % (show_duration + stay + hide_duration + interval);

        if (progress <= show_duration)
        {
            opacity = progress / (float)show_duration;
            return false;
        }
        else if (progress <= show_duration + stay)
        {
            opacity = 1.0f;
            return false;
        }
        else if (progress <= (show_duration + stay + hide_duration))
        {
            opacity = 1.0f - (progress - show_duration - stay) / (float)hide_duration;
            return false;
        }
        else
        {
            opacity = 0.0f;
            return true;
        }
    };

    auto hero = ObjectManager::ins().Hero();
    auto cloud = ObjectManager::ins().Cloud();

    auto &material = static_cast<PointsMaterial &>(cloud->material);

    if (animate(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(), material.opacity))
    {
        cloud->TranslateTo(0, 0, -1 * data_.hero_world_matrix.translation.z + 1);
        auto vertices = data_.cloud;
        vertices.resize(std::min(config_.cloud_limit * 3, vertices.size()));
        // print("cloud size: {}\n", vertices.size());
        //  auto vertices = std::vector<float>();

        // for (int i = 0;i < 20000;i++)
        // {
        //     std::srand(i);
        //     vertices.push_back(data_.hero_world_matrix.translation.x + std::rand() % 10000 / 1000.0f);
        //     vertices.push_back(data_.hero_world_matrix.translation.y + std::rand() % 10000 / 1000.0f);
        //     vertices.push_back(data_.hero_world_matrix.translation.z + std::rand() % 10000 / 1000.0f);
        // }
        auto &geometry = cloud->geometry;
        // print("hero.position: {},{},{}; cloud:{},{},{}\n",data_.hero_world_matrix.translation.x,data_.hero_world_matrix.translation.y,data_.hero_world_matrix.translation.z,vertices[0],vertices[1],vertices[2]);
        //  print("z_min: {}\n",z_min);

        auto &position = *geometry.GetAttribute("position");
        position.count = vertices.size() / 3;
        position.update_range.count = vertices.size();
        position.array = Array(std::move(vertices));
        position.NeedUpdate(true);
    }
}
