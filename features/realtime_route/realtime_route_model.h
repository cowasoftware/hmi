#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QPointF>
#include <QJsonObject>
#include "qmlreflect.h"
#include "json_listmodel.h"

#include "realtime_route_service.h"

class RouteStationItemModel : public QObject
{
    Q_OBJECT
    READ_PROPERTY(qint32, order, -1)
    READ_PROPERTY(QString, name, "")
public:
    RouteStationItemModel(QObject *parent = nullptr);
};

class RealtimeRouteModel : public QObject
{
    Q_OBJECT
    READ_PROPERTY(qint32, currentStationIndex, -1)
    READ_PROPERTY(QVariant, currentStation, QVariant())
    READ_PROPERTY(QVariant, nextStation, QVariant())
    READ_PROPERTY(QVariant, stations, QVariant())
    READ_PROPERTY(QString, name, QString())

public:
    RealtimeRouteModel(QObject *parent = nullptr);

// private Q_SLOTS:
//     void updateRouteList(QJsonArray routes);
//     void updatePosition(double const x, double const y);
//     void updateRoute(QString route_id, QJsonObject route);
//     void updateStation(QString route_id, qint32 current, qint32 next);

// public:
//     Q_INVOKABLE void selectRoute(QString route_id);

private Q_SLOTS:
    void updateRoute(QString id);
    void updatePosition(double x, double y);

private:
    int last_index_ = -1;
    bool has_reversed = false;
    RealtimeRouteService::Route route_;
    qint64 last_timestamp = 0;
    JsonListModel *station_list_model_{nullptr};
    RouteStationItemModel *current_station_model_{nullptr};
    RouteStationItemModel *next_station_model_{nullptr};
};
