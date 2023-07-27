#include "subs_vehicle_info_from_adu.h"
#include "AduProxy.h"
#include "DataManager.h"
#include <cmath>
#include "GlParam.h"
//#include "SendToMessageTest.h"
#include "Util.h"
#include "MapConfig.h"

extern double x_min;
extern double y_min;
extern double z_min;

extern MapConfig g_config;

SubsVehicleInfoFromAdu::SubsVehicleInfoFromAdu() {
    qRegisterMetaType<std::vector<std::pair<LightDirection, LightColor>>>("std::vector<std::pair<LightDirection, LightColor>>");
    qRegisterMetaType<DrivingMode>("DrivingMode");
    QObject::connect(&notifier, SIGNAL(notify_current_position(const double, const double)), SingletonCAduProxy::getInstance(), SLOT(setCurrentPosition(const double, const double)), Qt::QueuedConnection);
    QObject::connect(&notifier, SIGNAL(notify_traffic_light(std::vector<std::pair<LightDirection, LightColor>>)), SingletonCAduProxy::getInstance(), SLOT(set_traffic_light(std::vector<std::pair<LightDirection, LightColor>>)), Qt::QueuedConnection);
    QObject::connect(&notifier, SIGNAL(notify_vehicle_drive_steer(const float)), SingletonCAduProxy::getInstance(), SLOT(setVehicleDriveSteer(const float)), Qt::QueuedConnection);
    QObject::connect(&notifier, SIGNAL(notify_vehicle_drive_throttle(const float)), SingletonCAduProxy::getInstance(), SLOT(setVehicleDriveThrottle(const float)), Qt::QueuedConnection);
    QObject::connect(&notifier, SIGNAL(notify_vehicle_drive_speed(const float)), SingletonCAduProxy::getInstance(), SLOT(setVehicleDriveSpeed(const float)), Qt::QueuedConnection);
    QObject::connect(&notifier, SIGNAL(notify_vehicle_drive_mode(const DrivingMode)), SingletonCAduProxy::getInstance(), SLOT(setVehicleDriveMode(const DrivingMode)), Qt::QueuedConnection);
}

