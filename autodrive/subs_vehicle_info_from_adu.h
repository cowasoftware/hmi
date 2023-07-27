#pragma once

#include "common.h"
#include "recv_interface.h"
#include "context.h"
#include <QObject>
#include "AduHelper.h"

class SubsNotifier : public QObject {
  Q_OBJECT

  Q_SIGNALS:
    void notify_current_position(const double _x, const double _y);
    void notify_traffic_light(std::vector< std::pair<LightDirection, LightColor> > traffic_lights);
    // 方向盘转角
    void notify_vehicle_drive_steer(const float steer);
    // 刹车状态
    void notify_vehicle_drive_throttle(const float throttle);
    // 驾驶速度
    void notify_vehicle_drive_speed(const float speed);
    // 驾驶模式
    void notify_vehicle_drive_mode(const DrivingMode mode);
};


class SubsVehicleInfoFromAdu : public SubsRecvInterface {
 public: 
 SubsVehicleInfoFromAdu();
  virtual void onRecv(Message_Ptr msg) override;
  virtual void onError(Errno err) override
  {
    std::cout << "recv vehicle info from adu fail, code:" << err << std::endl;
  }
  private:
    SubsNotifier notifier;
};