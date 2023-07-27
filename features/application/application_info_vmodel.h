#pragma once

#include <QObject>

#include "qmlreflect.h"

class ApplicationInfoModel;

class ApplicationInfoVModel : public QObject
{
    Q_OBJECT
    READ_PROPERTY(quint32, vehicle, 0)
    READ_PROPERTY(bool, showRoute, false)
public:
    enum class Vehicle
    {
        PassengeVehicle,
        MiniBusVehicle,
    };
    Q_ENUM(Vehicle)

public:
    ApplicationInfoVModel(QObject *parent = nullptr);
    ~ApplicationInfoVModel();

private:
    ApplicationInfoModel *model_{nullptr};
};