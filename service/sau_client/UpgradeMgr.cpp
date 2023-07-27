#include "UpgradeMgr.h"
#include "QQmlContext"
#include "QQuickView"
#include <QDebug>
#include <iostream>
#include <string>
// #include <unistd.h>

#define LOGGER GetLogMgr().getLogger()

UpgradeMgr::UpgradeMgr(QObject *parent) : QObject{parent} {
  // TODO url为Tbox服务端的ip地址
  cmd_server_url = "tcp://192.168.1.1:9529";
}

inline CLogMgr& UpgradeMgr::GetLogMgr() {
  static CLogMgr my_logger("MAPP", "MCON", E_FUNC_LINE, DLT);
  return my_logger;
}

UpgradeMgr& UpgradeMgr::getInstance() {
  static UpgradeMgr s_upgradeMgr;
  return s_upgradeMgr;
}

void UpgradeMgr::init() {
  try
  {
    m_ZmqClient = std::make_unique<ZmqClient>(
    cmd_server_url, [this](const std::string &msg) { handle_callback(msg); });
    // TODO 需要服务端提供url
    m_zmqMonitorCb = std::bind(&UpgradeMgr::client_monitor,this,std::placeholders::_1,
    std::placeholders::_2);
    m_ZmqClient->set_monitor_callback(m_zmqMonitorCb); 
    bool connected = m_ZmqClient->connect(); 
    LOGGER->Cowa_Info(("connect to server, result = " + std::to_string(connected)).c_str());
  }
  catch(const std::exception& e)
  {
    LOGGER->Cowa_Error(e.what());
  }
  
}

void UpgradeMgr::handle_callback(const std::string &msg) {
  Command cmd;
  if (!cmd.ParseFromString(msg)) {
    LOGGER->Cowa_Warn("proto parse command failed!");
    return;
  }
  std::string out_msg = "";
  out_msg.append("receive msg from server, CmdId = ").append(std::to_string(cmd.id()))
         .append(", device = ").append(cmd.device())
         .append(", module = ").append(cmd.module())
         .append(", data = ").append(cmd.data());
  LOGGER->Cowa_Info(out_msg.c_str());
  switch (cmd.id()) {
  case CMD_ID_NOTIFY_DOWNLOAD_VERSIONS:
    // 主升级程序向hmi通知有新版本，是否需要升�?
    push_data_to_hmi(cmd.data());
    break;
  case CMD_ID_REQ_DOWNLOAD_VERSIONS:
    //请求升级下载信息
    // send_data_to_hmi(cmd.data());
    break;
  case CMD_ID_CONFIRM_INSTALL:
    // hmi确认是否需要升�?
    // TODO 通知服务端开始升级，hmi先不做处�?
    LOGGER->Cowa_Info("notify server to install. ");
    break;
  default:
    LOGGER->Cowa_Warn("unknown command!");
    break;
  }
}

bool UpgradeMgr::request_identify() {
  // 1、构造请求结构Command
  // CmdId: CMD_ID_NOTIFY_IDENTITY, device: "cm4", module: "tboxhmi"
  Command cmd = create_command(CMD_ID_NOTIFY_IDENTITY, "cm4", "tboxhmi", "");
  // 2、序列化为string类型
  std::string str_msg = cmd.SerializeAsString();
  // 3、通过ZmqClient.send()发送msg
  bool result = m_ZmqClient->send(str_msg);
  LOGGER->Cowa_Info(("send identify to server, result = " + std::to_string(result)).c_str());
  return result;
}

Command UpgradeMgr::create_command(const CmdId& id, const std::string& device, const std::string& module, const std::string& data) {
  std::string out_msg = "";
  out_msg.append("create command, id = ").append(std::to_string(id))
         .append(", device = ").append(device)
         .append(", module = ").append(module)
         .append(", data = ").append(data);
  LOGGER->Cowa_Info(out_msg.c_str());
  Command cmd;
  cmd.set_id(id);
  cmd.set_device(device);
  cmd.set_module(module);
  cmd.set_data(data);
  return cmd;
}

