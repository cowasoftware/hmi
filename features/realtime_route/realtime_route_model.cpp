#include <QDebug>
#include <QThread>
#include <algorithm>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QTimer>
#include <QCoreApplication>
#include <QFile>

#include "realtime_route_model.h"
#include "realtime_route_service.h"
#include "../autodrive/AduProxy.h"

RouteStationItemModel::RouteStationItemModel(QObject *parent)
    : QObject(parent)
{
}

RealtimeRouteModel::RealtimeRouteModel(QObject *parent)
    : QObject(parent)
{
    station_list_model_ = new JsonListModel(QList<QString>() << "order"
                                                             << "name",
                                            this);
    set_stations(QVariant::fromValue(station_list_model_));

    current_station_model_ = new RouteStationItemModel(this);
    set_currentStation(QVariant::fromValue(current_station_model_));

    next_station_model_ = new RouteStationItemModel(this);
    set_nextStation(QVariant::fromValue(next_station_model_));

    if (QFile::exists(QCoreApplication::applicationDirPath() + QString("/config/route.json")))
    {
        connect(SingletonCAduProxy::getInstance(), &CAduProxy::notifyCurrentPositionXY, this, &RealtimeRouteModel::updatePosition);
    }

    updateRoute("go");

    // auto timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this,
    //         [this]()
    //         {
    //             static int index = 0;
    //             static QVector<QPointF> positions = {
    //                 QPointF(759088.8, 2452685.9),
    //                 QPointF(756188.7, 2451567.6),
    //                 QPointF(753705.0, 2451616.9),
    //                 QPointF(751652.4, 2452746.9),
    //                 QPointF(752251.4, 2450730.9),
    //                 QPointF(751652.4, 2452746.9),
    //                 QPointF(753705.0, 2451616.9),
    //                 QPointF(756188.7, 2451567.6),
    //                 QPointF(759088.8, 2452685.9),
    //                 QPointF(753705.0, 2451616.9),
    //             };

    //             auto p = positions[index++ % positions.size()];
    //             qDebug() << p;
    //             updatePosition(p.x(), p.y());
    //         });

    // timer->setInterval(2000);
    // timer->start();
}

void RealtimeRouteModel::updateRoute(QString id)
{
    auto call = [this, id](auto &result)
    {
        if (result.first != RealtimeRouteService::ResultCode::Ok)
        {
            return;
        }
        route_ = result.second;
        set_name(route_.name);
        QJsonArray stations_json;
        int order = 0;
        for (auto &station : route_.stations)
        {
            stations_json.push_back(QJsonObject({{"order", QJsonValue(order++)}, {"name", QJsonValue(station.name)}}));
        }

        station_list_model_->set(stations_json);

        current_station_model_->set_order(-1);
        current_station_model_->set_name("");
        set_currentStationIndex(-1);

        next_station_model_->set_order(-1);
        next_station_model_->set_name("");

        has_reversed = false;
    };

    SingletonRealtimeRouteService::getInstance()->getRoute(id, call);
}

void RealtimeRouteModel::updatePosition(double x, double y)
{
    // 2s更新线路站点
    // if (QDateTime::currentMSecsSinceEpoch() - last_timestamp < 1000)
    // {
    //     return;
    // }
    // last_timestamp = QDateTime::currentMSecsSinceEpoch();

    auto call = [this](auto result)
    {
        if (result.first != RealtimeRouteService::ResultCode::Ok)
        {
            return;
        }

        auto iter = std::find_if(route_.stations.begin(), route_.stations.end(), [&](auto station)
                                 { return station.name == result.second.name; });
        if (iter == route_.stations.end())
        {
            return;
        }

        auto &stations = route_.stations;
        int current_index = iter - route_.stations.begin();
        int next_index = -1;

        // go
        if (current_index > last_index_)
        {
            // next_index = current_index + 1 != stations.size() ? current_index + 1: -1;

            if (has_reversed)
            {
                has_reversed = !has_reversed;
                QJsonArray stations_json;
                int order = 0;
                for (auto station : stations)
                {
                    stations_json.push_back(QJsonObject({{"order", QJsonValue(order++)}, {"name", QJsonValue(station.name)}}));
                }
                station_list_model_->set(stations_json);
            }

            current_station_model_->set_order(current_index);
            current_station_model_->set_name(stations[current_index].name);

            if (current_index + 1 != stations.size())
            {
                next_station_model_->set_order(current_index + 1);
                next_station_model_->set_name(stations[current_index + 1].name);
            }
            else
            {
                next_station_model_->set_order(-1);
                next_station_model_->set_name("");
            }

            set_currentStationIndex(current_index);
        }
        // back
        else if (current_index < last_index_)
        {
            if (!has_reversed)
            {
                has_reversed = !has_reversed;
                QJsonArray stations_json;
                int order = route_.stations.size() - 1;
                for (auto station : route_.stations)
                {
                    stations_json.push_front(QJsonObject({{"order", QJsonValue(order--)}, {"name", QJsonValue(station.name)}}));
                }
                station_list_model_->set(stations_json);
            }

            current_station_model_->set_order(stations.size() - current_index - 1);
            current_station_model_->set_name(stations[current_index].name);

            if (current_index != 0)
            {
                next_station_model_->set_order(stations.size() - current_index);
                next_station_model_->set_name(stations[current_index - 1].name);
            }
            else
            {
                next_station_model_->set_order(-1);
                next_station_model_->set_name("");
            }

            set_currentStationIndex(stations.size() - current_index - 1);
        }
        last_index_ = current_index;
    };

    SingletonRealtimeRouteService::getInstance()->locateStation("go", QPointF(x, y), call);
}