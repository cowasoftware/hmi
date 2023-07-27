#pragma once

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>    //加载网络请求头文件
#include <QNetworkReply>
#include <QNetworkRequest>      //加载发送请求头文件
#include <hiredis/hiredis.h>


class NetworkManager : public QObject
{
    Q_OBJECT

public:
    static NetworkManager& instance();

    NetworkManager(QObject *parent = nullptr);
    NetworkManager(const NetworkManager& other) = delete;
    void init();

    ~NetworkManager();

    void sendGetRequest(QString url);
    // 退出登录
    void sendLogoutRequest(QString url, QString vehicleId, QString openId);
    // 查询车辆管理后端
    void requestVehicleInfo(QString url, QString requestType, QString headers, QString token);

Q_SIGNALS:
    void notifyVehicleInfo(QString vehicleName, QString openId, QString plateNumber);

public Q_SLOTS:
    void onFinished(QNetworkReply*);


private:
    QNetworkAccessManager *manager;
    redisContext* pRedisContext;

};
