#include "AduProxy.h"
#include "context.h"
#include <QVariant>
#include "TrafficLightType.h"
#include <cmath>
#include "ConfigConstants.h"
#include <chrono>
#include "MapConfig.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

extern Context context;
extern MapConfig g_config;

CAduProxy::CAduProxy(QObject *parent)
    : QObject{parent}
{
     qRegisterMetaType<QVariantList*>("QVariantList*");
     qRegisterMetaType<QList<QList<double>>*>("QList<QList<double>>*");
     qRegisterMetaType<uint32_t>("uint32_t");
     m_handleCurvePointThread = std::thread(&CAduProxy::threadFunc, this);
    //  m_handleCurvePointThread.detach();
    //  m_handleDrivingModelThread = std::thread(&CAduProxy::drivingModelThreadFunc, this);
    //  m_handleDrivingModelThread.detach();
    m_lastPt.setX(0.0f);
    m_lastPt.setY(0.0f);
}

CAduProxy::~CAduProxy() {
    destroy();
}

void CAduProxy::destroy() {
    if(m_handleCurvePointThread.joinable()) {
        m_handleCurvePointThread.join();
    }
    // if(m_handleDrivingModelThread.joinable()) {
    //     m_handleDrivingModelThread.join();
    // }
    std::cout << "adu proxy thread exit !!!" << std::endl;
}

void CAduProxy::threadFunc() {
    while(true) {
        std::vector<Wgs8451Position> points_vect_copy;
        {
            std::unique_lock<std::mutex> guard(m_listMtx);
            while(m_target_points_vect.empty()) {
                m_condr.wait(guard);
            }
            if(!m_target_points_vect.empty()) {
                m_target_points_vect.swap(points_vect_copy);
            }
        }
        std::cout << "send curve points's size: " << points_vect_copy.size() << std::endl;
        if(!points_vect_copy.empty())
        {
            context.send_curve_points_request(points_vect_copy);
        }
    }
}

void CAduProxy::drivingModelThreadFunc() {
    while(true) {
        std::cout << "m_driving_mode: " << m_driving_mode << std::endl;
        {
            while(m_driving_mode == DrivingModeEnum::DrivingMode::DEFAULT) {
                std::unique_lock<std::mutex> guard(m_modeMtx);
                m_modelCondr.wait(guard);
            }
            if(m_driving_mode == DrivingModeEnum::DrivingMode::ATUO_DRIVE) {
                // std::cout << "开启自动驾驶" << std::endl;
                context.send_auto_drive(STANDBY_MODE);
            } else if(m_driving_mode == DrivingModeEnum::DrivingMode::MANUAL_DRIVE) {
                // std::cout << "开启手动驾驶" << std::endl;
                context.send_auto_drive(MANUAL_MODE);
            }
            m_driving_mode = DrivingModeEnum::DrivingMode::DEFAULT;
        }
    }
}

void CAduProxy::addPoint(const double lng, const double lat) {
    // 坐标转换
    {
        Wgs8451Position wgs8451 = m_util->Gcj02_to_wgs8451(lng, lat);
        // std::vector<Wgs8451Position> target_vect;
        // target_vect.push_back(wgs8451);
        // m_vects.push_back(target_vect);
        std::unique_lock<std::mutex> guard(m_listMtx);
        m_target_points_vect.push_back(wgs8451);
        std::cout << "addPoint: " << lng << "," << lat << std::endl;
    }
}

void CAduProxy::removePoint(const double lng, const double lat) {
    // 坐标转换
    {
        Wgs8451Position wgs8451 = m_util->Gcj02_to_wgs8451(lng, lat);
        std::unique_lock<std::mutex> guard(m_listMtx);
        // m_target_points_vect.push_back(wgs8451);
        for(auto iter = m_target_points_vect.begin(); iter != m_target_points_vect.end(); iter++) {
            if(iter->get_longitude() == wgs8451.get_longitude() && iter->get_latitude() == wgs8451.get_latitude()) {
                m_target_points_vect.erase(iter);
                break;
            }
        }
        std::cout << "removePoint: " << lng << "," << lat << std::endl;
    }
}

void CAduProxy::clearAllPoints() {
    {
        std::unique_lock<std::mutex> guard(m_listMtx);
        m_target_points_vect.clear();
        std::cout << "clear all points. " << std::endl;
    }
}

void CAduProxy::drivingRoute() {
    // 子线程发送请求
    std::cout << __func__ << std::endl;
    // std::thread _thread([&](){
    //     if(m_vects.size() > 0) {
    //         auto target = m_vects.front();
    //         m_vects.pop_back();
    //         context.send_data(target);
    //     }
    // });
    // _thread.detach();
    //while(true);
    m_condr.notify_one();
}

