#include <QFile>
#include <QCoreApplication>
#include <QDebug>
#include "Cini.h"
#include "ini_reader.h"
#include "application_info_model.h"

ApplicationInfoModel::ApplicationInfoModel(QObject *parent)
    : QObject(parent)
{
    Cini ini((QCoreApplication::applicationDirPath() + QString("/autodrive.ini")).toStdString());
    IniReader reader;
    int vehicle_type = 0;
    reader.Read("vehicleType", ini.readIni("vehicleType"), vehicle_type);
    vehicle_type_ = static_cast<VehicleType>(vehicle_type);
}

ApplicationInfoModel::~ApplicationInfoModel()
{
}

ApplicationInfoModel::VehicleType ApplicationInfoModel::GetVehicleType()
{
    return vehicle_type_;
}