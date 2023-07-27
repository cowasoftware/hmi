#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QThread>
#include <QCoreApplication>
#include <QMetaObject>
#include <QTimer>

#include "realtime_route_service.h"

RealtimeRouteService::RealtimeRouteService(QObject *parent)
    : AsyncInvoker(parent)
{
    init();
}

RealtimeRouteService::~RealtimeRouteService()
{
}

void RealtimeRouteService::init()
{
    invoke<int>(
        [this]()
        {
            auto path = QCoreApplication::applicationDirPath() + QString("/config/route.json");
            route_map_ = LoadFromFile(path);
            return 0;
        });
}

void RealtimeRouteService::getRoute(QString const &route_id, std::function<void(std::pair<ResultCode, Route> const &)> callback, QObject *target)
{

    invoke<std::pair<ResultCode, Route>>(
        [this, route_id]()
        {
            if (route_map_.contains(route_id))
            {
                return std::make_pair(ResultCode::Ok, route_map_[route_id]);
            }
            else
            {
                return std::make_pair(ResultCode::RouteNotExist, Route{});
            }
        },
        [this, callback](auto result)
        {
            //qDebug() << "call RealtimeRouteService::getRoute" << get_code_msg(result.first);
            if(callback)
                callback(result);
        },
        target);
}

void RealtimeRouteService::locateStation(QString const &route_id, QPointF const &position, std::function<void(std::pair<ResultCode, Station> const &)> callback, QObject *target)
{
    invoke<std::pair<ResultCode, Station>>(
        [this, route_id, position]()
        {
            auto iter = route_map_.find(route_id);
            if (iter != route_map_.end())
            {
                int index = -1;

                for (auto &station : iter.value().stations)
                {
                    auto offset = position - station.position;

                    if (offset.x() * offset.x() + offset.y() * offset.y() < station.radius * station.radius)
                    {
                        return std::make_pair(ResultCode::Ok, station);
                    }
                }
            }
            return std::make_pair(ResultCode::StationNotExist, Station());
        },
        [this, callback](auto result)
        {
            //qDebug() << "call RealtimeRouteService::locateStation" << get_code_msg(result.first);
            if(callback)
                callback(result);
        },
        target);
}

QMap<QString, RealtimeRouteService::Route> RealtimeRouteService::LoadFromFile(QString const &path)
{
    QMap<QString, Route> route_map;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return route_map;
    }

    auto data = file.readAll();
    auto doc = QJsonDocument::fromJson(data);
    if (doc.isObject())
    {
        auto root = doc.object();
        auto routes = root["routes"].toArray();
        for (auto const &route_value : routes)
        {
            auto route = route_value.toObject();
            auto route_id = route["id"].toString();

            if (!route_id.isEmpty())
            {
                auto route_item = Route();
                route_item.id = route_id;
                route_item.name = route["name"].toString();
                for (auto station_value : route["stations"].toArray())
                {
                    auto station = station_value.toObject();
                    route_item.stations.push_back({station["name"].toString(), QPointF{station["x"].toDouble(), station["y"].toDouble()}, station["radius"].toDouble()});
                }
                route_map[route_id] = route_item;
            }
        }
    }

    return route_map;
}

QString RealtimeRouteService::get_code_msg(ResultCode code)
{
    switch (code)
    {
    case ResultCode::Ok:
        return "OK";
    case ResultCode::RouteNotExist:
        return "route not exist";
    case ResultCode::StationNotExist:
        return "station not exist";
    default:
        return "OK";
    }
}