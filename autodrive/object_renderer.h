#pragma once

#include <cppgl.h>
#include <three.h>
#include <thread>

#include "object_manager.h"


class ObjectRendererData
{
public:
    class WorldMatrixInfo
    {
    public:
        vec3 translation;
        quat quaternion;
        vec3 scale;
    };

    WorldMatrixInfo hero_world_matrix;
    std::map<uint32_t, std::vector<WorldMatrixInfo>> obstacle_world_matrices;
    std::vector<float> cloud;
    std::vector<vec3> trajectory;
};

class ObjectRenderer
{
private:


public:
    ObjectRenderer(cppgl::CppGL &gl);
    virtual ~ObjectRenderer();

public:
    void Init();
    void Sync();
    void Render();

public:
    void SetDataSource(std::function<void(ObjectRendererData &)> source) { source_ = source; }
    void SetConfig(ObjectRendererConfig const &config) { config_ = config; }
    void ResetCamera(size_t width, size_t height,float angle);

    void HandleHero();
    void HandleObstacles();
    void HandleWave();
    void HandleTrajectory();
    void HandleCamera();
    void HandleLights();
    void HandleCloud();
    void HandleSkybox();

private:
    size_t width_{0};
    size_t height_{0};
    float fov_{0.0f};
    cppgl::CppGL &gl_;
    ObjectRendererConfig config_;
    ObjectRendererData data_;
    std::function<void(ObjectRendererData &)> source_;
};