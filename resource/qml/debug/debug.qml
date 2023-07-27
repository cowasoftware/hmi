import QtQuick 2.0
import QtGraphicalEffects 1.15

// debug: first level
// 调试页面的 以及一级
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
    property var crmonitor_icon: ["qrc:///resource/asset/image/debug/dark/crmonitor.png", "qrc:///resource/asset/image/debug/light/crmonitor.png"]
    property var camera_icon: ["qrc:///resource/asset/image/debug/dark/camera-debugging.png", "qrc:///resource/asset/image/debug/light/camera-debugging.png"]
    property var wifi_icon: ["qrc:///resource/asset/image/debug/dark/wifi.png", "qrc:///resource/asset/image/debug/light/wifi.png"]
    property var module_status_icon: ["qrc:///resource/asset/image/debug/dark/module-status.png", "qrc:///resource/asset/image/debug/light/module-status.png"]

    Rectangle {
        width: 324
        height: 960
        // color: "#323232"
        color: gConfig.tabItemColor[currentIndex]

        Column {
            id: debug_column_id
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
                    {state:"crmonitor", content_qml:"qrc:///resource/qml/debug/crmonitor.qml", icon_source: crmonitor_icon, text:qsTr("crmonitor")},
                    {state:"camera", content_qml:"qrc:///resource/qml/debug/camera.qml", icon_source: camera_icon, text:qsTr("相机调试")},
                    {state:"wifi", content_qml:"qrc:///resource/qml/debug/wifi.qml", icon_source: wifi_icon, text:qsTr("WIFI")},
                    {state:"module_status", content_qml:"qrc:///resource/qml/debug/module_status.qml", icon_source: module_status_icon, text:qsTr("模块状态")},
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
                            if (debug_column_id.last_select_item_id != item_setting_id) {
                                item_setting_id.color = gConfig.tabItemColor[index];
                                // item_setting_id.wifi_image_id.source = modelData.icon_source
                            }
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
                            if (debug_column_id.last_select_item_id != item_setting_id) {
                                if (debug_column_id.last_select_item_id != null) {
                                    // 修改上一个选中的颜色
                                    // debug_column_id.last_select_item_id.color = "#323232"
                                    debug_column_id.last_select_item_id.color = currentBgColor
                                    debug_column_id.last_select_item_border_id.sourceComponent = undefined
                                }
                                debug_column_id.last_select_item_id = item_setting_id
                                debug_column_id.last_select_item_border_id = border_linear_loader_id
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
