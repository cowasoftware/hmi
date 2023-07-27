#include <QDebug>
#include <QApplication>
#include <QGuiApplication>
#include <QMetaObject>
#include <QQmlApplicationEngine>
#include <QScreen>
#include <QtQml>
#include <QWindow>
#include <QtQuick/QQuickItem>
#include <QQuickView>
#include <log.h>
#include <QtWebEngine>
#include "Util.h"
#include "ConfigManager.h"
#include "UIBarHandle.h"
#include "UIDataHandle.h"
#include "context.h"
#include "manager.h"
#include "recv_curve_points_from_adu.h"
#include "subs_vehicle_info_from_adu.h"
#include "subs_filter_point_cloud_from_adu.h"
#include "recv_auto_drive_resp_from_adu.h"
#include "MapConfig.h"

#define LOGGER GetLogMgr().getLogger()
Context context;

MapConfig g_config;

void handleSignal(int signum)
{
    // if (signum == SIGINT || signum == SIGTERM) {
    //     isStoped = true;
    //     std::cout << "ctrl+c or ctrl+d pressed!" << std::endl;
    //     mZmqSubIF.stop();
    //     std::cout << " mZmqSubIF.stop() has been executed!" << std::endl;
    //     mZmqReqIF.stop();
    //     std::cout << " mZmqReqIF.stop() has been executed!" << std::endl;
    //     mCondition.notify_one();
    //     exit(1);
    // }
}

inline CLogMgr& GetLogMgr() {
  static CLogMgr my_logger("MAPP", "MCON", E_FUNC_LINE, CONSOLE );
  return my_logger;
}

void printVersionInfo() {
    LOGGER->Cowa_Info("/********************************** hmi version info *********************/");
    std::string version = SingletonConfigManager::getInstance()->getBuildVersion();
    std::string buildTime = SingletonConfigManager::getInstance()->getBuildTime();
    std::string versionInfo = "[HMI_MAIN] hmi main in, version: " + version + " , build time: " + buildTime;
    LOGGER->Cowa_Info(versionInfo.c_str());
    LOGGER->Cowa_Info("/************************************************************************/");
}

int main(int argc, char* argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    // qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9025");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QtWebEngine::initialize();
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    auto currentExePath = Util::GetCurrentExePath();
	g_config.load(currentExePath + "autodrive.ini");

    // 初始化资源管理类
    Manager::getInstance().init();
    // 处理车辆异常情况
    Manager::getInstance().handleExceptionOp();

    //设置engine's root context属性，以便在qml里通过appDir获取文件目录
    engine.rootContext()->setContextProperty("appDir", qApp->applicationDirPath());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) { return -1; }

    //获取QMl的源对象
    QObject* qmlAppObj = engine.rootObjects().first();
    SingletonCUIDataHandle::getInstance()->loadLocalData();
    SingletonCUIBarHandle::getInstance()->setAppItem(qmlAppObj);
    SingletonCUIBarHandle::getInstance()->initData();
    printVersionInfo();

    // init listeners
    auto recv_vehicle_info_from_adu = std::make_shared<SubsVehicleInfoFromAdu>();
    context.add_base_info_subs_listener(recv_vehicle_info_from_adu);

    auto recv_filter_point_cloud_from_adu = std::make_shared<SubsFilterPointCloudFromAdu>();
    context.add_filter_point_cloud_subs_listener(recv_filter_point_cloud_from_adu);

    auto recv_curve_points_from_adu = std::make_shared<RecvCurvePointsFromAdu>();
    context.add_response_listener(TARGET_CURVE_TYPE, recv_curve_points_from_adu);

    auto recv_auto_drive_resp_from_adu = std::make_shared<RecvAutoDriveRespFromAdu>();
    context.add_response_listener(ENABLE_AUTO_DRIVE_TYPE, recv_auto_drive_resp_from_adu);


    app.exec();
    LOGGER->Cowa_Info("main test...");
    // ser.destroy();
    Manager::getInstance().destroy();
    return 0;
}