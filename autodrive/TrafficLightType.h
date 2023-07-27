#ifndef TRAFFICLIGHTTYPE_H
#define TRAFFICLIGHTTYPE_H

#include <QObject>

class TrafficLightEnum : public QObject
{
    Q_OBJECT
private:
    /* data */
public:
    TrafficLightEnum();
    
    enum Color {
        UNKNOWN = 0,
        RED = 1,
        YELLOW = 2,
        GREEN = 3
    };

    enum Direction {
        FORWARD = 1,
        LEFT = 2,
        RIGHT = 3,
        UTURN = 4,
        NONE = 5
    };

    Q_ENUM(Color);
    Q_ENUM(Direction);
};

class DrivingModeEnum : public QObject
{
    Q_OBJECT
private:
    /* data */
public:
    DrivingModeEnum();
    
    enum DrivingMode {
        DEFAULT = 0,
        ATUO_DRIVE = 1,
        MANUAL_DRIVE = 2
    };
    Q_ENUM(DrivingMode);

};

#endif

