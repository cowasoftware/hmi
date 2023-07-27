import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtWebView 1.15
import WorkClass 1.0
import ConfigClass 1.0
import UpgradeMgrClass 1.0
// import App.RtspPlayer 1.0
import Cowa.HMI2.Plugins 1.0
import Cowa.HMI2.VModel 1.0

Window {
    id: window
    width: 1920
    height: 1080
    visible: true
    visibility : Window.FullScreen
    color: "#1d1d1d"

    // 实例化GlobalConfig
    GlobalConfig {
        id: gConfig
    }

    Loader{
        anchors.left: parent.left
        anchors.right: routePanel.left
        height: parent.height
        source: "qrc:///resource/qml/autodrive/autodrive.qml"
        Component.onCompleted: console.info(width,height)
    }

    Loader{
        id: routePanel
        width:  visible ? 376 : 0
        height: parent.height
        anchors.right: parent.right
        source: "qrc:/resource/qml/features/RealtimeRoute.qml"
        visible: ApplicationInfoVModel.vehicle === ApplicationInfoVModel.MiniBusVehicle && ApplicationInfoVModel.showRoute
    }
}
