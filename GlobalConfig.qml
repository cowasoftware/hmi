import QtQuick 2.0
import ConfigClass 1.0
// import LevelDBConfigClass 1.0


// TODO 全局主题配置，前者为浅色背景，后者为深色背景
QtObject {
    id: gConfigId
    property var titleBackground: ["#F1F1F1", "#4F4F4F"]   //标题栏的背景色
    property var background: ["#FFFFFF", "#2B2B2B"]        //背景色
    property var tabItemColor: ["#F6F6F6", "#323232"]   // 左侧菜单栏背景色
    property var slide_checked_bg: ["#5B89FF", "#F8F8F8"]  // slide选中部分的颜色
    property var slide_unchecked_bg: ["#BDBDBD", "#6D6D6D"]  // slide未选中部分的颜色
    property var reserverColor: ["#ffffff"]     //与背景色相反的对比色
    property var textColor: ["#333333", "#FFFFFF"]           //文本颜色
    property var buttonColor: ["#666666", "#FFFFFF"]  // 按钮颜色
    property var timeColor: ["#666666", "#FFFFFF"]      // 时间颜色
    property var tabButtonColor: ["#F5F5F5", "#3B3B3B"]     // 每个tab按钮颜色
    property var tabColor: ["#FFFFFF", "#2B2B2B"]      // 每个tab背景颜色
    property var topButtonColor: ["#BDBDBD", "#3B3B3B"]      // 上装调试页面每个tab按钮颜色
    property var carSettingButtonColor: ["#E9E9E9", "#4F4F4F"]      // 车辆设置页面每个tab按钮颜色
    property var statusBarColor: Qt.rgba(0,0,0,0.0)
    property var theme: ConfigManager.theme
    property real screen_width: ConfigManager.screenWidth
    property real screen_height: ConfigManager.screenHeight
    property real resolution_ratio: screen_width / screen_height
    property var debugOnButtonColor: ["#4F4F4F", "#5B89FF"]
    property var debugOffButtonColor: ["#5B89FF", "#4F4F4F"]
    property var selectedColor: "#5B89FF"

    property int currentIndex: 1
    // 当前保养里程
    property int currentMileage: 0
    // 媒体音量
    property real mediaVolume: 0.2
    // 通知音量
    property real notificationVolume: 0.3
    // 车辆音量
    property real verhicleVolume: 0.5
    // 当前亮度
    property real currentBrightness: 0.3
    property int fileId: 0
    property var host_address : "0.0.0.0" // 主机ip地址信息
    property var version_info : "0.0.0" // 主机版本信息

    property var debug_key: "enable_debug"
    property var debugEnable: 0    // 调试按钮默认不显示，仅在配置文件中开启时显示，0：关闭，1：开启
    property var debug_mode_desc: ["工程模式未开启！","工程模式已开启！"]

    signal qmlSignalFlushUI(int index) // 切换模式时刷新UI界面
    signal qmlSignalSaveConfig(string key, string value, int fileId)    // 保存配置信息的信号

    onCurrentIndexChanged: {
        // console.log("index发生了改变：" ,currentIndex)
        qmlSignalFlushUI(currentIndex)
        // currentIndex发生改变时，触发信号
        qmlSignalSaveConfig("index", currentIndex, fileId)
    }

    onDebugEnableChanged: {
        
    }

}
