#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H 

#include <QObject>
#include <QString>
#include <memory> 
#include "Singleton.h"
#include "MsgType.h"
#include "log.h"
#include <thread>
#include "LoginInfo.h"

using namespace Cowa;

struct Point
{
    QString address;
    double longtitude;
    double latitude;
    Point(QString addr, double lng, double lat) {
        address = addr;
        longtitude = lng;
        latitude = lat;
    }
};

class ConfigManager : public QObject
{
     Q_OBJECT
public:
    explicit ConfigManager(QObject *parent = nullptr);
    Q_PROPERTY(QString theme MEMBER m_theme NOTIFY themeChanged);
    Q_PROPERTY(double screenWidth MEMBER screen_width NOTIFY screenWidthChanged);
    Q_PROPERTY(double screenHeight MEMBER screen_height NOTIFY screenHeightChanged);

    /**
     * @brief Get the Log Mgr object
     * @return CLogMgr& 
     */
    inline CLogMgr& GetLogMgr();

    Q_INVOKABLE double getScreenWidth();
    Q_INVOKABLE double getScreenHeight();

    // 从数据库中获取配置信息
    // key: "index", value: default 0, fileId: default 0
    bool getConfigFromDB(std::string key, std::string& value, int32_t fileId);
    // 将配置信息保存到数据库中
    Q_INVOKABLE void setConfigToDB(QString key, QString value, int fileId);
    QString getCurDate();
    std::string getTodayMile(std::string totalMile);

    /** 获取主机ip地址信息
     */
    void getLocalIpWithQt();
    // 获取版本信息
    std::string getBuildVersion();
    std::string getBuildTime();

    Q_INVOKABLE void getVehicleInfo();
    Q_INVOKABLE void parseUrl(QString url);

    // 以spilts为分割符，分割字符串
    void split(const std::string& strs, const std::string& splits, std::vector<std::string>& res);
    // TODO 保存登录信息
    Q_INVOKABLE void saveLoginInfo(QString username, QString vehicleId, QString openId, QString loginStatus);
    // 返回用户名
    Q_INVOKABLE QString getLoginUser();
    std::shared_ptr<LoginInfo> getLoginInfo();
    // 保存用户收藏夹的目标点
    Q_INVOKABLE void saveToFavorites(QString key, QString targetAddress, const double longitude, const double latitude);
    Q_INVOKABLE void removeFromFavorites(QString key, QString targetAddress, const double longitude, const double latitude);
    // 获取用户收藏夹内容
    Q_INVOKABLE void showFavorites(QString key);
    void parseCoordinateFromDB(const std::string& pointStr);
    void splitPoint(const std::string& str, const std::string& splits, std::vector<std::string>& res);
    // 异常退出时，主动请求登出
    void autoLogout(std::shared_ptr<LoginInfo> info);
    // 清除leveldb数据
    void deleteLevelDbConfig(const QString& key, int32_t fileId);

private:
    QString m_theme = "default";
    double screen_width = 1080;
    double screen_height = 960;

Q_SIGNALS:
    void themeChanged();
    void screenWidthChanged();
    void screenHeightChanged();
    // 向qml发送配置信息
    void signalSendConfig(QString key, QString value, int fileId);
    // 发送主机ip信息到qml
    void signalSendIpInfo(QString ip_address);
    // 发送版本号
    void signalSendVersionInfo(QString version_info);
    // qml验证登录状态
    void signalCheckLoginStatus(QString ley, QString value);
    // back to the login page
    void backToLogin();
    // 向qml发送登录信息
    void sendLoginInfo(QString username, QString token, QString openId);
    // 清空原来的收藏夹数据
    void clearFavorites();
    // 展示用户收藏的目标位置
    void sendFavorites(QString address, const double lontitude, const double latitude);
    // 返回车辆信息
    void notifyVehicleInfo(QString vehicleName, QString openId, QString plateNumber);

public Q_SLOTS:
    /** 执行基础设置shell命令
     * @param mode 当前模式：1：音量调节，2：亮度调节
     * @param value 当前值
     */
    void executeShellCmd(int mode, int value);

    /** 退出用户登录，并清除用户数据
     */
    void logout();

    void onNotifyVehicleToken(QString token);

    void onNotifyVehicleInfo(QString vehicleName, QString openId, QString plateNumber);
    
public:
    CMsgType m_eMsgType;
    //日期
    QString m_curDate;
    std::shared_ptr<LoginInfo> m_loginInfo;
    // 目标点集合
    std::map<QString, Point> targetMap;
    std::vector<Point> targetVec;
};

typedef Singleton<ConfigManager> SingletonConfigManager;

#endif // CONFIGMANAGER_H
