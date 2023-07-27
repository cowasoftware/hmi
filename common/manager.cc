#include "manager.h"
#include "Util.h"
#include "LevelDBManager.h"
#include "UIDataHandle.h"
#include "UIBarHandle.h"
#include "UpgradeMgr.h"
#include "ConfigManager.h"
#include "DataManager.h"
#include "RtspPlayer.h"
#include "CoordinateUtil.h"
#include "autodrive_item.h"
#include "TrafficLightType.h"
#include "ConfigConstants.h"
#include "context.h"
#include "autodrive_item.h"
#include "autodrive_item2.h"
#include "fps_text.h"
#include "AduProxy.h"
#include "network_manager.h"
#include "CWidgetManager.h"
#include "realtime_route_model.h"
#include "application_info_vmodel.h"

// extern Context context;

Manager::Manager() {

}

Manager::~Manager() {

}

Manager& Manager::getInstance() {
    static Manager s_manager;
    return s_manager;
}

void Manager::init() {
    initService();
    initConfigInfo();
    initQmlRegister();
}

void Manager::initService() {
    //持久化存储类初始�???
    LevelDBManager::instance().openDBFile(Util::GetCurrentExePath() + "savetboxhmi.db");
    //加载点云
    DataManager::instance().loadObjectPointList(10);
    SingletonCUIDataHandle::getInstance()->init();
    SingletonCUIBarHandle::getInstance()->init();
    SingletonUpgradeMgr::getInstance()->init();
}

void Manager::initConfigInfo() {
    // TODO 模拟服务端推�???    
    // SingletonUpgradeMgr::getInstance()->push_mock_data();

    // 1、读取上次保存的黑白模式配置信息
    // key: "index", value: default 1, FILE_ID: default 0
    std::string index_value = "1";
    bool result = SingletonConfigManager::getInstance()->getConfigFromDB(INDEX, index_value, FILE_ID);
    // 2、将读取到的配置信息发送给qml
    // 读取上次保存的保养里程信�???
    // key: "mileage", value: default 0, FILE_ID: default 0
    std::string mileage_value = "0";
    SingletonConfigManager::getInstance()->getConfigFromDB(MILEAGE, mileage_value, FILE_ID);

    // 读取上次保存的音量信�???
    // key: "mediaVolume", value: default 0.2, FILE_ID: default 0
    std::string media_volume = "0.2";
    SingletonConfigManager::getInstance()->getConfigFromDB(MEDIA_VOLUME, media_volume, FILE_ID);
    std::string notification_volume = "0.3";
    SingletonConfigManager::getInstance()->getConfigFromDB(NOTIFICATION_VOLUME, notification_volume, FILE_ID);
    std::string verhicle_volume = "0.5";
    SingletonConfigManager::getInstance()->getConfigFromDB(VERHICLE_VOLUME, verhicle_volume, FILE_ID);

    // 读取上次保存的亮度信�???
    // key: "brightness", value: default 0.3, FILE_ID: default 0
    std::string brightness_value = "0.3";
    SingletonConfigManager::getInstance()->getConfigFromDB(BRIGHTNESS, brightness_value, FILE_ID);
    // 获取工程模式状态
    std::string debug_enable_value = "0";
    SingletonConfigManager::getInstance()->getConfigFromDB(DEBUG_ENABLE, debug_enable_value, FILE_ID);

    // 获取主机信息
    SingletonConfigManager::getInstance()->getLocalIpWithQt();

}

void Manager::initQmlRegister() {
    qmlRegisterType<AutodriveItem>("Cowa.HMI2.Plugins", 1, 0, "AutodriveItem");
    qmlRegisterType<AutodriveItem2>("Cowa.HMI2.Plugins", 1, 0, "AutodriveItem2");
    qmlRegisterType<RealtimeRouteModel>("Cowa.HMI2.Model", 1, 0, "RealtimeRouteModel");
    qmlRegisterType<FPSText>("Cowa.HMI2.Plugins", 1, 0, "FPSText");
    qmlRegisterSingletonInstance("WorkClass", 1, 0, "CUIDataHandle", SingletonCUIDataHandle::getInstance());
    qmlRegisterSingletonInstance("BarClass", 1, 0, "CUIBarHandle", SingletonCUIBarHandle::getInstance());
    qmlRegisterSingletonInstance("ConfigClass", 1, 0, "ConfigManager", SingletonConfigManager::getInstance());
    qmlRegisterSingletonInstance("LevelDBConfigClass", 1, 0, "LevelDBManager", &LevelDBManager::instance());
    qmlRegisterSingletonInstance("UpgradeMgrClass", 1, 0, "UpgradeMgr", SingletonUpgradeMgr::getInstance());
    qmlRegisterSingletonInstance<ApplicationInfoVModel>("Cowa.HMI2.VModel", 1, 0, "ApplicationInfoVModel", new ApplicationInfoVModel());
    // 注册ConverterUtil
    qmlRegisterSingletonInstance("CoordinateUtilClass", 1, 0, "CoordinateUtil", SingletonCoordinateUtil::getInstance());
    // 注册RtspPlayer
    qRegisterMetaType<std::string>("std::string");//注册新类�???
    qmlRegisterType<RtspPlayer>("App.RtspPlayer", 1, 0, "RtspPlayer");
    qmlRegisterType<TrafficLightEnum>("TrafficLightTypeEnum", 1, 0, "TrafficLightEnum");
    qmlRegisterType<DrivingModeEnum>("TrafficLightTypeEnum", 1, 0, "DrivingModeEnum");
    qmlRegisterSingletonInstance("CAduProxyClass", 1, 0, "CAduProxy", SingletonCAduProxy::getInstance());
    // qmlRegisterSingletonInstance("App.RtspPlayer", 1, 0, "RtspPlayer", SingletonRtspPlayer::getInstance());
    // qRegisterMetaType<QString>("QString");
    qmlRegisterSingletonInstance("Cowa.NetworkPlugin", 1, 0, "NetworkManager", &NetworkManager::instance());
    //注册组件类
    CWidgetManager::getInstance().registerWidget();
}

void Manager::handleExceptionOp() {
    // 车辆上电时，处理登录异常
    std::shared_ptr<LoginInfo> loginInfo = SingletonConfigManager::getInstance()->getLoginInfo();
    if(loginInfo != NULL) {
        if(loginInfo->login_status == STATUS_ONLINE) {
            // 退出上次登录帐号
            std::cout << "The user is offline abnormally and has not logout!!!" << std::endl;
            SingletonConfigManager::getInstance()->autoLogout(loginInfo);
        }
    }
}

void Manager::destroy() {
    SingletonCUIDataHandle::getInstance()->destroy();
    LevelDBManager::instance().closeDBFile();
    SingletonUpgradeMgr::getInstance()->destroy();
    // SingletonCAduProxy::getInstance()->destroy();
}
