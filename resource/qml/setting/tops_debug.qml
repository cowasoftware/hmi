import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import WorkClass 1.0
//import MsgType 1.0

// 上装调试 页面的 右侧的主内容, 一个tabview
Rectangle {
    id: rootid
    width: 1446
    height: 860
    signal qmlSignalTopDebug(int mode, int onOff) //上装调试信号
    property int currentIndex: gConfig.currentIndex
    TabView {
        id: tabview_id
        anchors.fill: parent

        property string selected_color :  "#5B89FF"
        property string unselected_color :  "#3B3B3B"
        style: TabViewStyle {
            frameOverlap: 1
            tab: Rectangle { // for each tab
                color: styleData.selected ? tabview_id.selected_color : gConfig.tabButtonColor[currentIndex]
                implicitWidth: 180
                implicitHeight: 90
                radius: 2
                Text {
                    width: 96
                    height: 45
                    anchors.centerIn: parent
                    verticalAlignment : Text.AlignVCenter
                    horizontalAlignment : Text.AlignHCenter
                    text: styleData.title
                    font.pixelSize: styleData.selected ? 32 : 28
                    color: gConfig.textColor[currentIndex]
                }
            }

            tabBar:  Rectangle { color: gConfig.tabButtonColor[currentIndex] }
        }


        Component.onCompleted : {
            addTab("左扫盘", left_content_id)
            addTab("右扫盘", right_content_id)
            addTab("吸嘴", mouthpiece_content_id)
            addTab("鄂板", jawplate_content_id)
            addTab("风机", fan_content_id)
            addTab("隔膜泵",diaphragm_pump_id )
            addTab("污水循环", water_circulation_reuse_id)
            addTab("EPS标定", eps_content_id)
        }
    }

    // 左扫盘
    Component {
        id : left_content_id
        Rectangle {
            width: 1446
            height: 770
            // color: "#2b2b2b"
            color: gConfig.background[currentIndex]

            Text {
                x: 72
                y: 42
                width: 128
                height: 45
                color: gConfig.textColor[currentIndex]
                text: qsTr("扫盘旋转")
                font.pixelSize: 32
                font.styleName: "Regular"
            }

            // 开关
            Switch {
                id: left_switch_id
                x: 1130
                y: 42
                width:200
                height:60

                indicator: Rectangle {
                    width: 200
                    height: 60
                    radius: height / 2
                    color: left_switch_id.checked ? "#5B89FF" : "#3B3B3B"
                    border.width: 1
                    border.color: left_switch_id.checked ?  "#5B89FF" : "#3B3B3B"
                    onColorChanged: {
                        rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_WORK_DEBUG, left_switch_id.checked ? 1 : 0)
                    }

                    Rectangle {
                        x: left_switch_id.checked ? parent.width - width - 2 : 1
                        width: left_switch_id.checked ? parent.height - 4 : parent.height - 2
                        height: width
                        radius: width / 2
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        border.color: "#D5D5D5"

                        Behavior on x {
                            NumberAnimation { duration: 100 }
                        }
                    }
                 }
            }


            GridLayout {
                x: 72
                y: 138
                columns: 3
                columnSpacing: 57
                rowSpacing: 52


                Repeater {
                   model: [qsTr("加速"), qsTr("提升"), qsTr("展开"), qsTr("减速"), qsTr("下降"), qsTr("收拢")]

                   Rectangle {
                       id: left_rectange_item_id
                    //    color: "#3b3b3b"
                    color: gConfig.topButtonColor[currentIndex]
                       width: 400
                       height: 200
                       Text {
                           width: 96
                           height: 67
                           anchors.centerIn: parent
                           color: gConfig.textColor[currentIndex]
                           text: qsTr(modelData)
                           font.pixelSize: 48
                           font.styleName: "Regular"
                       }
                       function onLongPressItem(index) {
                           console.log("timer trigger", index)
                           left_rectange_item_id.state  =  'selected';
                           if (index === 0) { //加速
                               rootid.qmlSignalTopDebug(TDMsgType.BRUSH_SPEED_ACC, 1)
                           }else if (index === 1) {
                               rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_UP, 1)
                           }else if (index === 2) {
                               rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_EXTEND, 1)
                           }else if (index === 3) {
                               rootid.qmlSignalTopDebug(TDMsgType.BRUSH_SPEED_MIN, 1)
                           }else if (index === 4) {
                               rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_DOWN, 1)
                           }else {
                               rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_NARROW, 1)
                           }
                       }
                       function onLongPressItemFinish(index) {
                           left_rectange_item_id.state  =  "";
                           if (index === 0) { //加速
                               rootid.qmlSignalTopDebug(TDMsgType.BRUSH_SPEED_ACC, 0)
                           }else if (index === 1) {
                               rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_UP, 0)
                           }else if (index === 2) {
                               rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_EXTEND, 0)
                           }else if (index === 3) {
                               rootid.qmlSignalTopDebug(TDMsgType.BRUSH_SPEED_MIN, 0)
                           }else if (index === 4) {
                               rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_DOWN, 0)
                           }else {
                               rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_NARROW, 0)
                           }
                       }
                        Timer {
                            id: timer_id
                            interval: 500; 
                            running: false; 
                            repeat: true;
                            property real index : -1;
                            onTriggered: {
                                console.log("timer trigger", index)
                                onLongPressItem(index)
                            }
                        }
                       MouseArea  {
                            anchors.fill:  parent
                            onPressed:  {
                                console.log("onPressed", modelData)
                                console.log(index)
                                onLongPressItem(index)
                                timer_id.index = index
                                timer_id.start()
                            }
                            onReleased: {
                                console.log("onReleased", modelData)
                                console.log(index)
                                timer_id.stop()
                                onLongPressItemFinish(index)
                            }
                        }
                       states: [
                           State {
                               name: "selected"
                               PropertyChanges {
                                   target: left_rectange_item_id
                                   color: "#5B89FF"
                               }
                           }
                       ]
                   }
               }

            }
        }
    }
    // 右扫盘
    Component {
        id : right_content_id
        Rectangle {
            width: 1446
            height: 770
            // color: "#2b2b2b"
            color: gConfig.background[currentIndex]

            Text {
                x: 72
                y: 42
                width: 128
                height: 45
                color: gConfig.textColor[currentIndex]
                text: qsTr("扫盘旋转")
                font.pixelSize: 32
                font.styleName: "Regular"
            }

            // 开关
            Switch {
                id: right_switch_id
                x: 1130
                y: 42
                width:200
                height:60

                indicator: Rectangle {
                    width: 200
                    height: 60
                    radius: height / 2
                    color: right_switch_id.checked ? "#5B89FF" : "#3B3B3B"
                    border.width: 1
                    border.color: right_switch_id.checked ?  "#5B89FF" : "#3B3B3B"
                    onColorChanged: {
                        rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_WORK_DEBUG, right_switch_id.checked ? 1 : 0)
                    }

                    Rectangle {
                        x: right_switch_id.checked ? parent.width - width - 2 : 1
                        width: right_switch_id.checked ? parent.height - 4 : parent.height - 2
                        height: width
                        radius: width / 2
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        border.color: "#D5D5D5"

                        Behavior on x {
                            NumberAnimation { duration: 100 }
                        }
                    }
                 }
            }


            GridLayout {
                x: 72
                y: 138
                columns: 3
                columnSpacing: 57
                rowSpacing: 52


                Repeater {
                   model: [qsTr("加速"), qsTr("提升"), qsTr("展开"), qsTr("减速"), qsTr("下降"), qsTr("收拢")]

                   Rectangle {
                       id: right_rectangexx_id
                    //    color: "#3b3b3b"
                       color: gConfig.topButtonColor[currentIndex]
                       width: 400
                       height: 200
                       Text {
                           width: 96
                           height: 67
                           anchors.centerIn: parent
                           color: gConfig.textColor[currentIndex]
                           text: qsTr(modelData)
                           font.pixelSize: 48
                           font.styleName: "Regular"
                       }
                       function onLongPressItem(index) {
                           console.log("timer trigger", index)
                            right_rectangexx_id.state  =  'selected';
                            if (index === 0) { //加速
                                rootid.qmlSignalTopDebug(TDMsgType.BRUSH_SPEED_ACC, 1)
                            }else if (index === 1) {
                                rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_UP, 1)
                            }else if (index === 2) {
                                rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_EXTEND, 1)
                            }else if (index === 3) {
                                rootid.qmlSignalTopDebug(TDMsgType.BRUSH_SPEED_MIN, 1)
                            }else if (index === 4) {
                                rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_DOWN, 1)
                            }else {
                                rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_NARROW, 1)
                            }
                       }
                       function onLongPressItemFinish(index) {
                           right_rectangexx_id.state  =  "";
                            if (index === 0) { //加速
                                rootid.qmlSignalTopDebug(TDMsgType.BRUSH_SPEED_ACC, 0)
                            }else if (index === 1) {
                                rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_UP, 0)
                            }else if (index === 2) {
                                rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_EXTEND, 0)
                            }else if (index === 3) {
                                rootid.qmlSignalTopDebug(TDMsgType.BRUSH_SPEED_MIN, 0)
                            }else if (index === 4) {
                                rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_DOWN, 0)
                            }else {
                                rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_NARROW, 0)
                            }
                       }
                        Timer {
                            id: timer_id
                            interval: 500; 
                            running: false; 
                            repeat: true;
                            property real index : -1;
                            onTriggered: {
                                console.log("timer trigger", index)
                                onLongPressItem(index)
                            }
                        }
                       MouseArea  {
                            anchors.fill:  parent
                            onPressed:  {
                                console.log(modelData)
                                console.log(index)
                                onLongPressItem(index)
                                timer_id.index = index
                                timer_id.start()      
                            }
                            onReleased: {
                                timer_id.stop()
                                onLongPressItemFinish(index)
                            }
                        }
                       states: [
                           State {
                               name: "selected"
                               PropertyChanges {
                                   target: right_rectangexx_id
                                   color: "#5B89FF"
                               }
                           }
                       ]
                   }
               }

            }
        }
    }

    // 吸嘴
    Component {
        id : mouthpiece_content_id
        Rectangle {
            width: 1446
            height: 770
            // color: "#2b2b2b"
            color: gConfig.background[currentIndex]


            GridLayout {
                x: 218
                y: 210
                columns: 2
                columnSpacing: 210

                Repeater {
                   model: [ qsTr("提升"), qsTr("下降")]
                   Rectangle {
                       id: mouthpiece_rectangexx_id
                    //    color: "#3b3b3b"
                       color: gConfig.topButtonColor[currentIndex]
                       width: 400
                       height: 200
                       Text {
                           width: 96
                           height: 67
                           anchors.centerIn: parent
                           color: gConfig.textColor[currentIndex]
                           text: qsTr(modelData)
                           font.pixelSize: 48
                           font.styleName: "Regular"
                       }
                       function onLongPressItem(index) {
                           console.log("timer trigger", index)
                            mouthpiece_rectangexx_id.state  = 'selected'
                            if (index === 0) {
                                rootid.qmlSignalTopDebug(TDMsgType.NOZZLE_UP, 1)
                            }else {
                                rootid.qmlSignalTopDebug(TDMsgType.NOZZLE_DOWN, 1)
                            }
                       }
                       function onLongPressItemFinish(index) {
                            mouthpiece_rectangexx_id.state  =  ""
                            if (index === 0) {
                                rootid.qmlSignalTopDebug(TDMsgType.NOZZLE_UP, 0)
                            }else {
                                rootid.qmlSignalTopDebug(TDMsgType.NOZZLE_DOWN, 0)
                            }
                       }
                       Timer {
                            id: timer_id
                            interval: 500; 
                            running: false; 
                            repeat: true;
                            property real index : -1;
                            onTriggered: {
                                console.log("timer trigger", index)
                                onLongPressItem(index)
                            }
                        }
                       MouseArea  {
                            anchors.fill:  parent
                            onPressed:  {
                                console.log(modelData)
                                console.log(index)
                                onLongPressItem(index)
                                timer_id.index = index
                                timer_id.start()   
                            }
                            onReleased: {
                                timer_id.stop()
                                onLongPressItemFinish(index)
                            }
                        }
                       states: [
                           State {
                               name: "selected"
                               PropertyChanges {
                                   target: mouthpiece_rectangexx_id
                                   color: "#5B89FF"
                               }
                           }
                       ]
                   }
               }

            }
        }
    }

    // 鄂板
    Component {
        id : jawplate_content_id
        Rectangle {
            width: 1446
            height: 770
            // color: "#2b2b2b"
            color: gConfig.background[currentIndex]

            Text {
                x: 72
                y: 42
                width: 128
                height: 45
                color: gConfig.textColor[currentIndex]
                text: qsTr("鄂板张开/关闭")
                font.pixelSize: 32
                font.styleName: "Regular"
            }

            GridLayout {
                x: 218
                y: 210
                columns: 2
                columnSpacing: 210

                Repeater {
                   model: [ qsTr("张开"), qsTr("收拢")]
                   Rectangle {
                       id: jawplate_rectangexx_id
                    //    color: "#3b3b3b"
                       color: gConfig.topButtonColor[currentIndex]
                       width: 400
                       height: 200
                       Text {
                           width: 96
                           height: 67
                           anchors.centerIn: parent
                           color: gConfig.textColor[currentIndex]
                           text: qsTr(modelData)
                           font.pixelSize: 48
                           font.styleName: "Regular"
                       }
                       function onLongPressItem(index) {
                           console.log("timer trigger", index)
                            jawplate_rectangexx_id.state  =  'selected';
                            if (index === 0) {
                                rootid.qmlSignalTopDebug(TDMsgType.EXTEND_RELAY, 1)
                            }else {
                                rootid.qmlSignalTopDebug(TDMsgType.WITHDRAW_RELAY, 1)
                            }
                       }
                       function onLongPressItemFinish(index) {
                            jawplate_rectangexx_id.state  =  "";
                            if (index === 0) {
                                rootid.qmlSignalTopDebug(TDMsgType.EXTEND_RELAY, 0)
                            }else {
                                rootid.qmlSignalTopDebug(TDMsgType.WITHDRAW_RELAY, 0)
                            }
                       }

                       Timer {
                            id: timer_id
                            interval: 500; 
                            running: false; 
                            repeat: true;
                            property real index : -1;
                            onTriggered: {
                                console.log("timer trigger", index)
                                onLongPressItem(index)
                            }
                        }
                       MouseArea  {
                            anchors.fill:  parent
                            onPressed:  {
                                console.log(modelData)
                                console.log(index)
                                onLongPressItem(index)
                                timer_id.index = index
                                timer_id.start()   
                            }
                            onReleased: {
                                timer_id.stop()
                                onLongPressItemFinish(index)
                            }
                        }
                       states: [
                           State {
                               name: "selected"
                               PropertyChanges {
                                   target: jawplate_rectangexx_id
                                   color: "#5B89FF"
                               }
                           }
                       ]
                   }
               }

            }
        }
    }

    // 风机
    Component {
        id : fan_content_id
        Rectangle {
            width: 1446
            height: 770
            // color: "#2b2b2b"
            color: gConfig.background[currentIndex]

            Text {
                x: 72
                y: 42
                width: 128
                height: 45
                color: gConfig.textColor[currentIndex]
                text: qsTr("风机开启/关闭")
                font.pixelSize: 32
                font.styleName: "Regular"
            }

            // 开关
            Switch {
                id: fan_switch_id
                x: 1130
                y: 42
                width:200
                height:60

                indicator: Rectangle {
                    width: 200
                    height: 60
                    radius: height / 2
                    color: fan_switch_id.checked ? "#5B89FF" : "#3B3B3B"
                    border.width: 1
                    border.color: fan_switch_id.checked ?  "#5B89FF" : "#3B3B3B"
                    onColorChanged: {
                        rootid.qmlSignalTopDebug(TDMsgType.FAN_WORK_DEBUG, fan_switch_id.checked ? 1 : 0)
                    }

                    Rectangle {
                        x: fan_switch_id.checked ? parent.width - width - 2 : 1
                        width: fan_switch_id.checked ? parent.height - 4 : parent.height - 2
                        height: width
                        radius: width / 2
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        border.color: "#D5D5D5"

                        Behavior on x {
                            NumberAnimation { duration: 100 }
                        }
                    }
                 }
            }

            GridLayout {
                x: 72
                y: 215
                columns: 3
                columnSpacing: 57

                Repeater {
                   model: [ qsTr("加速"), qsTr("减速"),  qsTr("风机标定")]
                   Rectangle {
                       id: fan_rectangexx_id
                    //    color: "#3b3b3b"
                       color: gConfig.topButtonColor[currentIndex]
                       width: 400
                       height: 200
                       Text {
                           width: 400
                           height: 67
                           anchors.centerIn: parent
                           color: gConfig.textColor[currentIndex]
                           verticalAlignment : Text.AlignVCenter
                           horizontalAlignment : Text.AlignHCenter
                           text: qsTr(modelData)
                           font.pixelSize: 48
                           font.styleName: "Regular"

                       }
                       function onLongPressItem(index) {
                           console.log("timer trigger", index)
                            if (index === 0) {
                                fan_rectangexx_id.state  =  'selected';
                                rootid.qmlSignalTopDebug(TDMsgType.FAN_SPEEDACC, 1)
                            }else if (index === 1) {
                                fan_rectangexx_id.state  =  'selected';
                                rootid.qmlSignalTopDebug(TDMsgType.FAN_SPEEDMIN, 1)
                            }
                       }
                       function onLongPressItemFinish(index) {
                            fan_rectangexx_id.state  =  "";
                            if (index === 0) {
                                rootid.qmlSignalTopDebug(TDMsgType.FAN_SPEEDACC, 0)
                            }else if (index === 1) {
                                rootid.qmlSignalTopDebug(TDMsgType.FAN_SPEEDMIN, 0)
                            } else {
                                // nothing to do
                            }
                       }
                       Timer {
                            id: timer_id
                            interval: 500; 
                            running: false; 
                            repeat: true;
                            property real index : -1;
                            onTriggered: {
                                console.log("timer trigger", index)
                                onLongPressItem(index)
                            }
                        }
                       MouseArea  {
                            anchors.fill:  parent
                            onPressed:  {
                                console.log(modelData)
                                console.log(index)
                                if (index === 2) { // for 风机标定, check password if want seleted
                                    if (fan_rectangexx_id.state  ==  '') {
                                        password_content_loader_id.source = "qrc:///resource/qml/setting/password_box.qml"
                                        password_content_loader_id.fan_rectangexx_id = fan_rectangexx_id
                                    } else {
                                        fan_rectangexx_id.state  =  'selected'
                                        rootid.qmlSignalTopDebug(TDMsgType.FAN_CALIBRATION, 0);
                                    }
                                } else {  // for not 风机标定
                                    onLongPressItem(index)
                                    timer_id.index = index
                                    timer_id.start()
                                }
                            }
                            onReleased:  {
                                console.log(modelData)
                                console.log(index)
                                fan_rectangexx_id.state  =  "";
                                if (index === 2) { // for 风机标定
                                    // nothing to do
                                } else { // for not 风机标定
                                    timer_id.stop()
                                    onLongPressItemFinish(index)
                                }
                                
                            }
                        }
                       states: [
                           State {
                               name: "selected"
                               PropertyChanges {
                                   target: fan_rectangexx_id
                                   color: "#5B89FF"
                               }
                           }
                       ]
                   }
               }

            }

            Loader {
                id: password_content_loader_id
                width: 1446
                height: 960
                source: ""

                property var fan_rectangexx_id : null

                //qrc:///resource/qml/setting/password_box.qml
                Connections {
                    target: password_content_loader_id.item
                    function onPasswordSuccess() {
                        console.log("password_component_loader_id onPasswordSuccess ")
                        password_content_loader_id.source=""

                        function finish() {
                            password_content_loader_id.fan_rectangexx_id.state  =  'selected';
                            rootid.qmlSignalTopDebug(TDMsgType.FAN_CALIBRATION, 1);
                        }
                        finish()
                    }
                    function onCancel() {
                        console.log("password_component_loader_id onCancel ")
                        password_content_loader_id.source=""
                    }
                }

            }
        }


    }


    // 隔膜泵
    Component {
        id : diaphragm_pump_id
        Rectangle {
            width: 1446
            height: 770
            // color: "#2b2b2b"
            color: gConfig.background[currentIndex]

            Text {
                x: 72
                y: 42
                width: 128
                height: 45
                color: gConfig.textColor[currentIndex]
                text: qsTr("隔膜泵开启/关闭")
                font.pixelSize: 32
                font.styleName: "Regular"
            }

            // 开关
            Switch {
                id: diaphragm_pump_switch_id
                x: 1130
                y: 42
                width:200
                height:60

                indicator: Rectangle {
                    width: 200
                    height: 60
                    radius: height / 2
                    color: diaphragm_pump_switch_id.checked ? "#5B89FF" : "#3B3B3B"
                    border.width: 1
                    border.color: diaphragm_pump_switch_id.checked ?  "#5B89FF" : "#3B3B3B"
                    onColorChanged: {
                        //if (diaphragm_pump_switch_id.checked) {
                            rootid.qmlSignalTopDebug(TDMsgType.SPRAY_PUMP_DEBUG, diaphragm_pump_switch_id.checked ? 1 : 0)
                        //}
                    }

                    Rectangle {
                        x: diaphragm_pump_switch_id.checked ? parent.width - width - 2 : 1
                        width: diaphragm_pump_switch_id.checked ? parent.height - 4 : parent.height - 2
                        height: width
                        radius: width / 2
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        border.color: "#D5D5D5"

                        Behavior on x {
                            NumberAnimation { duration: 100 }
                        }
                    }
                 }
            }
          }


    }

    // 污水循环
    Component {
        id : water_circulation_reuse_id
        Rectangle {
            width: 1446
            height: 770
            // color: "#2b2b2b"
            color: gConfig.background[currentIndex]

            Text {
                x: 72
                y: 42
                width: 128
                height: 45
                color: gConfig.textColor[currentIndex]
                text: qsTr("污水循环开启/关闭")
                font.pixelSize: 32
                font.styleName: "Regular"
            }

            // 开关
            Switch {
                id: water_circulation_reuse_switch_id
                x: 1130
                y: 42
                width:200
                height:60

                indicator: Rectangle {
                    width: 200
                    height: 60
                    radius: height / 2
                    color: water_circulation_reuse_switch_id.checked ? "#5B89FF" : "#3B3B3B"
                    border.width: 1
                    border.color: water_circulation_reuse_switch_id.checked ?  "#5B89FF" : "#3B3B3B"
                    onColorChanged: {
                        //if (water_circulation_reuse_switch_id.checked) {
                            rootid.qmlSignalTopDebug(TDMsgType.SEWAGE_LOOP, water_circulation_reuse_switch_id.checked ? 1 : 0)
                        //}
                    }

                    Rectangle {
                        x: water_circulation_reuse_switch_id.checked ? parent.width - width - 2 : 1
                        width: water_circulation_reuse_switch_id.checked ? parent.height - 4 : parent.height - 2
                        height: width
                        radius: width / 2
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        border.color: "#D5D5D5"

                        Behavior on x {
                            NumberAnimation { duration: 100 }
                        }
                    }
                 }
            }
          }


    }

    // EPS标定
    Component {
        id : eps_content_id
        Rectangle {
            width: 1446
            height: 770
            // color: "#2b2b2b"
            color: gConfig.background[currentIndex]


            GridLayout {
                x: 520
                y: 215
                columns: 1

                Repeater {
                   model: [ qsTr("中位标定")]
                   Rectangle {
                       id: eps_rectangexx_id
                    //    color: "#3b3b3b"
                       color: gConfig.topButtonColor[currentIndex]
                       width: 400
                       height: 200
                       Text {
                           width: 400
                           height: 67
                           anchors.centerIn: parent
                           color: gConfig.textColor[currentIndex]
                           verticalAlignment : Text.AlignVCenter
                           horizontalAlignment : Text.AlignHCenter
                           text: qsTr(modelData)
                           font.pixelSize: 48
                           font.styleName: "Regular"

                       }
                       MouseArea  {
                            anchors.fill:  parent
                            onPressed:  {
                                console.log(modelData)
                                console.log(index)
                                eps_rectangexx_id.state  =  'selected';
                                rootid.qmlSignalTopDebug(TDMsgType.EPS_CALIBRATION, 1)
                            }
                            onReleased:  {
                                console.log(modelData)
                                console.log(index)
                                eps_rectangexx_id.state  =  "";
                                rootid.qmlSignalTopDebug(TDMsgType.EPS_CALIBRATION, 0)
                            }
                        }
                       states: [
                           State {
                               name: "selected"
                               PropertyChanges {
                                   target: eps_rectangexx_id
                                   color: "#5B89FF"
                               }
                           }
                       ]
                   }
               }

            }

            Loader {
                id: password_content_loader_id
                width: parent.width
                height: parent.height
                source: "qrc:///resource/qml/setting/password_box.qml"

                Connections {
                    target: password_content_loader_id.item
                    function onPasswordSuccess() {
                        console.log("password_component_loader_id onPasswordSuccess ")
                        password_content_loader_id.source=""
                    }
                }
            }
        }


    }

    Connections {
        target: rootid
        function onQmlSignalTopDebug(val, onOff)
        {
            CUIDataHandle.slotSetTopCleanCmd(val, onOff)
        }
    }
    //Component.onDestruction: {//退出上装调试，停止上装操作，暂时不开启该功能
        // rootid.qmlSignalTopDebug(TDMsgType.LEFT_BRUSH_WORK_DEBUG, 0)
        // rootid.qmlSignalTopDebug(TDMsgType.RIGHT_BRUSH_WORK_DEBUG, 0)
        // rootid.qmlSignalTopDebug(TDMsgType.FAN_WORK_DEBUG, 0)
        // rootid.qmlSignalTopDebug(TDMsgType.SPRAY_PUMP_DEBUG, 0)
        // rootid.qmlSignalTopDebug(TDMsgType.SEWAGE_LOOP, 0)
    //}
}


