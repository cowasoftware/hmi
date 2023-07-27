#include "ConfigManager.h"
#include "qdebug.h"
#include "LevelDBManager.h"
#include <QGuiApplication>
#include <QScreen>
#include <QProcess>
#include <iostream>
#include <algorithm>
#include <QDateTime>
#include "QtNetwork/qhostinfo.h"
#include <QNetworkInterface>
#include "network_manager.h"
#include "ConfigConstants.h"
#include "redis_manager.h"
#include "json/json.h"
#include <QJsonObject>

#define LOGGER GetLogMgr().getLogger()
#define FILE_ID 0

ConfigManager::ConfigManager(QObject *parent)
    : QObject{parent}
{
    m_theme = "default_theme";
    screen_width = getScreenWidth();
    screen_height = getScreenHeight();
}

inline CLogMgr& ConfigManager::GetLogMgr() {
  static CLogMgr my_logger("MAPP", "MCON", E_FUNC_LINE, DLT_AND_CONSOLE);
  return my_logger;
}

QRect getScreen() {
    // 多显示器
    QList<QScreen *> list_screen = QGuiApplication::screens();
    QRect rect = list_screen.at(0)->geometry();
    return rect;
}

double ConfigManager::getScreenWidth() {
    QRect rect = getScreen();
    double desktop_width = rect.width();
    double desktop_height = rect.height();
    qDebug()<<"desktop_width: "<<desktop_width<<desktop_height;
    return desktop_width;
}

double ConfigManager::getScreenHeight() {
    QRect rect = getScreen();
    double desktop_width = rect.width();
    double desktop_height = rect.height();
    qDebug()<<"desktop_width: "<<desktop_width<<desktop_height;
    return desktop_height;
}


void ConfigManager::executeShellCmd(int mode, int value) {
    std::string cmdStr;
    float mValue; 

    switch (mode)
    {
    case m_eMsgType.VOLUME_ADJUST:
        // 执行音量调节shell命令
        // "amixer -c 0 sset 'Master',0 %1, 80% unmute"
        LOGGER->Cowa_Info(("current volume: " + std::to_string(value)).c_str());
        //cmd = tr("amixer cset numid=1,iface=MIXER,name='PCM Playback Volume' %1").arg(valtrue);
        cmdStr = "amixer cset numid=9,iface=MIXER,name='PCM Playback Volume' " + std::to_string(value);
        LOGGER->Cowa_Info(("cmdstr = " + cmdStr).c_str());
        // QProcess::execute("sudo amixer cset numid=1,iface=MIXER,name='PCM Playback Volume' 60");
        if (system(cmdStr.c_str()) == -1)
        {
            std::cout << "system error" << std::endl;
        }
        break;
    case m_eMsgType.BRIGHTNESS_CONTROL:
        // 执行亮度调节shell命令
        // 更改value为0~1之间的浮点数
        mValue = (float) value * 0.01;
        mValue = std::max(mValue, 0.2f);
        LOGGER->Cowa_Info(("current brightness: " + std::to_string(mValue)).c_str());
        cmdStr = "xrandr --output eDP-1 --brightness " + std::to_string(mValue);
        LOGGER->Cowa_Info(("cmdstr = " + cmdStr).c_str());
        if (system(cmdStr.c_str()) == -1)
        {
            std::cout << "system error" << std::endl;
        }
        break;
    
    default:
        break;
    }
}

bool ConfigManager::getConfigFromDB(std::string key, std::string& value, int32_t fileId) {
    bool result = LevelDBManager::instance().getConfig(key, value, fileId);
    std::string msg_str = "";
    msg_str.append("getConfigFromDB, key = ").append(key)
           .append(", value = ").append(value)
           .append(", result = ").append(std::to_string(result));
    //LOGGER->Cowa_Info(msg_str.c_str());
    QString myk = QString::fromStdString(key);
    QString myv = QString::fromStdString(value);
    // TODO 
    // QString myv2 = QString::fromStdString("1");
    // setConfigToDB(myk, myv2, 0);
    Q_EMIT signalSendConfig(myk, myv, fileId);
    return result;
}

void ConfigManager::setConfigToDB(QString key, QString value, int fileId) {
    std::string strKey = key.toStdString();
    std::string strValue = value.toStdString();
    std::string msg_str = "";
    msg_str.append("setConfigToDB, key = ").append(strKey)
           .append(", value = ").append(strValue);
    LOGGER->Cowa_Info(msg_str.c_str());
    LevelDBManager::instance().setConfig(strKey, strValue, fileId);
}

