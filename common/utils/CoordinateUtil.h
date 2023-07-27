#ifndef COORDINATEUTIL_H
#define COORDINATEUTIL_H

#include <QObject>
#include "Singleton.h"
#include "coordinate_convert.h"

class CoordinateUtil : public QObject
{
    Q_OBJECT
public:
    explicit CoordinateUtil(QObject *parent = nullptr);

    virtual ~CoordinateUtil();

    // Bd09转wgs8451
    static Wgs8451Position Bd09_to_wgs8451(const double& lontitude, const double& latitude);

    // wgs8451转Bd09
    static Bd09Position Wgs8451_to_bd09(const double& lontitude, const double& latitude);

    // gcj02转wgs8451
    static Wgs8451Position Gcj02_to_wgs8451(const double& lontitude, const double& latitude);

    // wgs8451转gcj02
    static Gcj02Position Wgs8451_to_gcj02(const double& lontitude, const double& latitude);

Q_SIGNALS:

    void signalBd09_wgs8451(double lontitude, double latitude);

    void signalWgs8451_bd09(double lontitude, double latitude);

};

typedef Singleton<CoordinateUtil> SingletonCoordinateUtil;

#endif // COORDINATEUTIL_H
