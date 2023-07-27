#pragma once

#include <three.h>
#include "skybox.h"

enum class ObstacleRenderType
{
    CAR = 3,           // 小轿车
    BUS = 4,           // 大巴车
    TRUCK = 5,         // 卡车
    SPECIAL = 6,       // 特殊车
    CYCLIST = 10,      // 自行车
    TRICYCLE = 11,     // 三轮车
    MOTORCYCLIST = 12, // 摩托车
    PEDESTRAIN = 20,   // 行人
    ROADBLOCK = 30,    // 路障
    TREETRUNK = 31,    // 树
    POLE = 32,         // 电线杆
    PILES = 33,        // 路桩
    BLOCK = 36,        // 石墩
};

class ObjectRendererConfig
{
public:
    void Load(std::string const &path);

public:
    bool high{false};
    std::string app_dir;
    vec3 camera_position{0.0};
    vec3 camera_target{0.0};
    size_t cloud_limit{0};
    vec3 cloud_color{0.0};
    size_t trajectory_limit{0};
    float trajectory_width{0.0};
    vec3 spot_light_target{0.0};
    std::vector<int> obstacle_limits;
    int vehicle_type;
    std::string vehicle_model;
};

class ObstacleRendererData
{
public:
    size_t limit = 0;
    vec3 size = vec3(1.0f);
    std::vector<three::InstancedMesh *> parts;
};

class ObjectManager
{
protected:
    ObjectManager() = default;

public:
    void SetConfig(ObjectRendererConfig const &config) { config_ = config; }

public:
    static ObjectManager &ins();
    void Init(cppgl::CppGL &gl);
    void Destroy();
    bool IsInitalized();
    bool IsLoaded();

    static std::vector<vec4> CalcluateColor(size_t len, uint32_t rgba);
    static std::vector<InstancedMesh *> LoadInstancedMesh(std::string const &file, int32_t count);
    static std::vector<InstancedMesh *> CopyInstancedMesh(std::vector<InstancedMesh *> const &origin, int32_t count);

public:
    three::PerspectiveCamera *Camera() { return camera; }
    three::Scene *Scene() { return scene; };
    three::Renderer *Renderer() { return renderer; };
    three::SpotLight *SpotLight() { return spot_light; };
    three::Object *Hero() { return hero; };
    std::map<uint32_t, ObstacleRendererData> &Obstacles() { return obstacles; };
    three::Mesh *Wave() { return wave; };
    three::Mesh *Trajectory() { return trajectory; };
    three::Points *Cloud() { return cloud; };
    MemoryUtil& Memory() {return memory_;}
    Skybox* skybox{nullptr};

private:
    void InitCamera(float fov, float aspect);
    void InitCamera();
    void InitScene();
    void InitLights();
    void InitModel();
    void InitWave();
    void InitTrajectory();
    void InitCloud();
    void InitSkybox(cppgl::CppGL& gl);

private:
    three::PerspectiveCamera *camera{nullptr};
    three::Scene *scene{nullptr};
    three::Renderer *renderer{nullptr};
    three::SpotLight *spot_light{nullptr};
    three::Object *hero{nullptr};
    std::map<uint32_t, ObstacleRendererData> obstacles;
    three::Mesh *wave{nullptr};
    three::Mesh *trajectory{nullptr};
    three::Points *cloud{nullptr};
    bool initalized_{false};
    bool finished_{false};
    MemoryUtil memory_;
    ObjectRendererConfig config_;

};