QString ConfigManager::getCurDate()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    //日期
    QString tempDate = dateTime.toString("yyyy-MM-dd");
    if (m_curDate != tempDate)
    {
        m_curDate = tempDate;
    }
    return m_curDate;
}
std::string ConfigManager::getTodayMile(std::string totalMile)
{
    QString date = getCurDate();
    std::string todayMile;
    bool res = LevelDBManager::instance().getConfig(date.toStdString(), todayMile, FILE_ID);
    if (!res)
    {
        LOGGER->Cowa_Warn("the key, not found val, to set today mile to leveldb *****************");
        LevelDBManager::instance().setConfig(date.toStdString(), totalMile, FILE_ID);
        todayMile = totalMile;
    }else
    {
        LOGGER->Cowa_Info(("****************** get today mile is : " + todayMile).c_str());
    }
    return todayMile;
}

void ConfigManager::getLocalIpWithQt() {
    //获取所有网络接口的列表
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //遍历每一个网络接口
    Q_FOREACH(QNetworkInterface interface,list)
    { 
        // 设备为有线网卡eth0，无线网卡wlan0
        if(interface.name() == "eth0" || interface.name() == "wlan0") {
            //设备名
            LOGGER->Cowa_Info(("Device: " + interface.name().toStdString()).c_str());
            Q_FOREACH (QHostAddress address, interface.allAddresses()) {
                if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) {
                    // ipv4地址
                    LOGGER->Cowa_Info(("IPv4 Address: " + address.toString().toStdString()).c_str());
                    Q_EMIT signalSendIpInfo(address.toString());
                    break;
                }
            }
        }
    }
}

std::string ConfigManager::getBuildVersion() {
    std::string versionInfo = std::string(HMI_BUILD_VERSION);
    Q_EMIT signalSendVersionInfo(QString::fromStdString(versionInfo));
    return versionInfo;
}

std::string ConfigManager::getBuildTime() {
    std::string buildTime = std::string(HMI_BUILD_TIME);
    return buildTime;
}

void ConfigManager::parseUrl(QString url) {
    std::string url_str = url.toStdString();
    LOGGER->Cowa_Info(("url: " + url_str).c_str());
    if(url_str.empty()) {
        return;
    }
    std::string splits = "?";
    size_t pos = url_str.find(splits);
    int step = splits.size();
    if(pos == url_str.npos) {
        // 没有参数
        return;
    }
    if(m_loginInfo == nullptr) {
        m_loginInfo = std::make_shared<LoginInfo>();
    }
    m_loginInfo->base_url = url_str.substr(0, pos);
    url_str = url_str.substr(pos + step, url_str.size());
    // 分割参数
    std::vector<std::string> res;
    // 字符串末尾加分割符，方便截取最后一段
    splits = "&";
    split(url_str + splits, splits, res);
    // 参数与值
    for(auto s: res) {
        std::vector<std::string> res1;
        split(s, "=", res1);
    }
}

void ConfigManager::split(const std::string& str, const std::string& splits, std::vector<std::string>& res) {
    if(str.empty())
        return;
    std::string strs = str;
    size_t pos = strs.find(splits);
    int step = splits.size();
    while(pos != strs.npos) {
        std::string temp = strs.substr(0, pos);
        res.push_back(temp);
        // 剩余字符串
        strs = strs.substr(pos + step, strs.size()); 
        if(splits == "=") {
            // 保存键值对 temp：strs
            Q_EMIT signalCheckLoginStatus(QString::fromStdString(temp), QString::fromStdString(strs));
        }
        pos = strs.find(splits);
    }
}

void ConfigManager::saveLoginInfo(QString username, QString vehicleId, QString openId, QString loginStatus) {
    LOGGER->Cowa_Info(("saveLoginInfo: " + username.toStdString()).c_str());
    Q_EMIT sendLoginInfo(username, vehicleId, openId);
    // TODO 保存登录信息到数据库
    if(m_loginInfo == nullptr) {
        m_loginInfo = std::make_shared<LoginInfo>();
    }
    m_loginInfo->user_name = username.toStdString();
    m_loginInfo->vehicle_id = vehicleId.toStdString();
    m_loginInfo->open_id = openId.toStdString();
    m_loginInfo->login_status = loginStatus.toStdString();
    QDateTime dateTime = QDateTime::currentDateTime();
    m_loginInfo->login_datetime = dateTime.toString("yyyy-MM-dd hh:mm:ss").toStdString();

    // 登录信息写入json,保存到leveldb
    Json::Value root;
    Json::Value loginJson;
    loginJson[LOGIN_USERNAME] = m_loginInfo->user_name;
    loginJson[LOGIN_VEHICLE_ID] = m_loginInfo->vehicle_id;
    loginJson[LOGIN_OPEN_ID] = m_loginInfo->open_id;
    loginJson[LOGIN_STATUS] = m_loginInfo->login_status;
    loginJson[LOGIN_DATATIME] = m_loginInfo->login_datetime;
    std::string strLogin = loginJson.toStyledString();
    LOGGER->Cowa_Info(strLogin.c_str());
    LevelDBManager::instance().setConfig(LOGIN_INFO_KEY, strLogin, FILE_ID);
}

