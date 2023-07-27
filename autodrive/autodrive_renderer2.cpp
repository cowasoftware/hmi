#include "autodrive_renderer2.h"
#include "qtgles3.h"
#include <QCoreApplication>
#include "DataManager.h"
#include <QImage>
#include <QDebug>
#include <QOpenGLFramebufferObject>
#include <QCoreApplication>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <tuple>

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
#include "OpenGLManager.h"
#include <fmt/core.h>
#include "HdmapData.h"

#include "Cini.h"
#include "CTaskThreadManagerAPI.h"
#include "SaveFrameTask.h"
#include "Util.h"
#include <glm/gtx/string_cast.hpp>
#include <fmt/core.h>
#include "map_renderer.h"
#include "MapConfig.h"
#include "object_manager.h"

using namespace fmt;
using namespace std;

extern double x_min;
extern double y_min;
extern double z_min;
extern double g_trajectoryHeight;
extern int32_t g_windowWidth;
extern int32_t g_windowHeight;
extern int32_t g_perspectiveAngle;

extern MapConfig g_config;

AutodriveRenderer2::AutodriveRenderer2(cppgl::CppGL &gl, QSizeF const &size)
    : QObject(), gl_(gl), size_(size)
{
    map_renderer_ = new MapRenderer(&gl);
    object_renderer_ = new ObjectRenderer(gl);

    if (gl_.GetGLSLVersion().type == "core")
    {
        ctx_ = new MSAAOffscreenContext(gl_, uint32_t(size_.width()), uint32_t(size_.height()), 4);
    }
    else
    {
        ctx_ = new OffscreenContext(gl_, uint32_t(size_.width()), uint32_t(size_.height()));
    }
}

AutodriveRenderer2::~AutodriveRenderer2()
{
    delete map_renderer_;
    delete object_renderer_;
    delete ctx_;
}

void AutodriveRenderer2::ResetSize(QRectF rect)
{
    size_ = rect.size();
    g_windowHeight = int(size_.width());
    g_windowHeight = int(size_.height());
    object_renderer_->ResetCamera(g_windowWidth, g_windowHeight, glm::radians((float)g_perspectiveAngle));
    
    if (ctx_)
    {
        delete ctx_;
        ctx_ = nullptr;
    }

    if (gl_.GetGLSLVersion().type == "core")
    {
        ctx_ = new MSAAOffscreenContext(gl_, uint32_t(size_.width()), uint32_t(size_.height()), 4);
    }
    else
    {
        ctx_ = new OffscreenContext(gl_, uint32_t(size_.width()), uint32_t(size_.height()));
    }
}

void AutodriveRenderer2::Init()
{
    map_renderer_->Init();

    ObjectRendererConfig object_config;
    object_config.Load(QCoreApplication::applicationDirPath().toStdString() + "/autodrive.ini");
    object_config.app_dir = QCoreApplication::applicationDirPath().toStdString();
    object_renderer_->SetConfig(object_config);
    object_renderer_->ResetCamera(g_windowWidth, g_windowHeight, glm::radians((float)g_perspectiveAngle));

    auto object_data_source = [](ObjectRendererData &data)
    {
        // hero
        auto hero_position = DataManager::instance().heroCarPos();
        data.hero_world_matrix.translation = vec3(std::get<0>(hero_position) - x_min, std::get<1>(hero_position) - y_min, std::get<2>(hero_position) - z_min);
        data.hero_world_matrix.quaternion = glm::quat_cast(glm::rotate(mat4(1.0f), (float)DataManager::instance().heroCarTheta(), vec3(0, 0, 1)));
        data.hero_world_matrix.scale = vec3(1.0f);
        // obstacles
        auto obstalces = DataManager::instance().obstacleMap();

        data.obstacle_world_matrices.clear();

        for (auto &obstale_pair : obstalces)
        {
            ObjectRendererData::WorldMatrixInfo m;
            m.translation = vec3(obstale_pair.second.m_position.m_x - x_min, obstale_pair.second.m_position.m_y - y_min, obstale_pair.second.m_position.m_z - z_min);
            m.quaternion = glm::quat_cast(glm::rotate(mat4(1.0f), (float)obstale_pair.second.m_theta, vec3(0, 0, 1)));
            m.scale = vec3(obstale_pair.second.m_length, obstale_pair.second.m_width, obstale_pair.second.m_height);
            data.obstacle_world_matrices[obstale_pair.second.m_type].push_back(m);
        }

        // trajectory
        auto trajectory = DataManager::instance().trajectoryPoints();
        data.trajectory.resize(trajectory.size());
        std::transform(trajectory.begin(), trajectory.end(), data.trajectory.begin(), [&](Point3DGL &p)
                       { return vec3(p.m_x - x_min, p.m_y - y_min, 1.0f); });

        // cloud
        data.cloud = std::move(DataManager::instance().cloud());
    };

    object_renderer_->SetDataSource(object_data_source);
    object_renderer_->Init();
}

void AutodriveRenderer2::Sync()
{
    map_renderer_->Sync();
    object_renderer_->Sync();
}

uint32_t AutodriveRenderer2::Render()
{
    auto call = [this](auto &gl)
    {
        gl_.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        gl_.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        map_renderer_->Render();
        object_renderer_->Render();
        gl_.Flush();
    };

    static int count = 0;
    static auto start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    if (g_config.m_writeFps && count++ % 60 == 0)
    {
        auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        qDebug() << "fps: " << 1000.0f / ((end - start) / 60.0f);
        start = end;
    }

    return ctx_->With(call);
}