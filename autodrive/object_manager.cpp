#include <QCoreApplication>

#include <thread>

#include "object_manager.h"
#include "MapConfig.h"

extern int32_t g_windowWidth;
extern int32_t g_windowHeight;
extern int32_t g_perspectiveAngle;
extern MapConfig g_config;

ObjectManager &ObjectManager::ins()
{
    static ObjectManager instance;

    return instance;
}

std::vector<vec4> ObjectManager::CalcluateColor(size_t len, uint32_t rgba)
{
    auto fun = [](float x)
    {
        return 1 - 1 / (0.01 * x * x + 0.0001 * x + 1);
    };

    float opacity = 1.0f;
    float r = ((rgba >> 24) & 0xff) / 256.0f;
    float g = ((rgba >> 16) & 0xff) / 256.0f;
    float b = ((rgba >> 8) & 0xff) / 256.0f;
    float a = (rgba & 0xff) / 256.0f;

    std::vector<vec4> colors(len, vec4(r, g, b, a));

    for (size_t i = len; i > 0; i--)
    {
        colors[len - i].a = a * fun((float)i);
    }

    return colors;
}

std::vector<InstancedMesh *> ObjectManager::LoadInstancedMesh(std::string const &file, int32_t count)
{
    ObjectLoader loader;
    std::vector<InstancedMesh *> meshes;
    std::vector<Object *> wait_free_objects;

    auto object = loader.Load(file);

    if (!object)
    {
        return meshes;
    }

    auto call = [&](Object &obj)
    {
        if (obj.IsModel())
        {
            auto &model = static_cast<Model &>(obj);
            auto &mesh = *new InstancedMesh(model.geometry, model.material, count);
            meshes.push_back(&mesh);
        }
        wait_free_objects.push_back(&obj);
    };

    object->TraverseVisible(call);

    for (auto obj : wait_free_objects)
    {
        delete obj;
    }

    return meshes;
}

std::vector<InstancedMesh *> ObjectManager::CopyInstancedMesh(std::vector<InstancedMesh *> const &origin, int32_t count)
{
    std::vector<InstancedMesh *> meshes(origin.size());

    size_t index = 0;

    for (auto mesh : origin)
    {
        meshes[index++] = new InstancedMesh(mesh->geometry, mesh->material, count);
    }

    return meshes;
}

void ObjectManager::Init(cppgl::CppGL &gl)
{
    auto runable = [&]()
    {
        camera = new three::PerspectiveCamera();
        scene = new three::Scene();
        renderer = new three::Renderer(gl);
        InitCamera(glm::radians(float(g_perspectiveAngle)), g_windowWidth / (float)g_windowHeight);
        InitLights();
        InitModel();
        InitWave();
        InitTrajectory();
        InitCloud();
        InitSkybox(gl);
        finished_ = true;
    };

    if (!initalized_)
    {
        initalized_ = true;
        runable();
    }
}

void ObjectManager::Destroy()
{
    finished_ = false;
    initalized_ = false;
    memory_.Free();
    delete skybox;
    delete renderer;
    delete scene;
    delete camera;
}

bool ObjectManager::IsInitalized()
{
    return initalized_;
}

bool ObjectManager::IsLoaded()
{
    return finished_;
}

void ObjectManager::InitSkybox(cppgl::CppGL& gl)
{
    if (g_config.m_showSky)
    {
        skybox = new Skybox(gl);

        std::vector<std::string> files{
            config_.app_dir + "/resource/3d/texture/skybox/right.png",
            config_.app_dir + "/resource/3d/texture/skybox/left.png",
            config_.app_dir + "/resource/3d/texture/skybox/top.png",
            config_.app_dir + "/resource/3d/texture/skybox/bottom.png",
            config_.app_dir + "/resource/3d/texture/skybox/front.png",
            config_.app_dir + "/resource/3d/texture/skybox/back.png",
        };

        skybox->Init(files);
    }
}

void ObjectManager::InitCamera(float fov, float aspect)
{
    camera->aspect = aspect;
    camera->zfar = 500;
    camera->znear = 0.01;
    camera->fov = fov;
    camera->up = vec3(0, 0, 1);
    camera->TranslateTo(vec3(1.0f, 1.0f, 1.0f));
    camera->LookAt(vec3(0.0f));
    camera->UpdateWorldMatrix();
    camera->UpdateProjectionMatrix();
}

void ObjectManager::InitLights()
{
    auto ambient_light = new three::AmbientLight(0xffffff, 1);
    scene->Add(*ambient_light);
    memory_.Add(*ambient_light);

    spot_light = new three::SpotLight(0xffffff, 2, 500, glm::radians(40.0f), 1);
    scene->Add(*spot_light);
    memory_.Add(*spot_light);
}