void UpgradeMgr::push_data_to_hmi(const std::string &data) {
  // 1、解析接收到的数�?
  InstallPackages install_pkgs;
  int pkgs_size = 0;
  std::shared_ptr<VersionInfo> info;
  install_pkgs.ParseFromString(data);
  // 大包当前版本
  QString curr_version = QString::fromStdString(install_pkgs.version_cur());
  // 大包最新版�?
  QString new_version = QString::fromStdString(install_pkgs.version_new());
  Q_EMIT signalNotifyMajorVersionInfo(curr_version, new_version);
  // 待升级的包数�?
  pkgs_size = install_pkgs.pkgs_size();
  LOGGER->Cowa_Info(("push data to hmi, pkgs_size = " + std::to_string(pkgs_size)).c_str());
  // 清空list
  pkgs_list.clear();
  // 2、数据存入list�?
  for (int i = 0; i < pkgs_size; i++) {
    info = std::make_shared<VersionInfo>();
    PackageUpdate updates = install_pkgs.pkgs(i);
    info->name = QString::fromStdString(updates.name());
    info->old_version = QString::fromStdString(updates.old_version());
    info->new_version = QString::fromStdString(updates.new_version());
    std::string out_msg = "";
    out_msg.append("updates.name: ").append(updates.name())
           .append(", updates.old_version: ").append(updates.old_version())
           .append(", updates.new_version: ").append(updates.new_version());
    LOGGER->Cowa_Info(out_msg.c_str());
    // 重复数据处理，相同应用，相同版本不在HMI显示，不升级
    // if(!hasContains(info->name, info->old_version, info->new_version)) {
    //   pkgs_list.push_back(info);
    // }
    pkgs_list.push_back(info);
  }
  // 更新UI�?
  update_hmi_ui();
  // 3、显示安装结果：升级中、升级成功、升级失�?
  InstallState state = install_pkgs.state();
  Q_EMIT signalNotifyUpgradeStatus(state);
}

// QString UpgradeMgr::StateToString(const InstallState& state) {
//   QString q_state_str;
//   qint32 q_state;
//   switch(state) {
//     case INSTALL_STATE_NORMAL:
//       // 安装前的状�?
//       LOGGER->Cowa_Info("INSTALL_STATE_NORMAL");
//       break;
//     case INSTALL_STATE_PROCESSING:
//       // 正在安装�?
//       LOGGER->Cowa_Info("INSTALL_STATE_PROCESSING");
//       // q_state_str = "版本正在升级�?... ";
//       q_state = INSTALL_STATE_PROCESSING;
//       break;
//     case INSTALL_STATE_FINISH:
//       // 安装成功
//       LOGGER->Cowa_Info("INSTALL_STATE_FINISH");
//       // q_state_str = "升级成功�?";
//       q_state = INSTALL_STATE_FINISH;
//       break;
//     case INSTALL_STATE_ERROR:
//       // 安装失败
//       LOGGER->Cowa_Info("INSTALL_STATE_ERROR");
//       // q_state_str = "升级失败�?";
//       q_state = INSTALL_STATE_ERROR;
//       break;
//     case INSTALL_STATE_UNKNOW:
//       // 未知状�?
//       // q_state_str = "未知错误�?";
//       q_state = INSTALL_STATE_UNKNOW;
//       LOGGER->Cowa_Info("INSTALL_STATE_UNKNOW");
//       break;
//     default:
//       break;
//   }
//   return q_state_str;
// }

void UpgradeMgr::update_hmi_ui() {
  std::list<std::shared_ptr<VersionInfo>>::iterator it;
  // 先通知hmi端清空旧数据
  Q_EMIT signalClearData();
  for (it = pkgs_list.begin(); it != pkgs_list.end(); it++)
  {
    std::shared_ptr<VersionInfo> info = *it;
    // 将数据主动推送到qml�?
    Q_EMIT signalNotifyPkgInfo(info->name, info->old_version, info->new_version);
  }
}

bool UpgradeMgr::req_server() {
  // 1、构造请求结构Command
  // CmdId：CMD_ID_REQ_DOWNLOAD_VERSIONS，请求升级下载信�?
  // device: "cm4"
  // module: "tboxhmi"
  // data�?"
  Command cmd = create_command(CMD_ID_REQ_DOWNLOAD_VERSIONS, "cm4", "tboxhmi", "");
  // 2、序列化为string类型
  std::string str_msg = cmd.SerializeAsString();
  // 3、通过ZmqClient.send()发送msg
  bool result = m_ZmqClient->send(str_msg);
  LOGGER->Cowa_Info(("send request to server, result = " + std::to_string(result)).c_str());
  // TODO 使用假数据测试去�?
  // push_mock_data();
  return result;
}

