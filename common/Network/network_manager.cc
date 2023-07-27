#include "network_manager.h"
#include "ConfigConstants.h"
#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <hiredis/hiredis.h>
#include <threads.h>


NetworkManager::NetworkManager(QObject *parent)
{
    init();
}

NetworkManager::~NetworkManager() {
    if(manager != nullptr) {
        manager->deleteLater();
    }
}

NetworkManager& NetworkManager::instance() {
    static NetworkManager s_networkManager;
    return s_networkManager;
}

void NetworkManager::init() {
    manager = new QNetworkAccessManager(this); 
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)));     //绑定完成信号
}


// this url is not the real url, the real url = baseUrl + url
// for example, th real url is: http://172.31.10.111:2000/v1/time
void NetworkManager::sendGetRequest(QString url) {
    QString realUrl = HMI_REMOTE_BASE_URL + url;
    qDebug() << "the hmi remote url is: " << realUrl;
    QNetworkRequest request;
    request.setUrl(QUrl(realUrl));
    manager->get(request);
}

void NetworkManager::sendLogoutRequest(QString url, QString vehicleId, QString openId) {
    QString realUrl = HMI_REMOTE_BASE_URL + url;
    qDebug() << "the hmi remote url is: " << realUrl;

    QNetworkRequest request;
    request.setUrl(QUrl(realUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

    QJsonObject jsonObj;
    jsonObj.insert(LOGOUT_PARAM_VEHICLE, vehicleId);
    jsonObj.insert(LOGOUT_PARAM_OPEN_ID, openId);
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObj);
    QByteArray qByteHttpData = jsonDoc.toJson();
    manager->post(request, qByteHttpData);
}

void NetworkManager::requestVehicleInfo(QString url, QString requestType, QString headers, QString token) {
    QString msg = "requestVehicleInfo:: url: " + url + ", headers: " + headers + ", token: " + token;
    qDebug() << msg;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    // QSslConfiguration config;
    // config.setPeerVerifyMode(QSslSocket::VerifyNone);
    // config.setProtocol(QSsl::SslV3);
    // request.setSslConfiguration(config);
    
    if(requestType == REQUEST_METHOD_POST) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(headers));
        QNetworkReply* rep;
        if(REQUEST_HEADERS_CONTENT_TYPE_FORM == headers.toStdString()) {
            QString formData = QString("token=%1").arg(token);
            rep =  manager->post(request, formData.toUtf8());
        } else if(REQUEST_HEADERS_CONTENT_TYPE_JSON == headers.toStdString()) {
            QJsonObject jsonObj;
            jsonObj.insert(REQUEST_DATA, token);
            QJsonDocument jsonDoc;
            jsonDoc.setObject(jsonObj);
            QByteArray qByteHttpData = jsonDoc.toJson();
            rep =  manager->post(request, qByteHttpData);
        }
        rep->ignoreSslErrors();
    } else if(requestType == REQUEST_METHOD_GET) {
        manager->get(request);
    }
}

void NetworkManager::onFinished(QNetworkReply *reply) {
    QByteArray responseByte = reply->readAll();
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(responseByte, &jsonError);
    if(!document.isNull() && (QJsonParseError::NoError == jsonError.error)) {
        // parse response
        if(document.isObject()) {
            QJsonObject obj = document.object();
            qDebug() << "response is: " << obj;
            if(reply->error() == QNetworkReply::NoError) {
                // response: {"code": 200, "data": {}}
                if(obj.contains("code") && obj.take("code") == 200) {
                    if(obj.contains("data")) {
                        QJsonValue jsonData = obj.take("data");
                        QJsonObject objData = jsonData.toObject();
                        if(objData.contains("ts")) {
                            // timestamp
                            QJsonValue ts = objData.take("ts");
                            if(ts.isString()) {
                                QString login_time = QDateTime::fromSecsSinceEpoch(ts.toVariant().toInt()).toString("yyyy-MM-dd hh:mm:ss.zzz");
                                qDebug() << "login_time: " << login_time;
                            }
                        }
                    }
                }
                // parse vehicle info, {"expire": "", "user": {"open_id": "","name": "","plate_number": ""}}
                if(obj.empty() || !obj.contains("user")) {
                    qDebug() << "request vehicle info failed!!!";
                } else {
                    if(obj.contains("expire")) {
                        QJsonValue expire = obj.take("expire");
                        QVariant expireValue =  QDateTime::fromSecsSinceEpoch(expire.toVariant().toInt());
                        if(expireValue < QDateTime::currentSecsSinceEpoch()) {
                            qDebug() << "token is expired: " << reply->error();   
                        } else {
                            QJsonValue userData = obj.take("user");
                            QJsonObject objData = userData.toObject();
                            QString vehicle_name;
                            QString open_id;
                            QString plate_number;
                            if(objData.contains("name")) {
                                vehicle_name = objData.take("name").toVariant().toString();
                            }
                            if(objData.contains("open_id")) {
                                open_id = objData.take("open_id").toVariant().toString();
                            }
                            if(objData.contains("plate_number")) {
                                plate_number = objData.take("plate_number").toVariant().toString();
                            }
                            Q_EMIT notifyVehicleInfo(vehicle_name, open_id, plate_number);
                        }
                    }
                }
            } else {
                // bad requset
                qDebug() << "request error, the reason is: " << reply->error();
            }
        }
    }
    reply->deleteLater();
}
