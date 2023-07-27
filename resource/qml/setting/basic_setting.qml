import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.15
import ConfigClass 1.0

/* 基础设置 */
Item {
    id: rootid
    width: 1446 * gConfig.resolution_ratio;
    height: 960 / gConfig.resolution_ratio;
    signal qmlSignalSetting(int mode, int value) // 基础设置信号，音量，亮度调节
    signal qmlSignalSaveConfig(string key, string value, int fileId) // 保存当前配置信息到levelDb
    property int currentIndex: gConfig.currentIndex
    property real currentBrightness: gConfig.currentBrightness
    property real mediaVolume: gConfig.mediaVolume
    property real notificationVolume: gConfig.notificationVolume
    property real verhicleVolume: gConfig.verhicleVolume
    property int fileId: 0  //  保存到levelDb的文件索引
    property var host_address: gConfig.host_address    // 主机ip地址
    property var version_info: gConfig.version_info //版本号

    // 基础设置
    Rectangle {
        id: top_rectangle
        width: 1446
        height: 90
        color: gConfig.titleBackground[gConfig.currentIndex]
        Text {
            id: basic_setting_title
            width: 126
            height: 45
            text: qsTr("基础设置")
            color: gConfig.textColor[gConfig.currentIndex]
            font.pixelSize: 32
            font.styleName: "Regular"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    // 音量设置
    Rectangle {
        id: left_rectangle
        width: 393
        height: 628
        // color: "#2B2B2B"
        color: gConfig.background[gConfig.currentIndex]
        anchors.top: top_rectangle.bottom
        Text {
            id: volume_setting
            width: 111
            height: 39
            x: 45
            y: 44
            text: qsTr("音量设置")
            color: gConfig.textColor[gConfig.currentIndex]
            font.pixelSize: 28
            font.styleName: "Regular"
        }

        Column {
            id: slider_column1
//            width: 360
//            height: 628
            anchors.top: volume_setting.bottom
            anchors.topMargin: 32

            spacing: 44
            Slider {
                id: volume_slider1
                property color checkedColor: "#F8F8F8"
                property real media_value: 0.2
                property real maxValue: 1.0

                width: 72
                height: 360
                x: 45
                value: mediaVolume
                orientation: Qt.Vertical
                snapMode: Slider.SnapAlways

                background: Rectangle {
                    id: _rect
                    width: 72
                    height: 360
                    radius: 15
                    // 在父组件中设置 layer 属性的 enabled 和 effect 子属性
                    layer.enabled: true
                    layer.effect: OpacityMask {
                        maskSource: Rectangle {
                            width: _rect.width
                            height: _rect.height
                            radius: _rect.radius
                        }
                    }

                    LinearGradient {
                        id : linear_gradient_id
                        anchors.fill : parent
                        start: Qt.point(0, 0)
                        end: Qt.point(0, height)        ///1、纵向渐变
                        gradient: Gradient {
                            GradientStop {  position: 0.0;    color: gConfig.slide_unchecked_bg[gConfig.currentIndex] }
                            GradientStop {  position: Math.max(0.00000001, volume_slider1.visualPosition);    color: gConfig.slide_unchecked_bg[gConfig.currentIndex] }
                            GradientStop {  position: Math.min(volume_slider1.visualPosition+0.0000001, 1);    color: gConfig.slide_checked_bg[gConfig.currentIndex] }
                            GradientStop {  position: 1.0;    color: gConfig.slide_checked_bg[gConfig.currentIndex] }
                        }
                    }
                }

                Rectangle {
                    width: 24
                    height: 24
                    x: 20
                    y: 314
                    color: Qt.rgba(0,0,0, 0.0) // 透明
                    Image {
                        id: media_volume
                        width:  24
                        height: 24
                        source: "qrc:/resource/asset/image/setting_icon/media.png"
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                handle: Item {
                    id: handle1
                }

                onValueChanged: {
                    // 发送执行shell命令的信号
                    rootid.qmlSignalSetting(TDMsgType.BasicSettingType.VOLUME_ADJUST, value * 100)
                    // 发送保存配置信息的信号
                    rootid.qmlSignalSaveConfig("mediaVolume", value, fileId)
                }
            }
        }

        Column {
            id: slider_column2
            anchors.left: slider_column1.right
            anchors.leftMargin: 44
            anchors.top: volume_setting.bottom
            anchors.topMargin: 32

                Slider {
                    id: volume_slider2
                    property color checkedColor: "#F8F8F8"
                    property real notification_value: 0.2
                    property real maxValue: 1.0
                    width: 72
                    height: 360
                    x: 44
                    value: notificationVolume
                    orientation: Qt.Vertical
                    snapMode: Slider.SnapAlways

                    background: Rectangle {
                        id: _rect2
                        width: 72
                        height: 360
                        radius: 15
                        // 在父组件中设置 layer 属性的 enabled 和 effect 子属性
                            layer.enabled: true
                            layer.effect: OpacityMask {
                                maskSource: Rectangle {
                                    width: _rect2.width
                                    height: _rect2.height
                                    radius: _rect2.radius
                                }
                            }

                        LinearGradient {
                            id : linear_gradient_id2
                            anchors.fill : parent
                            start: Qt.point(0, 0)
                            end: Qt.point(0, height)        ///1、纵向渐变
                            gradient: Gradient {
                                GradientStop {  position: 0.0;    color: gConfig.slide_unchecked_bg[gConfig.currentIndex] }
                                GradientStop {  position: Math.max(0.00000001, volume_slider2.visualPosition);    color: gConfig.slide_unchecked_bg[gConfig.currentIndex] }
                                GradientStop {  position: Math.min(volume_slider2.visualPosition+0.0000001, 1);    color: gConfig.slide_checked_bg[gConfig.currentIndex] }
                                GradientStop {  position: 1.0;    color: gConfig.slide_checked_bg[gConfig.currentIndex] }
                            }
                        }
                    }

                    Rectangle {
                        width: 24
                        height: 24
                        x: 20
                        y: 314
                        color: Qt.rgba(0,0,0, 0.0) // 透明
                        Image {
                            id: notification
                            width:  24
                            height: 24
                            source: "qrc:/resource/asset/image/setting_icon/notification.png"
                            fillMode: Image.PreserveAspectFit
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    handle: Item {
                        id: handle2
                    }

                    onValueChanged:
                    {
                        // 发送执行shell命令的信号
                        rootid.qmlSignalSetting(TDMsgType.BasicSettingType.VOLUME_ADJUST, value * 100)
                        // 发送保存配置信息的信号
                        rootid.qmlSignalSaveConfig("notificationVolume", value, fileId)
                    }
                }
            }

        Column {
            id: slider_column3
            anchors.left: slider_column2.right
            anchors.leftMargin: 44
            anchors.top: volume_setting.bottom
            anchors.topMargin: 32

                Slider {
                    id: volume_slider3
                    property color checkedColor: "#F8F8F8"
                    property real volume_value: 0.2
                    property real maxValue: 1.0
                    width: 72
                    height: 360
                    x: 44
                    value: verhicleVolume
                    orientation: Qt.Vertical

                    background: Rectangle {
                        id: _rect3
                        width: 72
                        height: 360
                        radius: 15
                        anchors.fill : parent

                        // 在父组件中设置 layer 属性的 enabled 和 effect 子属性
                            layer.enabled: true
                            layer.effect: OpacityMask {
                                maskSource: Rectangle {
                                    width: _rect3.width
                                    height: _rect3.height
                                    radius: _rect3.radius
                                }
                            }

                            LinearGradient {
                                id : linear_gradient_id3
                                anchors.fill : parent
                                start: Qt.point(0, 0)
                                end: Qt.point(0, height)        ///1、纵向渐变
                                gradient: Gradient {
                                    GradientStop {  position: 0.0;    color: gConfig.slide_unchecked_bg[gConfig.currentIndex] }
                                    GradientStop {  position: Math.max(0.00000001, volume_slider3.visualPosition);    color: gConfig.slide_unchecked_bg[gConfig.currentIndex] }
                                    GradientStop {  position: Math.min(volume_slider3.visualPosition+0.0000001, 1);    color: gConfig.slide_checked_bg[gConfig.currentIndex] }
                                    GradientStop {  position: 1.0;    color: gConfig.slide_checked_bg[gConfig.currentIndex] }
                                }
                            }
                    }

                    Rectangle {
                        width: 24
                        height: 24
                        x: 20
                        y: 314
                        color: Qt.rgba(0,0,0, 0.0) // 透明
                        Image {
                            id: car_volumn
                            width:  24
                            height: 24
                            source: "qrc:/resource/asset/image/setting_icon/car_volumn.png"
                            fillMode: Image.PreserveAspectFit
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    handle: Item {
                        id: handle3
                    }

                    onValueChanged:
                    {
                        // 发送执行shell命令的信号
                        rootid.qmlSignalSetting(TDMsgType.BasicSettingType.VOLUME_ADJUST, value * 100)
                        // 发送保存配置信息的信号
                        rootid.qmlSignalSaveConfig("verhicleVolume", value, fileId)
                    }
                }
            }

        // 静音
        Rectangle {
            id: volume_icon
            width: 72
            height: 72
            color: "#5B89FF"
            x: 45
            y: 508
            radius: 15
            //
            Image {
                width:  29
                height: 32
                x: 21
                y: 20
                source: "qrc:/resource/asset/image/setting_icon/mute.png"
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        /* 静音模式 */
        Rectangle {
            id: stop_volume_model
            width: 208
            height: 72
            color: "#BDBDBD"
            x: 141
            y: 508
            radius: 15
            Text {
                id: stop_text
                width: 95
                height: 34
                x: 56
                y: 18
                text: qsTr("静音模式")
                color: gConfig.buttonColor[gConfig.currentIndex]
                font.pixelSize: 24
                font.styleName: "Regular"
            }

            MouseArea  {
                 anchors.fill:  parent
                 onClicked:  {
                     stop_volume_model.state  ==  'selected'  ?  stop_volume_model.state  =  ""  :  stop_volume_model.state  =  'selected';
                     if(stop_volume_model.state  ==  'selected') {
                            stop_text.color = "#FFFFFF"
                     }
                 }
             }
            states: [
                State {
                    name: "selected"
                    PropertyChanges {
                        target: stop_volume_model
                        color: "#5B89FF"
                    }
                }
            ]
        }
    }

    // 亮度设置
    Rectangle {
        id: right_rectangle
        width: 1041
        height: 628
        // color: "#2B2B2B"
        color: gConfig.background[gConfig.currentIndex]
        anchors.top: top_rectangle.bottom
        anchors.left: left_rectangle.right
        anchors.leftMargin: 12

        Text {
            id: brightness
            width: 111
            height: 39
            x: 45
            y: 44
            text: qsTr("亮度设置")
            color: gConfig.textColor[gConfig.currentIndex]
            font.pixelSize: 28
            font.styleName: "Regular"
        }

        // 亮度调节
        Item {
            id: brightness_row

            Rectangle {
                id: brightness_icon
                width: 72
                height: 72
                color: "#5B89FF"
                x: 44
                y: 116
                radius: 15
                Image {
                    width:  32
                    height: 32
                    source: "qrc:/resource/asset/image/setting_icon/luminance.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Slider {
                id: brightness_slider
                property color checkedColor: "#F8F8F8"
                property real initValue: currentBrightness
                property real maxValue: 1
                width: 360
                height: 72
                anchors.left:brightness_icon.right
                anchors.leftMargin: 24
                anchors.top: brightness_icon.top
                value: initValue

                background: Rectangle {
                    id: bright_rect
                    width: 360
                    height: 72
                    radius: 15
                    // 在父组件中设置 layer 属性的 enabled 和 effect 子属性
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: Rectangle {
                                width: bright_rect.width
                                height: bright_rect.height
                                radius: bright_rect.radius
                            }
                        }

                        LinearGradient {
                            id : light_linear_gradient
                            anchors.fill : parent
                            start: Qt.point(0, 0)
                            end: Qt.point(width, 0)        ///1、横向渐变
                            gradient: Gradient {
                                GradientStop {  position: 0.0;    color: gConfig.slide_checked_bg[gConfig.currentIndex] }
                                GradientStop {  position: Math.max(0.00000001, brightness_slider.visualPosition);    color: gConfig.slide_checked_bg[gConfig.currentIndex] }
                                GradientStop {  position: Math.min(brightness_slider.visualPosition+0.0000001, 1);    color: gConfig.slide_unchecked_bg[gConfig.currentIndex] }
                                GradientStop {  position: 1.0;    color: gConfig.slide_unchecked_bg[gConfig.currentIndex] }
                            }
                        }
                }

                Rectangle {
                        width: 24
                        height: 24
                        x: 29
                        y: 29
                        color: Qt.rgba(0,0,0, 0.0) // 透明
                        Image {
                            id: screen_lightid
                            width:  24
                            height: 24
                            source: "qrc:/resource/asset/image/setting_icon/light.png"
                            fillMode: Image.PreserveAspectFit
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                handle: Item {
                    id: light_handle
                }

                onValueChanged:
                {
                    console.log("brightness value: " + currentBrightness)
                    // 发送执行shell命令的信号
                    rootid.qmlSignalSetting(TDMsgType.BasicSettingType.BRIGHTNESS_CONTROL, value * 100)
                    // 发送保存配置信息的信号
                    rootid.qmlSignalSaveConfig("brightness", value, fileId)
                }
            }

            // 深色模式
            Rectangle {
                id: dark_mode_icon
                width: 72
                height: 72
                color: "#5B89FF"
    //            x: 44
    //            y: 116
                anchors.left: brightness_slider.right
                anchors.leftMargin: 90
                anchors.top: brightness_slider.top
                radius: 15
                Image {
                    width:  32
                    height: 32
                    source: "qrc:/resource/asset/image/setting_icon/alarm_clock.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle {
                id: dark_mode_timing
                width: 240
                height: 72
                color: "#BDBDBD"
    //            x: 141
    //            y: 508
                anchors.left: dark_mode_icon.right
                anchors.leftMargin: 48
                anchors.top: dark_mode_icon.top
                radius: 15

                /* 定时开启深色模式 */
                Text {
                    id: dark_mode_timing_text
                    width: 189
                    height: 34
                    x: 25
                    y: 19
                    text: qsTr("定时开启深色模式")
                    color: gConfig.buttonColor[gConfig.currentIndex]
                    font.pixelSize: 24
                    font.styleName: "Regular"
                }

                MouseArea  {
                     anchors.fill:  parent
                     onClicked:  {
                         dark_mode_timing.state  ==  'selected'  ?  dark_mode_timing.state  =  ""  :  dark_mode_timing.state  =  'selected';
                         // TODO
                         if(dark_mode_timing.state  ==  'selected') {
                             dark_mode_button.state  ==  'selected'
                             dark_mode_bg.border.color = "#FFFFFF"
                             dark_mode_timing_text.color = "#FFFFFF"
                             light_mode_button.state  =  ""
                             light_mode_bg.border.color = ""
                         } else {
                             dark_mode_button.state  ==  ''
                             dark_mode_bg.border.color = ""
                         }
                     }
                 }
                states: [
                    State {
                        name: "selected"
                        PropertyChanges {
                            target: dark_mode_timing
                            color: "#5B89FF"
                        }
                    }
                ]
            }

        }


        /* 浅色模式背景 */
        Item {
            id: light_item
            width: 208
            height: 240
            x: 44
            y: 236
            // 替换为Image
            Rectangle {
                id: light_mode_bg
                width:  210
                height: 242
                radius: 8
                Image {
                    source: "qrc:/resource/asset/image/setting_icon/light_bg.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        /* 深色模式背景 */
        Item {
            id: dark_item
            width: 208
            height: 240
            anchors.left: light_item.right
            anchors.leftMargin: 35
            anchors.top: light_item.top

            // 替换为Image
            Rectangle {
                id: dark_mode_bg
                width:  210
                height: 242
                radius: 8
                Image {
                    source: "qrc:/resource/asset/image/setting_icon/dark_bg.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        /* 两种模式选择 */
        Row {
            id: light_model_item
            anchors.left: light_item.left
            anchors.top: light_item.bottom
            anchors.topMargin: 32
            Rectangle {
                id: light_mode_button
                width: 208
                height: 72
                color: "#BDBDBD"
    //            x: 141
    //            y: 508
                radius: 8
                state: currentIndex == 0 ? "selected": ""
                /* 浅色模式按钮 */
                Text {
                    id: light_mode_text
                    width: 95
                    height: 34
                    x: 50
                    y: 19
                    text: qsTr("浅色模式")
                    color: gConfig.buttonColor[gConfig.currentIndex]
                    font.pixelSize: 24
                    font.styleName: "Regular"
                }

                onStateChanged: {
                    console.log("light_mode_button: state = ", light_mode_button.state)
                }

                MouseArea  {
                     anchors.fill:  parent
                     onClicked:  {
                         light_mode_button.state  ==  'selected'  ?  light_mode_button.state  =  ""  :  light_mode_button.state  =  'selected';
                         // TODO
                         if(light_mode_button.state  ==  'selected') {
                             light_mode_bg.border.color = "#5B89FF"
                             gConfig.currentIndex = 0;
                             light_mode_text.color = "#FFFFFF"
                             /* 重置深色模式背景 */
                             dark_mode_button.state  =  ""
                             dark_mode_bg.border.color = ""
                         } else {
                             light_mode_bg.border.color = ""
                         }
                     }
                 }
                states: [
                    State {
                        name: "selected"
                        PropertyChanges {
                            target: light_mode_button
                            color: "#5B89FF"
                        }
                    }
                ]
            }
        }
        Row {
            id: dark_model_item
            anchors.left: light_model_item.right
            anchors.leftMargin: 39
            anchors.top: dark_item.bottom
            anchors.topMargin: 32
            Rectangle {
                id: dark_mode_button
                width: 208
                height: 72
                color: "#BDBDBD"
                radius: 8
                /* 深色模式按钮 */
                Text {
                    id: dark_mode_text
                    width: 95
                    height: 34
                    x: 50
                    y: 19
                    text: qsTr("深色模式")
                    color: gConfig.buttonColor[gConfig.currentIndex]
                    font.pixelSize: 24
                    font.styleName: "Regular"
                }
                MouseArea  {
                     anchors.fill:  parent
                     onClicked:  {
                         dark_mode_button.state  ==  'selected'  ?  dark_mode_button.state  =  ""  :  dark_mode_button.state  =  'selected';
                         // TODO
                         if(dark_mode_button.state  ==  'selected') {
                             dark_mode_bg.border.color = "#FFFFFF"
                             gConfig.currentIndex = 1;
                             /* 重置浅色模式背景 */
                             light_mode_button.state  =  ""
                             light_mode_bg.border.color = ""
                         } else {
                             dark_mode_bg.border.color = ""
                         }
                     }
                 }
                states: [
                    State {
                        name: "selected"
                        PropertyChanges {
                            target: dark_mode_button
                            color: "#5B89FF"
                        }
                    }
                ]
            }
        }

        /* 重置浅色模式背景 */
        function reset_light_mode_bg() {
            light_mode_button.state  =  ""
            light_mode_bg.border.color = ""
        }

        /* 重置深色模式背景 */
        function reset_dark_mode_bg() {
            dark_mode_button.state  =  ""
            dark_mode_bg.border.color = ""
        }

        /* 自定义时间 */
        Item {
            id: defined_time_item
            width: 456
            height: 240
            anchors.left: dark_item.right
            anchors.leftMargin: 37
            anchors.top: dark_item.top

            Rectangle {
                width: 456
                height: 240
                color: "#C4C4C4"
                radius: 8

                /* 自定义时间 */
                Item {
                    id: defined_time
                    width: 158
                    height: 45
                    x: 32
                    y: 20
                    Text {
                        id: defined_time_text
                        width: 158
                        height: 45
                        text: qsTr("自定义时间")
                        color: "#5B89FF"
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }
                }

                /* 开始时间 */
                Item {
                    id: start_time
                    width: 126
                    height: 45
                    anchors.left: defined_time.left
                    anchors.top: defined_time.bottom
                    anchors.topMargin: 32
                    Text {
                        id: start_time_label
                        width: 126
                        height: 45
                        text: qsTr("开始时间")
                        color: gConfig.textColor[gConfig.currentIndex]
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }

                    Text {
                        id: start_time_text
                        width: 94
                        height: 37
                        text: qsTr("19:00")
                        color: gConfig.timeColor[gConfig.currentIndex]
                        font.pixelSize: 32
                        font.styleName: "Regular"
                        anchors.left: start_time_label.right
                        anchors.leftMargin: 142
                        anchors.top: start_time_label.top
                    }

                    Text {
                        id: start_time_selector
                        width: 15
                        height: 15
                        text: qsTr(">")
                        // color: "#C4C4C4"
                        color: gConfig.timeColor[gConfig.currentIndex]
                        font.pixelSize: 32
                        font.styleName: "Regular"
                        anchors.left: start_time_text.right
                        anchors.leftMargin: 12
                        anchors.top: start_time_text.top
                    }

                    MouseArea  {
                         anchors.fill:  parent
                         onClicked:  {
                             start_time_text.state  ==  'selected'  ?  start_time_text.state  =  ""  :  start_time_text.state  =  'selected';
                             // TODO
                         }
                     }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: start_time_text
                                color: "#5B89FF"
                            }
                        }
                    ]

                }

                /* 结束时间 */
                Item {
                    id: end_time
                    width: 126
                    height: 45
                    x: 32
                    y: 175
                    Text {
                        id: end_time_label
                        width: 126
                        height: 45
                        text: qsTr("结束时间")
                        color: gConfig.textColor[gConfig.currentIndex]
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }

                    Text {
                        id: end_time_text
                        width: 94
                        height: 37
                        text: qsTr("7:00")
                        color: gConfig.timeColor[gConfig.currentIndex]
                        font.pixelSize: 32
                        font.styleName: "Regular"
                        anchors.left: end_time_label.right
                        anchors.leftMargin: 142
                        anchors.top: end_time_label.top
                    }

                    // TODO
                    Text {
                        id: end_time_selector
                        width: 15
                        height: 15
                        text: qsTr(">")
                        // color: "#C4C4C4"
                        color: gConfig.timeColor[gConfig.currentIndex]
                        font.pixelSize: 32
                        font.styleName: "Regular"
                        anchors.left: end_time_text.right
                        anchors.leftMargin: 12
                        anchors.top: end_time_text.top
                    }

                }
            }
        }

    }

    /* 设置Item底部 */
    Item {
        id: time_setting_item
        width: 1446
        height: 230
        anchors.top: left_rectangle.bottom
        anchors.topMargin: 12
        Rectangle {
            id: time_setting_rect
            width: 1446
            height: 230
            // color: "#2B2B2B"
            color: gConfig.background[gConfig.currentIndex]
            Text {
                id: time_setting_label
                width: 111
                height: 39
                x: 45
                y: 44
                text: qsTr("时间设置")
                color: gConfig.textColor[gConfig.currentIndex]
                font.pixelSize: 28
                font.styleName: "Regular"
            }
        }
        // 时间
        Rectangle {
            id: time_icon
            width: 72
            height: 72
            color: "#5B89FF"
            x: 45
            y: 114
            radius: 15
            Image {
                width:  32
                height: 32
                source: "qrc:/resource/asset/image/setting_icon/set_timing.png"
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        /* 手动更新时间 */
        Rectangle {
            id: update_time_rect
            width: 208
            height: 72
            color: "#BDBDBD"
            x: 141
            y: 114
            radius: 15
            Text {
                id: update_time_text
                width: 95
                height: 34
                x: 56
                y: 19
                text: qsTr("更新时间")
                color: gConfig.buttonColor[gConfig.currentIndex]
                font.pixelSize: 24
                font.styleName: "Regular"
            }
            MouseArea  {
                 anchors.fill:  parent
                 onClicked:  {
                     update_time_rect.state  ==  'selected'  ?  update_time_rect.state  =  ""  :  update_time_rect.state  =  'selected';
                     // TODO
                     if(update_time_rect.state  ==  'selected') {
                         update_time_text.color = "#FFFFFF"
                     }
                 }
             }
            states: [
                State {
                    name: "selected"
                    PropertyChanges {
                        target: update_time_rect
                        color: "#5B89FF"
                    }
                }
            ]
        }

        // ip地址信息
        Rectangle {
            id: ip_info_rect
            width: 260
            height: 72
            color: gConfig.background[gConfig.currentIndex]
            y: 44
            anchors.left: update_time_rect.right
            anchors.leftMargin: 50
            Text {
                id: ip_info_label
                // width: 95
                // height: 39
                y: 0
                text: qsTr("ip地址: " + host_address)
                color: gConfig.textColor[gConfig.currentIndex]
                font.pixelSize: 28
                font.styleName: "Regular"
                // anchors.verticalCenter: parent.verticalCenter
            }
        }

        // 版本号信息
        Rectangle {
            id: version_info_rect
            width: 260
            height: 72
            color: gConfig.background[gConfig.currentIndex]
            anchors.left: update_time_rect.right
            anchors.leftMargin: 50
            anchors.top: ip_info_rect.bottom
            anchors.topMargin: 20
            Text {
                id: version_info_label
                // width: 95
                // height: 39
                y: 0
                text: qsTr("当前版本: " + version_info)
                color: gConfig.textColor[gConfig.currentIndex]
                font.pixelSize: 28
                font.styleName: "Regular"
                // anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Connections {
        target: rootid
        function onQmlSignalSetting(val, onval) {
            // 1、执行shell命令
            ConfigManager.executeShellCmd(val, onval);
            // 2、保存当前配置到levelDb
        }
    }

    Connections {
        target: rootid
        function onQmlSignalSaveConfig(key, value, fileId) {
            ConfigManager.setConfigToDB(key, value, fileId)
        }
    }

}
