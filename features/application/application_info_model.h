#pragma once

#include <QObject>

class ApplicationInfoModel : public QObject
{
public:
    enum class VehicleType
    {
        PassengeVehicle,
        MiniBusVehicle,
    };

public:
    ApplicationInfoModel(QObject *parent = nullptr);
    ~ApplicationInfoModel();

public:
    VehicleType GetVehicleType();

private:
    VehicleType vehicle_type_;
};