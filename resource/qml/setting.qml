import QtQuick 2.0
import QtGraphicalEffects 1.15

// setting: first level
// 设置页面的 以及一级
Row {
    width: 1770
    height: 960
    y: 60
    visible: true
    id: setting_id

    // signal qmlSignalFlushUI(int index) // 切换模式时刷新UI界面
    property string selected_button_color: "#5b89ff"
    property string unselected_button_color: "#323232"
    property string selected_border_color: "#"
    property var last_select_id : null
    property int currentIndex: gConfig.currentIndex
    property var currentBgColor: gConfig.tabItemColor[currentIndex]
    property var textColor: gConfig.textColor[currentIndex]
    property var basic_setting_icon: ["qrc:///resource/asset/image/setting_icon/basic_setting_light.png", "qrc:///resource/asset/image/setting_icon/basic_setting.png"]
    property var diagnosis_icon: ["qrc:///resource/asset/image/setting_icon/diagnosis_light.png", "qrc:///resource/asset/image/setting_icon/diagnosis.png"]
    property var top_debug_icon: ["qrc:///resource/asset/image/setting_icon/top_debug_light.png", "qrc:///resource/asset/image/setting_icon/top_debug.png"]
    property var vehicle_setting_icon: ["qrc:///resource/asset/image/setting_icon/car_light.png", "qrc:///resource/asset/image/setting_icon/car.png"]
    property var version_upgrade_icon: ["qrc:///resource/asset/image/setting_icon/upgrade_light.png", "qrc:///resource/asset/image/setting_icon/upgrade.png"]
    property var user_setting_icon: ["qrc:///resource/asset/image/setting_icon/user_setting_light.png", "qrc:///resource/asset/image/setting_icon/user_setting_dark.png"]
    property var debug_setting_icon: ["qrc:///resource/asset/image/setting_icon/debug_setting_light.png", "qrc:///resource/asset/image/setting_icon/debug_setting_dark.png"]

    Rectangle {
        width: 324
        height: 960
        // color: "#323232"
        color: gConfig.tabItemColor[currentIndex]

        Column {
            id: setting_column_id
            x: 0
            y: 0
            width: 324
            height: 960
            opacity: 1

            property var  last_select_item_id: null // 上一个选中的item
            property var  last_select_item_border_id: null // 上一个选中的item的边框效果
            Repeater {
                id : item_repeat_id
                model :
                    [
                    {state:"basicSetting", content_qml:"qrc:///resource/qml/setting/basic_setting.qml", icon_source: basic_setting_icon, text:qsTr("基础设置")},
                    {state:"diagnosis", content_qml:"qrc:///resource/qml/setting/diagnosis_information.qml", icon_source: diagnosis_icon, text:qsTr("诊断信息")},
                    {state:"topDebug", content_qml:"qrc:///resource/qml/setting/debug_password.qml", icon_source: top_debug_icon, text:qsTr("上装调试")},
                    {state:"car", content_qml:"qrc:///resource/qml/setting/vehicle_setting.qml", icon_source: vehicle_setting_icon, text:qsTr("车辆设置")},
                    {state:"upgrade",content_qml:"qrc:///resource/qml/setting/version_upgrade.qml", icon_source: version_upgrade_icon, text:qsTr("版本升级")},
                    {state:"userSetting",content_qml:"qrc:///resource/qml/setting/user_setting.qml", icon_source: user_setting_icon, text:qsTr("用户设置")},
                    {state:"debug",content_qml:"qrc:///resource/qml/setting/debug_setting.qml", icon_source: debug_setting_icon, text:qsTr("工程模式")},
                ]

                Rectangle {
                    id: item_setting_id
                    y: 0
                    width: 324
                    height: 96
                    // color: "#323232"
                    color: currentBgColor

                    Connections {
                        target: gConfig
                        function onQmlSignalFlushUI(index) {
                            console.log("item_setting_id: onQmlSignalFlushUI: index = " + index)
                            if (setting_column_id.last_select_item_id != item_setting_id) {
                                item_setting_id.color = gConfig.tabItemColor[index];
                                // item_setting_id.wifi_image_id.source = modelData.icon_source
                            }
                        }
                    }

                    Connections {
                        target: window
                        function onResetLogin() {
                            loader_setting_content_id.source = ""
                        }
                    }

                    MouseArea {
                        id: mouseArea
                        x: 0
                        y: 0
                        anchors.fill: parent
                        onClicked: {
                            item_setting_id.color = "#5b89ff" // item的颜色
                            border_linear_loader_id.sourceComponent = border_linear_id // item上下的渐变颜色效果
                            loader_setting_content_id.source  = modelData.content_qml // 右侧的内容

                            // 清除上一个选中的item
                            if (setting_column_id.last_select_item_id != item_setting_id) {
                                if (setting_column_id.last_select_item_id != null) {
                                    // 修改上一个选中的颜色
                                    // setting_column_id.last_select_item_id.color = "#323232"
                                    setting_column_id.last_select_item_id.color = currentBgColor
                                    setting_column_id.last_select_item_border_id.sourceComponent = undefined
                                }
                                setting_column_id.last_select_item_id = item_setting_id
                                setting_column_id.last_select_item_border_id = border_linear_loader_id
                            }
                            // to do
                        }
                        Image {
                            id: wifi_image_id
                            x: 44
                            y: 23
                            width: 50
                            height: 50
                            source: modelData.icon_source[currentIndex]
                            fillMode: Image.PreserveAspectFit
                        }
                        Text {
                            x: 118
                            y: 26
                            width: 200
                            height: 45
                            text: modelData.text
                            font.styleName: "Regular"
                            color: textColor
                            font.pixelSize: 32
                        }
                    }

                    Loader {
                        id: border_linear_loader_id
                        anchors.fill: parent
                        source: ""
                    }
                    Component {
                        id: border_linear_id
                        Item {
                            anchors.fill: parent
                            LinearGradient {
                                anchors.top : parent.top
                                width: item_setting_id.width
                                height: 5
                                start: Qt.point(0, 0)
                                end: Qt.point(width, 0)        ///1、横向渐变
                                gradient: Gradient {
                                    GradientStop {  position: 0.0;    color: "#5b89ff" }
                                    GradientStop {  position: 0.5;    color: "#52E0ff" }
                                    GradientStop {  position: 1.0;    color: "#5b89ff" }
                                }
                            }
                            LinearGradient {
                                anchors.bottom: parent.bottom
                                width: item_setting_id.width
                                height: 5
                                start: Qt.point(0, 0)
                                end: Qt.point(width, 0)        ///1、横向渐变
                                gradient: Gradient {
                                    GradientStop {  position: 0.0;    color: "#5b89ff" }
                                    GradientStop {  position: 0.5;    color: "#52E0ff" }
                                    GradientStop {  position: 1.0;    color: "#5b89ff" }
                                }
                            }
                        }
                    }
                }

            }

        }
    }
    

    Loader {
        id: loader_setting_content_id
        width: 1446
        height: 960
    }
}