void UpgradeMgr::push_mock_data() {
  std::cout << "push mock data." << std::endl;
  int size = 3;
  std::shared_ptr<VersionInfo> info = std::make_shared<VersionInfo>();
  info->name = QString::fromStdString("sau");
  info->old_version = QString::fromStdString("V1.0.1");
  info->new_version = QString::fromStdString("V1.0.1");
  if(addOrUpdateList(info->name, info->old_version, info->new_version)) {
      pkgs_list.push_back(info);
  }
  for (int i = 0; i < size; i++) {
    std::shared_ptr<VersionInfo> info = std::make_shared<VersionInfo>();
    info->name = QString::fromStdString("hmi_" + std::to_string(i));
    info->old_version = QString::fromStdString("V1.0." + std::to_string(i));
    info->new_version = QString::fromStdString("V2.0." + std::to_string(i));
    std::string out_msg = "";
    out_msg.append("name: ").append(info->name.toStdString())
           .append(", old_version: ").append(info->old_version.toStdString())
           .append(", new_version: ").append(info->new_version.toStdString());
    LOGGER->Cowa_Info(out_msg.c_str());
    if(addOrUpdateList(info->name, info->old_version, info->new_version)) {
      pkgs_list.push_back(info);
    }
  }
  update_hmi_ui();
  // 间隔发送信�?
  // sleep(3);
}

bool UpgradeMgr::addOrUpdateList(QString &name, QString &oldVersion, QString &newVersion) {
  std::list<std::shared_ptr<VersionInfo>>::iterator it;
  for (it = pkgs_list.begin(); it != pkgs_list.end(); it++)
  {
    std::shared_ptr<VersionInfo> info = *it;
    if(info->name == name) {
      info->old_version = oldVersion;
      info->new_version = newVersion;
      info->old_version.toStdString();
      std::string out_msg = "";
      // out_msg.append("*****old info******: ").append("old_version: ").append(info->old_version.toStdString())
      //      .append(", new_version: ").append(info->new_version.toStdString());
      // out_msg.append("*****new info******: ").append("now_old_version: ").append(oldVersion.toStdString())
      //      .append(", now_new_version: ").append(newVersion.toStdString());
      LOGGER->Cowa_Info("更新数据");
      return false;
    }
  }
  return true;
}

bool UpgradeMgr::notify_server() {
  // 1、构造请求结构Command
  // CmdId：CMD_ID_CONFIRM_INSTALL，hmi确认是否需要升�?
  // device: "cm4"
  // module: "tboxhmi"
  // data：InstallNotify
  InstallNotify install_notify;
  install_notify.set_update(1);
  Command cmd = create_command(CMD_ID_CONFIRM_INSTALL, "cm4", "tboxhmi", install_notify.SerializeAsString());
  // 2、序列化为string类型
  std::string str_msg = cmd.SerializeAsString();
  // 3、通过ZmqClient.send()发送msg
  bool result = m_ZmqClient->send(str_msg);
  LOGGER->Cowa_Info(("notify server to install, result = " + std::to_string(result)).c_str());
  // TODO 模拟服务端的回调结果
  // if(result) {
  //   // 通知hmi端升级状�?
  //   signalNotifyUpgradeStatus(2);
  // }
  return result;
}

void UpgradeMgr::client_monitor(int events, const char *addr) {
  bool connected;
  switch (events)
  {
  case ZMQ_EVENT_CONNECTED:
    // 连接成功，则发送认证信�?
    connected = request_identify();
    if(connected) {
      LOGGER->Cowa_Info("identify success. ");
    } else {
      LOGGER->Cowa_Warn("identify failed, please try again!");
    }
    break;
  case ZMQ_EVENT_DISCONNECTED: 
    // 未连接，则重新连�?
    LOGGER->Cowa_Warn("failed to connect to server, please try again!");
    // m_ZmqClient->connect();
    break;
  case ZMQ_EVENT_CLOSED:
    LOGGER->Cowa_Warn("monitor is closed, please try again!");
    // 关闭连接
    // m_ZmqClient->stop();
    break;
  default:
    LOGGER->Cowa_Warn("undefined event!");
    break;
  }
}

std::list<std::shared_ptr<VersionInfo>> UpgradeMgr::getPackageLists() {
  return pkgs_list;
}

void UpgradeMgr::destroy() {
    if(m_ZmqClient->connected()) {
      m_ZmqClient->stop();
    }
}