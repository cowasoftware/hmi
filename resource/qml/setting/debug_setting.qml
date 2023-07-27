import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import ConfigClass 1.0


Rectangle {
    id: debug_setting_id
    width: 1446
    height: 960

    property int currentIndex: gConfig.currentIndex
    property var debug_mode_desc: gConfig.debug_mode_desc[gConfig.debugEnable]
    color: gConfig.background[currentIndex]

    Rectangle {
        id: debug_title_id
        x: 0
        y: 0
        width: parent.width
        height: 100
        color: gConfig.titleBackground[currentIndex]
        onColorChanged: {
        }
        Text {
            id: text1
            anchors.centerIn:parent
            width: 144
            height: 50
            color: gConfig.textColor[currentIndex]
            text: qsTr("工程模式")
            font.pixelSize: 36
            font.styleName: "Regular"
            horizontalAlignment : Text.AlignHCenter
        }
    }

    // 工程模式
    Rectangle {
        id: debug_rect_id
        width: parent.width
        height: 860
        y: 100
        // color: "#2b2b2b"
        // color: "#F15555"
        color: gConfig.background[currentIndex]
        Button {
            id: debug_off_id
            width: 120
            height: 60
            x: 60
            y: 40
            highlighted: false
            //设置按钮背景颜色
            background: Rectangle {
                id: debug_off_bg
                color: gConfig.debugOffButtonColor[gConfig.debugEnable]
                radius: 4
                Text{
                    text: qsTr("OFF")
                    anchors.centerIn: parent
                    font.pixelSize: 24
                    font.styleName: "Regular"
                    color: gConfig.textColor[currentIndex]
                }
            }
            onClicked: {
                debug_rect_id.enableDebugMode(false)
            }
        }

        Button {
            id: debug_on_id
            width: 120
            height: 60
            x: 180
            y: 40
            highlighted: false
            //设置按钮背景颜色
            background: Rectangle {
                id: debug_on_bg
                color: gConfig.debugOnButtonColor[gConfig.debugEnable]
                radius: 4
                Text{
                    text: qsTr("ON")
                    anchors.centerIn: parent
                    font.pixelSize: 24
                    font.styleName: "Regular"
                    color: gConfig.textColor[currentIndex]
                }
            }
            onClicked: {
                debug_rect_id.enableDebugMode(true)
            }
        }

        Text {
            id: debug_mode_desc_txt
            x: 994
            y: 40
            // width: 128
            // height: 45
            color: gConfig.textColor[currentIndex]
            text: qsTr(debug_mode_desc.toString())
            font.pixelSize: 32
            font.styleName: "Regular"
        }

        Loader {
            id: password_content_loader_id
            width: parent.width
            height: parent.height
            source: "qrc:///resource/qml/setting/password_box.qml"

            Connections {
                target: password_content_loader_id.item
                function onPasswordSuccess()
                {
                    console.log("password_component_loader_id onPasswordSuccess ")
                    password_content_loader_id.source=""
                }
            }
        }

        function enableDebugMode(enable) {
            if(enable == true) {
                console.log("开启工程模式")
                gConfig.debugEnable = 1
                debug_on_bg.color = gConfig.debugOnButtonColor[gConfig.debugEnable]
                debug_off_bg.color = gConfig.debugOffButtonColor[gConfig.debugEnable]
                ConfigManager.setConfigToDB(gConfig.debug_key, 1, gConfig.fileId)
            } else {
                console.log("关闭工程模式")
                gConfig.debugEnable = 0
                debug_off_bg.color = gConfig.debugOffButtonColor[gConfig.debugEnable]
                debug_on_bg.color = gConfig.debugOnButtonColor[gConfig.debugEnable]
                ConfigManager.setConfigToDB(gConfig.debug_key, 0, gConfig.fileId)
            }
        }
    }

}
