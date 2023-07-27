#include "CoordinateUtil.h"

CoordinateUtil::CoordinateUtil(QObject *parent)
    : QObject{parent}
{

}

CoordinateUtil::~CoordinateUtil() {

}

Wgs8451Position CoordinateUtil::Bd09_to_wgs8451(const double& lontitude, const double& latitude) {
    Bd09Position bd09(lontitude, latitude);
    Wgs84Position wgs84 = bd09_to_wgs84(bd09);
    Wgs8451Position wgs8451 = wgs84_to_wgs8451(wgs84);
    // emit signalBd09_wgs8451(wgs8451.get_longitude(), wgs8451.get_latitude());
    return wgs8451;
}

Bd09Position CoordinateUtil::Wgs8451_to_bd09(const double& lontitude, const double& latitude) {
    Wgs8451Position wgs8451(lontitude, latitude);
    Wgs84Position wgs84 = wgs8451_to_wgs84(wgs8451);
    Bd09Position bd09 = wgs84_to_bd09(wgs84);
    // emit signalWgs8451_bd09(bd09.get_longitude(), bd09.get_latitude());
    return bd09;
}

Wgs8451Position CoordinateUtil::Gcj02_to_wgs8451(const double& lontitude, const double& latitude) {
    Gcj02Position gcj02(lontitude, latitude);
    Wgs84Position wgs84 = gcj02_to_wgs84(gcj02);
    Wgs8451Position wgs8451 = wgs84_to_wgs8451(wgs84);
    return wgs8451;
}

Gcj02Position CoordinateUtil::Wgs8451_to_gcj02(const double& lontitude, const double& latitude) {
    Wgs8451Position wgs8451(lontitude, latitude);
    Wgs84Position wgs84 = wgs8451_to_wgs84(wgs8451);
    Gcj02Position gcj02 = wgs84_to_gcj02(wgs84);
    return gcj02;
}
