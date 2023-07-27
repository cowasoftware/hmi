#ifndef UPGRADEMGR_H
#define UPGRADEMGR_H

#include <QObject>
#include <QQmlListProperty>
#include "zmq_client.h"
#include "zmq_monitor.h"
#include "sau.pb.h"
#include "Singleton.h"
#include "VersionInfo.h"
#include "log.h"

using namespace cowa;
using namespace cowa::zmqex;
using namespace cowa::sau;
// using namespace COWA;
using namespace Cowa;
/** upgrade管理类
*/
class UpgradeMgr : public QObject
{
    Q_OBJECT

public:
    explicit UpgradeMgr(QObject *parent = nullptr);

    /**
     * @brief Get the Log Mgr object
     * @return CLogMgr& 
     */
    inline CLogMgr& GetLogMgr();

    /** 单一实例
	@return 返回单一实例
	*/
	static UpgradeMgr& getInstance();

    /**
     * @brief 初始化ZmqClient连接
     */
    void init();

    /**
     * @brief server端连接监听
     * @param events 
     * @param addr 
     */
    void client_monitor(int events,const char* addr);

    /**
     * @brief 模拟服务端推送新版本数据
     */
    void push_mock_data();

    /**
     * @brief 获取有新版本的安装包列表
     * @return Q_INVOKABLE 
     */
    Q_INVOKABLE std::list<std::shared_ptr<VersionInfo>> getPackageLists();

    void destroy();

private:
    /**
     * @brief 接收并处理来自zmqServer端的回调
     * @param msg 服务端回调的消息
     */
    void handle_callback(const std::string& msg);

    /**
     * @brief 向zmqServer请求身份认证
     * @return true   认证成功
     * @return false  认证失败
     */
    bool request_identify();

    /**
     * @brief 构造服务端的请求体Command结构
     * @param id        : CmdId
     * @param device    : 设备名
     * @param module    ：模块名
     * @param data      ：数据
     * @return Command& ：Command
     */
    Command create_command(const CmdId& id, const std::string& device, const std::string& module, const std::string& data);

    /**
     * @brief 通过推送方式，向hmi端推送数据
     * @param data 服务端推送的版本信息
     */
    void push_data_to_hmi(const std::string& data);

    /**
     * @brief 通过get-post方式，将数据发送到hmi端
     * @param data 服务端响应的版本信息
     */
    void send_data_to_hmi(const std::string& data);

    /** 更新HMI的UI端显示的数据
     */
    void update_hmi_ui();

    // /** 安装状态转为QString类型
    //  * @param state 
    //  * @return QString 
    //  */
    // QString StateToString(const InstallState& state);

    /** 新增或更新list中app为name的版本信息
     * @param name 应用名
     * @param oldVersion 旧版本
     * @param newVersion 新版本
     * @return true 新增
     * @return false 更新
     */
    bool addOrUpdateList(QString &name, QString &oldVersion, QString &newVersion);

Q_SIGNALS:

    /** 通知hmi端固件版本
     * @param curr_version 大包当前版本 
     * @param new_version 大包最新版本
     */
    void signalNotifyMajorVersionInfo(QString curr_version, QString new_version);

    /** 清空hmi端旧数据
     */
    void signalClearData();

    /** 服务端主动向hmi推送有新版本的数据
     * @param name 
     * @param old_version 
     * @param new_version 
     */
    void signalNotifyPkgInfo(QString name, QString old_version, QString new_version);

    /** 服务端响应hmi端的请求
     * @param name 
     * @param old_version 
     * @param new_version 
     */
    void signalSendPkgInfo(QString name, QString old_version, QString new_version);

    /** 服务端的数据封装为QList发送到qml
     * @param pkg_lists 
     */
    void signalSendPkgList(QList<VersionInfo> pkg_lists);

    /** 向hmi端展示升级状态
     * @param status 升级状态：升级中，升级完成
     */
    void signalNotifyUpgradeStatus(qint32 status);

public Q_SLOTS:
    /**
     * @brief 请求服务端数据
     * @return true    请求成功
     * @return false   请求失败
     */
    bool req_server();  

    /**
     * @brief 通知服务端确认升级
     * @return true 
     * @return false 
     */
    bool notify_server();

private:
    std::unique_ptr<ZmqClient>                  m_ZmqClient;
    ZmqMonitorCb                                m_zmqMonitorCb;
    std::list<std::shared_ptr<VersionInfo>>     pkgs_list;     //  所有待升级的包
    std::string                                 cmd_server_url; // 服务端url

};
typedef Singleton<UpgradeMgr> SingletonUpgradeMgr;

#endif // UPGRADEMGR_H