QString ConfigManager::getLoginUser() {
    if(m_loginInfo == nullptr) {
        return QString::fromStdString("none");
    }
    return QString::fromStdString(m_loginInfo->user_name);
}

std::shared_ptr<LoginInfo> ConfigManager::getLoginInfo() {
    std::string loginValue;
    LevelDBManager::instance().getConfig(LOGIN_INFO_KEY, loginValue, FILE_ID);
    Json::Reader reader;
    Json::Value data;
    std::shared_ptr<LoginInfo> loginInfo = std::make_shared<LoginInfo>();
    if(reader.parse(loginValue, data)) {
        std::string userName = data[LOGIN_USERNAME].asString();
        std::string vehicleId = data[LOGIN_VEHICLE_ID].asString();
        std::string openId = data[LOGIN_OPEN_ID].asString();
        std::string loginStatus = data[LOGIN_STATUS].asString();
        std::string loginDateTime = data[LOGIN_DATATIME].asString();
        loginInfo->user_name = userName;
        loginInfo->vehicle_id = vehicleId;
        loginInfo->open_id = openId;
        loginInfo->login_status = loginStatus;
        loginInfo->login_datetime = loginDateTime;
        LOGGER->Cowa_Info(loginInfo->toString().c_str());
    }
    return loginInfo;
}

void ConfigManager::logout() {
    // notify server logout
    if(m_loginInfo == NULL) {
        return;
    }
    LOGGER->Cowa_Info("退出登录，清除用户数据！！！");
    NetworkManager::instance().sendLogoutRequest(LOGOUT_QR_URL, 
        QString::fromStdString(m_loginInfo->vehicle_id), 
        QString::fromStdString(m_loginInfo->open_id));
    deleteLevelDbConfig(LOGIN_INFO_KEY, FILE_ID);
    // TODO emit signal for backToLogin
    Q_EMIT backToLogin();
    m_loginInfo = nullptr;
}

void ConfigManager::autoLogout(std::shared_ptr<LoginInfo> info) {
    if(info == NULL) {
        return;
    }
    LOGGER->Cowa_Info("上次异常退出，需要先退出登录，清除用户数据！！！");
    NetworkManager::instance().sendLogoutRequest(LOGOUT_QR_URL, 
        QString::fromStdString(info->vehicle_id), 
        QString::fromStdString(info->open_id));
    // 清除leveldb数据
    deleteLevelDbConfig(LOGIN_INFO_KEY, FILE_ID);
}

void ConfigManager::saveToFavorites(QString key, QString targetAddress, const double longitude, const double latitude) {
    std::string strKey = key.toStdString();
    std::string strAddress = targetAddress.toStdString();
    std::string msg_str = "";
    msg_str.append("saveToFavorites, key = ").append(strKey)
           .append(", address = ").append(strAddress)
           .append(", coordinate = ").append("(" + std::to_string(longitude) + "," + std::to_string(latitude) + ")");
    LOGGER->Cowa_Info(msg_str.c_str());
    // targetVec.push_back(Point(targetAddress, longitude, latitude));
    std::string strValue;
    LevelDBManager::instance().getConfig(strKey, strValue);
    strValue.append(strAddress)
        .append(":")
        .append(std::to_string(longitude))
        .append(",")
        .append(std::to_string(latitude))
        .append("_");
    LevelDBManager::instance().setConfig(strKey, strValue, FILE_ID);
}

