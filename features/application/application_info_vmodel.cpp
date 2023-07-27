#include "application_info_vmodel.h"
#include "application_info_model.h"
#include <QFile>
#include <QCoreApplication>

ApplicationInfoVModel::ApplicationInfoVModel(QObject *parent)
    : QObject(parent)
{
    model_ = new ApplicationInfoModel(this);
    set_vehicle((quint32)model_->GetVehicleType());
    set_showRoute(QFile::exists(QCoreApplication::applicationDirPath() + QString("/config/route.json")));
}

ApplicationInfoVModel::~ApplicationInfoVModel()
{
}