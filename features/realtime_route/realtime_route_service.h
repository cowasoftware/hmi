#pragma once

#include <QObject>
#include <QString>
#include <QPointF>
#include <QVector>
#include <QMap>

#include "async_invoker.h"
#include "Singleton.h"



class RealtimeRouteService : public AsyncInvoker
{
    Q_OBJECT
public:
    enum class ResultCode
    {
        Ok,
        RouteNotExist,
        StationNotExist,
    };

    struct Station
    {
        QString name;
        QPointF position;
        qreal radius;
    };

    struct Route
    {
        QString id;
        QString name;
        QVector<Station> stations;
    };


public:
    RealtimeRouteService(QObject *parent = nullptr);
    ~RealtimeRouteService();

public:
    void getRoute(QString const &route_id, std::function<void(std::pair<ResultCode,Route> const&)> callback = nullptr, QObject* target = nullptr);
    void locateStation(QString const &route_id, QPointF const& position, std::function<void(std::pair<ResultCode,Station> const&)> callback = nullptr, QObject* target = nullptr);


private:
    void init();
    QMap<QString, Route> LoadFromFile(QString const& path);
    QString get_code_msg(ResultCode code);

private:
    bool initialized_ = false;
    QMap<QString, Route> route_map_;
};

typedef Singleton<RealtimeRouteService> SingletonRealtimeRouteService;