void SubsVehicleInfoFromAdu::onRecv(Message_Ptr msg)
{
    static int32_t printCount = 0;
    ++printCount;
    int32_t printInter = 50;
    auto beginTime = Util::GetHighTickCount();
    hmi::BaseInfoDataType new_msg;
    new_msg.ParseFromArray(msg->data(), msg->size());

    if (g_config.m_debug)
    {
        static int32_t fpsCount = 0;
        static auto beginTime = Util::GetHighTickCount();
        ++fpsCount;
        int32_t time = Util::GetHighTickCountMilliRunTime(beginTime);
        double seconds = (time / 1000.0);
        double fps = fpsCount / seconds;
        if (printCount % printInter == 0)
        {
            printf("onRecv fps = %lf\n", fps);
        }
        if (seconds > 2)
        {
            fpsCount = 0;
            beginTime = Util::GetHighTickCount();
        }
    }

    // 主车位置
    if(new_msg.has_pose_info() && new_msg.pose_info().has_pose())
    {
        if (new_msg.pose_info().pose().has_position())
        {
            COWA::NavMsg::Point3D position = new_msg.pose_info().pose().position();
            double car_x = position.x();
            double car_y = position.y();
            double car_z = position.z();
            if (g_config.m_debug && (printCount % printInter == 0))
            {
                printf("car_x = %lf, car_y = %lf, car_z = %lf\n", car_x - x_min, car_y - y_min, car_z - z_min);
            }
            if(!std::isnan(car_x))
            {
             DataManager::instance().setHeroCarPos(car_x, car_y, car_z);
            Q_EMIT notifier.notify_current_position(car_x, car_y);

            uint64_t timestamp = new_msg.pose_info().timestamp();
            DataManager::instance().setTimestamp(timestamp);
        }
        }
        if (new_msg.pose_info().pose().has_rotation())
        {
            COWA::NavMsg::Quaternion rotation = new_msg.pose_info().pose().rotation();
            // 主车方向
            double qx = rotation.qx();
            double qy = rotation.qy();
            double qz = rotation.qz();
            double qw = rotation.qw();
            if(!std::isnan(qx))
            {
            double theta = std::atan2(2.0f * (qz * qw + qx * qy), -1.0f + 2.0f * (qw * qw + qx * qx));
            //printf("theta = %lf", theta);
            DataManager::instance().setHeroCarQuaternion({(float)qx, (float)qy, (float)qz, (float)qw});
            DataManager::instance().setHeroCarTheta(theta);
        }
    }
    }

    // 交通灯信息
    if(new_msg.has_trafficlight2_info()) {
        if (new_msg.trafficlight2_info().lights_size() > 0)
        {
            std::vector<std::pair<LightDirection, LightColor>> traffic_lights;
            for(const auto& light: new_msg.trafficlight2_info().lights()) {
                LightDirection direction = uint32_to_traffic_light_direction_enum(light.dir());
                LightColor color = uint32_to_traffic_light_state_enum(light.state());
                std::pair<LightDirection, LightColor> light_info = std::make_pair(direction, color);
                traffic_lights.push_back(light_info);
            }
            Q_EMIT notifier.notify_traffic_light(traffic_lights);
        }
    }

    // 预测轨迹
    if (new_msg.has_trajectory_info())
    {
        COWA::NavMsg::Trajectory trajectory = new_msg.trajectory_info();
        std::vector<Point3DGL> vecTrajectoryPoint;
        for (int pointIndex = 0; pointIndex < trajectory.points_size(); ++pointIndex)
        {
            COWA::NavMsg::TrajectoryPoint point = trajectory.points(pointIndex);
            vecTrajectoryPoint.push_back(Point3DGL(point.x(), point.y(), 0.0));
        }
        DataManager::instance().setTrajectoryPoints(vecTrajectoryPoint);
    }

    // 障碍物
    if (new_msg.has_obstacles_info())
    {
        COWA::NavMsg::Obstacles obstacles = new_msg.obstacles_info();
        int obstacles_size = obstacles.obstacles_size();
        if (obstacles_size != 0)
        {
            std::map<int32_t, ObstacleFrameInfo> obstacleMap;
            for (auto index = 0; index < obstacles_size; ++index)
            {
                COWA::NavMsg::Obstacle obstacle = obstacles.obstacles(index);
                int32_t id = obstacle.id();
                ObstacleFrameInfo& info = obstacleMap[id];
                info.m_type = obstacle.type();
                //printf("type = %d", info.m_type);
                if (obstacle.has_pose())
                {
                    COWA::NavMsg::Pose pose = obstacle.pose();
                    if (pose.has_position())
                    {
                        COWA::NavMsg::Point3D position = pose.position();
                        // 障碍物位置
                        double obstacle_x = position.x();
                        double obstacle_y = position.y();
                        double obstacle_z = position.z();
                        info.m_position.m_x = obstacle_x;
                        info.m_position.m_y = obstacle_y;
                        info.m_position.m_z = obstacle_z;
                        //printf("info.m_position.m_x = %lf", info.m_position.m_x);
                        //printf("info.m_position.m_y = %lf", info.m_position.m_y);
                    }
                }
                if (obstacle.has_theta())
                {
                    info.m_theta = obstacle.theta();
                    //printf("info.m_theta = %f", info.m_theta);
                }
                if (obstacle.has_length())
                {
                    info.m_length = obstacle.length();
                    //printf("info.m_length = %f", info.m_length);
                }
                if (obstacle.has_width())
                {
                    info.m_width = obstacle.width();
                    //printf("info.m_width = %f", info.m_width);
                }
                if (obstacle.has_height())
                {
                    info.m_height = obstacle.height();
                    //printf("info.m_height = %f", info.m_height);
                }
            }
            DataManager::instance().setObstacleMap(obstacleMap);
        }
    }

    // 方向盘转角
    if(new_msg.has_vehicle_drive_info()) {
        if(new_msg.vehicle_drive_info().has_steer()) {
            float steer = new_msg.vehicle_drive_info().steer();
            // std::cout << "steer:" << steer << std::endl;
            steer = steer / 4 * 1000.0f;
            Q_EMIT notifier.notify_vehicle_drive_steer(steer);
        }
    }

    // 刹车状态
    if(new_msg.has_vehicle_drive_info()) {
        if(new_msg.vehicle_drive_info().has_throttle()) {
            float throttle = new_msg.vehicle_drive_info().throttle();
            // std::cout << "throttle:" << throttle << std::endl;
            // 小于0为制动，大于0为加速
            if(throttle < 0) {
                throttle = -throttle;
                // 转化为百分比
                throttle = throttle * 100;
            } else {
                throttle = 0;
            }
            Q_EMIT notifier.notify_vehicle_drive_throttle(throttle);
        }
    }

    if(new_msg.has_vehicle_drive_info()) {
        // 驾驶速度
        if(new_msg.vehicle_drive_info().has_speed()) {
            float speed = new_msg.vehicle_drive_info().speed();
            // 速度转化m/s -> km/h
            speed = speed * 60 * 60 / 1000;
            Q_EMIT notifier.notify_vehicle_drive_speed(speed);
        }

        // 驾驶模式
        if(new_msg.vehicle_drive_info().has_driving_mode()) {
            DrivingMode driving_mode = new_msg.vehicle_drive_info().driving_mode();
            Q_EMIT notifier.notify_vehicle_drive_mode(driving_mode);
        }
    }

    //RCSend("%lf, %lf", x, y);

    // 点云
    // if (new_msg.has_point_cloud_collect())
    // {
    //     std::vector<float> vecCloud;
    //     ::utm_point_cloud::PointCloudCollect pointCloudCollect = new_msg.point_cloud_collect();
    //     int32_t pointCloudSize = pointCloudCollect.point_cloud_size();
    //     for (int32_t pointCloudIndex = 0; pointCloudIndex < pointCloudSize; ++pointCloudIndex)
    //     {
    //         ::utm_point_cloud::PointCloud pointCloud = pointCloudCollect.point_cloud(pointCloudIndex);
    //         int32_t pointSize = pointCloud.point_size();
    //         for (int32_t pointInd转化为ex = 0; pointIndex < pointSize; ++pointIndex)
    //         {
    //             ::utm_point_cloud::PointXYZ point = pointCloud.point(pointIndex);
    //             float x = point.x();
    //             float y = point.y();
    //             float z = 0.0f;
    //             if (point.has_z())
    //             {
    //                 z = point.z();
    //             }
    //             vecCloud.push_back(x);
    //             vecCloud.push_back(y);
    //             vecCloud.push_back(z);
    //             //RCSend("%lf, %lf", x, y);
    //         }
    //     }
    //     if (g_debug)
    //     {
    //         printf("cloud point size = %d\n", (int32_t)vecCloud.size());
    //         if (vecCloud.size() > 5 * 3)
    //         {
    //             printf("cloud[12] = %f, 13 = %f, 14 = %f\n", vecCloud[12], vecCloud[13], vecCloud[14]);
    //         }
    //         if (vecCloud.size() > 15 * 3)
    //         {
    //             printf("cloud[42] = %f, 43 = %f, 44 = %f\n", vecCloud[42], vecCloud[43], vecCloud[44]);
    //         }
    //     }
    //     DataManager::instance().setCloud(vecCloud);
    // }

    // 附近道路ID
    if (new_msg.has_lane_info())
    {
        // std::cout << "crossroad_id_size:" << new_msg.lane_info().crossroad_id_size() << std::endl;
        // std::cout << "crosswalk_id_size:" << new_msg.lane_info().crosswalk_id_size()<< std::endl;
        // std::cout << "road_id_size:" << new_msg.lane_info().road_id_size() << std::endl;
        // std::cout << "signal_id_size:" << new_msg.lane_info().signal_id_size() << std::endl;
        // std::cout << "lane_id_size:" << new_msg.lane_info().lane_id_size() << std::endl;

        ::hmi::LaneInfoType lane_info = new_msg.lane_info();
        std::set<std::string> vecLaneId;
        for (int index = 0; index < lane_info.lane_id_size(); ++index)
        {
            //RCSend("lane_id = %s", lane_info.lane_id(index).id().c_str());
            vecLaneId.insert(lane_info.lane_id(index).id());
        }
        std::set<std::string> vecRoadId;
        for (int index = 0; index < lane_info.road_id_size(); ++index)
        {
            //RCSend("road_id = %s", lane_info.road_id(index).id().c_str());
            vecRoadId.insert(lane_info.road_id(index).id());
        }
        std::set<std::string> vecCrossroadId;
        for (int index = 0; index < lane_info.crossroad_id_size(); ++index)
        {
            //RCSend("crossroad_id = %s", lane_info.crossroad_id(index).id().c_str());
            vecCrossroadId.insert(lane_info.crossroad_id(index).id());
        }
        std::set<std::string> vecCrosswalkId;
        for (int index = 0; index < lane_info.crosswalk_id_size(); ++index)
        {
            //RCSend("crosswalk_id = %s", lane_info.crosswalk_id(index).id().c_str());
            vecCrosswalkId.insert(lane_info.crosswalk_id(index).id());
        }
        std::set<std::string> vecSignalId;
        for (int index = 0; index < lane_info.signal_id_size(); ++index)
        {
            //RCSend("signal_id = %s", lane_info.signal_id(index).id().c_str());
            vecSignalId.insert(lane_info.signal_id(index).id());
        }
        DataManager::instance().setMap(vecLaneId, vecRoadId, vecCrossroadId, vecCrosswalkId, vecSignalId);
    }

    if (g_config.m_debug && (printCount % printInter == 0))
    {
        int32_t time = Util::GetHighTickCountMicroRunTime(beginTime);
        printf("onRecv time = %d\n", time);
    }
}