void ObjectManager::InitModel()
{
    ObjectLoader loader;

    auto exec_dir = QCoreApplication::applicationDirPath().toStdString();
    
    hero = loader.Load(exec_dir + "/" + config_.vehicle_model);

    if(hero)
    {
        scene->Add(*hero);
        memory_.Add(*hero);
    }
    else{
        throw std::runtime_error("herocar model load failed: " + exec_dir + "/" + config_.vehicle_model);
    }

    std::string dir = exec_dir + std::string("/resource/3d/obj/") + (config_.high ? "high/" : "");

    // {type: [limit, size, file]}
    std::map<ObstacleRenderType, std::tuple<size_t, vec3, std::string>> obstacle_file_map{
        {ObstacleRenderType::CAR, {100, vec3(3.8f, 1.7f, 1.3f)* 1.2f, dir + "obstacle/trolley/trolley.obj"}},                     // 小轿车
        {ObstacleRenderType::BUS, {100, vec3(6.2f, 2.2f, 2.0f)* 1.2f, dir + "obstacle/bus/bus.obj"}},                             // 大巴车
        {ObstacleRenderType::TRUCK, {100, vec3(5.2f, 2.0f, 2.0f), dir + "obstacle/truck/truck.obj"}},                       // 卡车
        {ObstacleRenderType::SPECIAL, {100, vec3(5.3f, 2.0f, 2.3f), dir + "obstacle/special-vehicle/special-vehicle.obj"}}, // 特殊车
        {ObstacleRenderType::CYCLIST, {100, vec3(0.0f), dir + "obstacle/bike/bike.obj"}},                                   // 自行车
        {ObstacleRenderType::TRICYCLE, {100, vec3(0.0f), dir + "obstacle/tricycle/tricycle.obj"}},                          // 三轮车
        {ObstacleRenderType::MOTORCYCLIST, {100, vec3(0.0f), dir + "obstacle/motorcycle/motorcycle.obj"}},                  // 摩托车
        {ObstacleRenderType::PEDESTRAIN, {100, vec3(), dir + "obstacle/people/people2/people2.obj"}},                       // 行人
        {ObstacleRenderType::ROADBLOCK, {100, vec3(0.47f, 0.47f, 0.47f), dir + "obstacle/roadblock/roadblock.obj"}},        // 路障
        {ObstacleRenderType::TREETRUNK, {100, vec3(1.0f, 1.0f, 3.5f), dir + "obstacle/trees/trees.obj"}},                   // 树
        {ObstacleRenderType::POLE, {100, vec3(0.3f, 0.3f, 0.75f), dir + "obstacle/light-pole/light-pole.obj"}},             // 电线杆
        {ObstacleRenderType::PILES, {100, vec3(0.0f), dir + "obstacle/stone-pier/stone-pier.obj"}},          // 路桩
        {ObstacleRenderType::BLOCK, {100, vec3(0.4f, 0.4f, 0.5f), dir + "obstacle/road-stakes/road-stakes.obj"}},           // 石墩
    };

    for(size_t i = 0; i < config_.obstacle_limits.size();i+=2)
    {
        auto iter = obstacle_file_map.find((ObstacleRenderType)config_.obstacle_limits[i]);
        if(iter != obstacle_file_map.end())
        {
            std::get<0>(iter->second) = config_.obstacle_limits[i+1];
        }
    }

    for (auto &file_pair : obstacle_file_map)
    {
        auto &obstacle_type = file_pair.first;
        auto &obstacle_limit = std::get<0>(file_pair.second);
        auto &obstacle_size = std::get<1>(file_pair.second);
        auto &obstacle_file = std::get<2>(file_pair.second);

        auto obstacle = LoadInstancedMesh(obstacle_file, obstacle_limit);

        if (obstacle.empty())
        {
            printf("load obstacle failed: %s\n", obstacle_file.c_str());
            continue;
        }
        else
        {
            printf("load obstacle success: %s\n", obstacle_file.c_str());
        }

        for (auto part : obstacle)
        {
            scene->Add(*part);
            memory_.Add(*part);
            part->draw_count = 0;
        }

        obstacles.emplace((uint32_t)obstacle_type, ObstacleRendererData{obstacle_limit, obstacle_size, std::move(obstacle)});
    }
}

void ObjectManager::InitWave()
{
    // 雷达探测波
    auto &geometry = *new CircleGeometry(1, 36);
    auto &material = *new MeshBasicMaterial(0x707070, true, 0.3);
    wave = new Mesh(geometry, material);
    scene->Add(*wave);
    memory_.Add(*wave);
}

void ObjectManager::InitTrajectory()
{
    // 轨迹线
    uint32_t max_len = 2000;
    auto &trajectory_geometry = *new Geometry();

    auto &position_attr = *new GeometryAttribute(Array(std::vector<float>(3 * max_len, 0)), 3, false, Usage::DYNAMIC_DRAW);
    position_attr.update_range.count = 0;
    position_attr.count = 0;
    trajectory_geometry.SetAttribute("position", position_attr);

    auto &color_attr = *new GeometryAttribute(Array(std::vector<float>(4 * max_len)), 4, false, Usage::DYNAMIC_DRAW);
    trajectory_geometry.SetAttribute("color", color_attr);

    auto &index = *new GeometryAttribute(Array(std::vector<uint32_t>(6 * max_len)), 1, false, Usage::DYNAMIC_DRAW);
    trajectory_geometry.SetIndex(index);

    auto &trajectory_material = *new MeshBasicMaterial(0xffffff, true);
    trajectory_material.vertex_colors = true;
    trajectory = new Mesh(trajectory_geometry, trajectory_material);
    scene->Add(*trajectory);
    memory_.Add(*trajectory);
}

void ObjectManager::InitCloud()
{
    auto &geometry = *new Geometry();

    auto &position = *new GeometryAttribute(Array(std::vector<float>(config_.cloud_limit * 3)), 3, false, Usage::DYNAMIC_DRAW);
    position.update_range.count = 0;
    position.count = 0;
    geometry.SetAttribute("position", position);

    auto &material = *new PointsMaterial;
    material.color = config_.cloud_color;
    material.transparent = true;
    cloud = new Points(geometry, material);
    scene->Add(*cloud);
    memory_.Add(*cloud);
}