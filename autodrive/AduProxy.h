#ifndef CAduProxy_H
#define CAduProxy_H

#include <QObject>
#include <thread>
#include <condition_variable>
#include "Singleton.h"
#include "CoordinateUtil.h"
#include "AduHelper.h"
#include <QPointF>
#include "TrafficLightType.h"
#include <QVariant>

class CAduProxy : public QObject
{
    Q_OBJECT
public:
    explicit CAduProxy(QObject *parent = nullptr);

    ~CAduProxy();

    void destroy();

    // 选点
    Q_INVOKABLE void addPoint(const double lng, const double lat);

    // 取消选点
    Q_INVOKABLE void removePoint(const double lng, const double lat);

    // 清空vector中的点
    Q_INVOKABLE void clearAllPoints();

    // 向adu请求驾车路线
    Q_INVOKABLE void drivingRoute();

    // 切换驾驶模式
    Q_INVOKABLE void switchDrivingMode(uint32_t driving_model);

    void threadFunc();

    // 请求自动驾驶线程
    void drivingModelThreadFunc();
    
Q_SIGNALS:
    // 主车位置
    void notifyCurrentPosition(const double _x, const double _y);
    void notifyCurrentPositionXY(const double _x, const double _y);
    // 行驶路线
    // void notifyTargetCurvePath(const double _x, const double _y);
    // void notifyTargetCurvePath(QList<QList<double>>& paths);
    void notifyTargetCurvePath(QVariantList paths);
    void notifyPathUnreachable();
    // 交通灯
    void notifyTrafficLight(QVariantList traffic_light_list);
    // 方向盘转角
    void notifyVehicleDriveSteer(const float steer);
    // 刹车状态
    void notifyVehicleDriveThrottle(const float throttle);
    // 驾驶速度
    void notifyVehicleDriveSpeed(const float speed);
    // 驾驶模式
    void notifyVehicleDriveMode(QVariant mode);

public Q_SLOTS:
    // 得到主车位置
    void setCurrentPosition(const double _x, const double _y);

    // 接收客户端返回的行驶轨迹
    void target_curve_paths(std::vector<std::pair<double, double>> curve_paths);

    void handle_path_unreachable();

    // 接收adu返回的信号灯
    void set_traffic_light(std::vector<std::pair<LightDirection, LightColor>> traffic_lights);

    // 接收方向盘转角
    void setVehicleDriveSteer(const float steer);

    // 接收刹车状态
    void setVehicleDriveThrottle(const float throttle);

    // 驾驶速度
    void setVehicleDriveSpeed(const float speed);

    // 驾驶模式
    void setVehicleDriveMode(const DrivingMode mode);

    // 计算地图上两点距离
    // 转化为弧度
    double rad(const double d);
    double GetDistance(const double lat1, const double lng1, const double lat2, const double lng2);

private: 
    // 选中的路径点
    // std::vector<std::vector<Wgs8451Position>> m_vects;
    std::vector<Wgs8451Position> m_target_points_vect;
    CoordinateUtil* m_util;
    std::thread m_handleCurvePointThread;   // 请求曲线点线程
    std::thread m_handleDrivingModelThread; // 处理驾驶模式线程
    std::mutex m_listMtx;
    std::condition_variable m_condr;
    std::mutex m_modeMtx;
    std::condition_variable m_modelCondr;
    uint32_t m_driving_mode;
    QPointF m_lastPt;   // 上一次的主车位置
    long last_t = 0;
};

typedef Singleton<CAduProxy> SingletonCAduProxy;

#endif // CAduProxy_H