void ConfigManager::removeFromFavorites(QString key, QString targetAddress, const double longitude, const double latitude) {
    std::string strKey = key.toStdString();
    std::string strAddress = targetAddress.toStdString();
    std::string msg_str = "";
    msg_str.append("removeFromFavorites, key = ").append(strKey)
           .append(", address = ").append(strAddress)
           .append(", coordinate = ").append("(" + std::to_string(longitude) + "," + std::to_string(latitude) + ")");
    LOGGER->Cowa_Info(msg_str.c_str());
    // targetVec.push_back(Point(targetAddress, longitude, latitude));
    std::string strValue;
    LevelDBManager::instance().getConfig(strKey, strValue);

    int32_t last_pos = strValue.find_last_of("_");
    int32_t curr_pos = strValue.find_last_of("_", last_pos - 1);
    std::cout << last_pos << "," << curr_pos << std::endl;
    strValue = strValue.substr(0, curr_pos + 1);
    LevelDBManager::instance().setConfig(strKey, strValue, FILE_ID);
}

void ConfigManager::showFavorites(QString key) {
    std::string strKey = key.toStdString();
    std::string strValue;
    // LevelDBManager::instance().deleteConfig(strKey);
    LevelDBManager::instance().getConfig(strKey, strValue);
    LOGGER->Cowa_Info((strKey + ": " + strValue).c_str());
    // if(!targetVec.empty()) {
    //     for(auto iter = targetVec.cbegin(); iter != targetVec.cend();) {
    //         Point p = *iter;
    //         // qDebug() << "位置："<<p.address;
    //         // qDebug() << "坐标："<<p.longtitude << "," << p.latitude;
    //         iter = targetVec.erase(iter);
    //         Q_EMIT sendFavorites(p.address, p.longtitude, p.latitude);
    //     }
    // }

    // 先清空原来的数据
    Q_EMIT clearFavorites();
    parseCoordinateFromDB(strValue);
}

void ConfigManager::parseCoordinateFromDB(const std::string& pointStr) {
    if(pointStr.empty()) {
        return;
    }
    std::string splits = "_";
    size_t pos = pointStr.find(splits);
    int step = splits.size();
    if(pos == pointStr.npos) {
        return;
    }
    std::vector<std::string> res;
    splitPoint(pointStr, splits, res);
    // 分割每对坐标点
    for(auto &p: res) {
        std::vector<std::string> res1;
        splitPoint(p, ":", res1);
    }
}

void ConfigManager::splitPoint(const std::string& str, const std::string& splits, std::vector<std::string>& res) {
    if(str.empty())
        return;
    std::string strs = str;
    size_t pos = strs.find(splits);
    int step = splits.size();
    while(pos != strs.npos) {
        std::string first_part = strs.substr(0, pos);
        res.push_back(first_part);
        // 剩余字符串
        strs = strs.substr(pos + step, strs.size());
        if(splits == ":") {
            // strs格式为：addr:longtitude,latitude
            pos = strs.find(",");
            if(pos == strs.npos)
                return;
            //　解析坐标点
            double longtitude = std::stod(strs.substr(0, pos).c_str());
            double latitude = std::stod(strs.substr(pos + step, strs.size()).c_str());
            Q_EMIT sendFavorites(QString::fromStdString(first_part), longtitude, latitude);
        }
        pos = strs.find(splits);
    }
}

void ConfigManager::getVehicleInfo() {
    // 1、从redis获取车辆token
    RedisManager* redis = new RedisManager(REDIS_SERVER_IP, REDIS_SERVER_PORT);
    QObject::connect(redis, SIGNAL(notifyRedisResult(QString)), this, SLOT(onNotifyVehicleToken(QString)));
    std::string command = "get AccessToken";
    std::cout << "command: " << command << std::endl;
    redis->execRedis(command);
}

void ConfigManager::onNotifyVehicleToken(QString token) {
    // QString token2 = QString::fromStdString(token_str);
    // 2、根据token向车辆理平台查询车辆信息
    NetworkManager &instance = NetworkManager::instance();
    QObject::connect(&instance, SIGNAL(notifyVehicleInfo(QString, QString, QString)), this, SLOT(onNotifyVehicleInfo(QString, QString, QString)));
    instance.requestVehicleInfo(VEHICLE_SERVER_URL, REQUEST_METHOD_POST, REQUEST_HEADERS_CONTENT_TYPE_FORM, token);
}

void ConfigManager::onNotifyVehicleInfo(QString vehicleName, QString openId, QString plateNumber) {
    QString msg = QString("VehicleInfo: vehicleName=%1, openId=%2, plateNumber=%3").arg(vehicleName).arg(openId).arg(plateNumber);
    qDebug() << msg;
    Q_EMIT notifyVehicleInfo(vehicleName,openId, plateNumber);
}

void ConfigManager::deleteLevelDbConfig(const QString& key, int32_t fileId) {
    LevelDBManager::instance().deleteConfig(key.toStdString(), fileId);
}