void CAduProxy::setCurrentPosition(const double _x, const double _y) {
    //std::cout << "主车当前位置" << _x << ", "<< _y << std::endl;
    Gcj02Position gcj02 = m_util->Wgs8451_to_gcj02(_x, _y);
    double curr_x = gcj02.get_longitude();
    double curr_y = gcj02.get_latitude();
    double dis = GetDistance(m_lastPt.x(), m_lastPt.y(), curr_x, curr_y);
    // 更新上次的位置
    // if(dis < DISTANCE_THRESHOLD) {
    //     return;
    // }
    m_lastPt.setX(curr_x);
    m_lastPt.setY(curr_y);
    // 每隔50ms刷新一次
    auto now_t = std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
    if (now_t - last_t < g_config.m_heroCarUpdateFreq) {
        return;
    }
    last_t = now_t;
    // Bd09Position bd09 {_x , _y};
    Q_EMIT notifyCurrentPosition(gcj02.get_longitude(), gcj02.get_latitude());
    Q_EMIT notifyCurrentPositionXY(_x, _y);
}

double CAduProxy::rad(const double d) {
    return d * M_PI / 180.0;
}

double CAduProxy::GetDistance(const double lat1, const double lng1, const double lat2, const double lng2) {
    double radLat1 = rad(lat1);
    double radLat2 = rad(lat2);
    double x_dis = radLat1 - radLat2;
    double y_dis = rad(lng1) - rad(lng2);

    double dis = 2 * asin(sqrt(pow(sin(x_dis/2),2) +
    cos(radLat1) * cos(radLat2) * pow(sin(y_dis/2),2)));
    dis = dis * EARTH_RADIUS;
    dis = round(dis * 10000) / 10000;
    return dis;
}

void CAduProxy::target_curve_paths(std::vector<std::pair<double, double>> curve_paths) {
    std::cout << __func__ << " SIZE:" << curve_paths.size() << std::endl;
    QVariantList point_list;
    for(auto iter = curve_paths.begin(); iter != curve_paths.end(); iter++) {
        Gcj02Position gcj02 = m_util->Wgs8451_to_gcj02(iter->first, iter->second);
        // std::cout << gcj02.to_string() <<std::endl;
        // TODO 测试
        // Gcj02Position gcj02 {iter->first, iter->second};
        QList<double> points;
        points.append(gcj02.get_longitude());
        points.append(gcj02.get_latitude());
        QVariant vr;
        vr.setValue(points);
        point_list.append(vr);
        // Q_EMIT notifyTargetCurvePath(gcj02.get_longitude(), gcj02.get_latitude());
    }
    Q_EMIT notifyTargetCurvePath(point_list);
}

void CAduProxy::handle_path_unreachable() {
    Q_EMIT notifyPathUnreachable();
}

void CAduProxy::set_traffic_light(std::vector<std::pair<LightDirection, LightColor>> traffic_lights) {
    // std::cout << "the size of traffic lights: " << traffic_lights.size() << std::endl;
    QVariantList traffic_light_list;
    for(auto& lights: traffic_lights) {
        QList<double> light;
        light.append(lights.first);
        light.append(lights.second);
        QVariant vr;
        vr.setValue(light);
        traffic_light_list.append(vr);
    }
    Q_EMIT notifyTrafficLight(traffic_light_list);
}

void CAduProxy::switchDrivingMode(uint32_t driving_mode) {
    std::cout << "driving_mode: " << driving_mode << std::endl;
    {
        std::unique_lock<std::mutex> guard(m_modeMtx);
        m_driving_mode = driving_mode;
        m_modelCondr.notify_one();
    }
}

void CAduProxy::setVehicleDriveSteer(const float steer) {
    Q_EMIT notifyVehicleDriveSteer(steer);
}

void CAduProxy::setVehicleDriveThrottle(const float throttle) {
    Q_EMIT notifyVehicleDriveThrottle(throttle);
}

void CAduProxy::setVehicleDriveSpeed(const float speed) {
    Q_EMIT notifyVehicleDriveSpeed(speed);
}

void CAduProxy::setVehicleDriveMode(const DrivingMode mode) {
    QVariant vr;
    switch(mode) {
        case MANUAL_MODE:
            vr.setValue(DrivingModeEnum::MANUAL_DRIVE);
            Q_EMIT notifyVehicleDriveMode(vr);
            break;
        case AUTO_DRIVE_MODE:
            vr.setValue(DrivingModeEnum::ATUO_DRIVE);
            Q_EMIT notifyVehicleDriveMode(vr);
            break;
        default:
            break;
    }
}