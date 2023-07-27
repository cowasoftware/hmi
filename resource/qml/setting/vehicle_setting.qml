import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import ConfigClass 1.0

//车辆设置
Item {
    id: car_setting_id
    width: 1446
    height: 960
    property string vehtype: ""
    property int currentIndex: gConfig.currentIndex
    property string currentMileage: gConfig.currentMileage
    signal qmlSignalSaveMileage(string key, string value, int fileId)
    // 保存配置信息的信号
    Rectangle {
        id: diagnosis_infor_id
        x: 0
        y: 0
        width: 1446
        height: 100
        color: gConfig.titleBackground[currentIndex]

        Text {
            id: text1
            anchors.centerIn: parent
            width: 128
            height: 45
            color: gConfig.textColor[currentIndex]
            text: qsTr("车辆设置")
            font.pixelSize: 32
            font.styleName: "Regular"
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Rectangle {
        id: rootid
        x: 0
        y: 100
        width: 1446
        height: 860
        TabView {
            id: tabview_id
            anchors.fill: parent
            property string selected_color: "#5B89FF"
            property string unselected_color: "#3B3B3B"
            style: TabViewStyle {
                frameOverlap: 1
                tab: Rectangle {
                    // for each tab
                    color: styleData.selected ? tabview_id.selected_color : gConfig.tabButtonColor[currentIndex]
                    implicitWidth: 201
                    implicitHeight: 90
                    radius: 2
                    Text {
                        width: 150
                        height: 39
                        anchors.centerIn: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: styleData.title
                        font.pixelSize: styleData.selected ? 32 : 28
                        color: gConfig.textColor[currentIndex]
                    }
                }

                tabBar: Rectangle {
                    color: gConfig.tabButtonColor[currentIndex]
                }
            }

            Component.onCompleted: {
                addTab("车型设置", vehtype_content_id)
                addTab("保养提醒里程", mileage_content_id)
                addTab("复位保养记录", reset_maintenance_recordid)
            }
        }

        // 车型设置
        Component {
            id: vehtype_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle {
                    id: veh_rectange_id
                    x: 48
                    y: 40
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    width: 128
                    height: 45
                    Text {
                        width: 128
                        height: 45
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("当前车型")
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }
                }
                Rectangle {
                    id: rectypeid
                    x: 205
                    y: 35
                    width: 50
                    height: 56
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        width: 50
                        height: 56
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr(vehtype)
                        font.pixelSize: 48
                        font.styleName: "Regular"
                    }
                }
                //车辆图片
                GridLayout {
                    x: 72
                    y: 161
                    columns: 4
                    columnSpacing: 70
                    rowSpacing: 0

                    Repeater {
                        model: [{
                                "text": qsTr(""),
                                "image": "qrc:/resource/asset/image/tops/carmodel/Kirin.png"
                            }, {
                                "text": qsTr(""),
                                "image": "qrc:/resource/asset/image/tops/carmodel/Hulk.png"
                            }, {
                                "text": qsTr(""),
                                "image": "qrc:/resource/asset/image/tops/carmodel/unicorn.png"
                            }]

                        Rectangle {
                            id: veh_rectangeimg_id
                            //    color: "#2b2b2b"
                            color: gConfig.background[currentIndex]
                            width: 266
                            height: 326
                            Image {
                                width: 266
                                height: 326

                                anchors.verticalCenter: parent.verticalCenter
                                source: modelData.image
                                fillMode: Image.PreserveAspectFit
                            }
                            Text {
                                width: 38
                                height: 42
                                anchors.centerIn: parent
                                color: gConfig.textColor[currentIndex]
                                text: modelData.text
                                font.pixelSize: 36
                                font.styleName: "Regular"
                            }
                        }
                    }
                }

                GridLayout {
                    x: 150
                    y: 535
                    columns: 4
                    columnSpacing: 255
                    rowSpacing: 0

                    Repeater {
                        model: [qsTr("麒麟"), qsTr("浩克"), qsTr("独角兽")]

                        // Rectangle {
                        //     id: veh_rectangexx_id
                        //     color: gConfig.carSettingButtonColor[currentIndex]
                        //     width: 200
                        //     height: 60
                        //     Text {
                        //         width: 71
                        //         height: 50
                        //         anchors.centerIn: parent
                        //         color: gConfig.textColor[currentIndex]
                        //         text: qsTr(modelData)
                        //         font.pixelSize: 36
                        //         font.styleName: "Regular"
                        //         verticalAlignment : Text.AlignVCenter
                        //         horizontalAlignment : Text.AlignHCenter
                        //     }

                        //     MouseArea  {
                        //         anchors.fill:  parent
                        //         onClicked:  {
                        //             console.log(modelData)
                        //             //console.log(index)
                        //             veh_rectangexx_id.state  ==  'selected'  ?  veh_rectangexx_id.state  =  ""  :  veh_rectangexx_id.state  =  'selected';
                        //             vehtype = modelData
                        //             // TODO

                        //         }
                        //     }
                        //     states: [
                        //         State {
                        //             name: "selected"
                        //             PropertyChanges {
                        //                 target: veh_rectangexx_id
                        //                 color: "#5B89FF"
                        //             }
                        //         }
                        //     ]

                        // }
                        Button {
                            id: veh_btnx_id
                            width: 200
                            height: 80
                            text: qsTr(modelData)
                            font.pixelSize: 36
                            font.styleName: "Regular"
                            highlighted: true
                            
                            //设置按钮背景颜色
                            background: Rectangle {
                                color: "#4F4F4F"
                                width: 200
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            onClicked: {
                                console.log(modelData)
                                //console.log(index)
                                vehtype = modelData
                            }
                            onPressed: {
                                veh_btnx_id.background.color = "#5B89FF"
                            }
                            onReleased: {
                                veh_btnx_id.background.color = "#4F4F4F"
                            }
                        }
                    }
                }
            }
        }

        // 保养提醒里程
        Component {
            id: mileage_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle {
                    id: mile_rectange_id
                    x: 48
                    y: 40
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    width: 192
                    height: 45
                    Text {
                        width: 192
                        height: 45
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("当前保养里程")
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }
                }
                Rectangle {
                    id: mile_text_rect
                    x: 262
                    y: 35
                    width: 93
                    height: 56
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        id: mile_text
                        width: 93
                        height: 56
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr(currentMileage)
                        font.pixelSize: 48
                        font.styleName: "Regular"
                    }
                }
                Rectangle {
                    x: 380
                    y: 59
                    width: 33
                    height: 28
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        width: 33
                        height: 28
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("KM")
                        font.pixelSize: 20
                        font.styleName: "Regular"
                    }
                }
                Rectangle {
                    x: 605
                    y: 40
                    width: 192
                    height: 45
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        width: 192
                        height: 45
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("修改保养里程")
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }
                }

                Rectangle {
                    x: 605
                    y: 125
                    width: 642
                    height: 80
                    // color: "#4f4f4f"
                    color: gConfig.carSettingButtonColor[currentIndex]

                    TextField {
                        id: km_id
                        width: 642
                        height: 80
                        // color: "#ffffff"
                        color: gConfig.textColor[currentIndex]
                        maximumLength: 10
                        //echoMode: TextInput.Password
                        font.pixelSize: 48
                        //font.weight: Font.Bold
                        //font.letterSpacing : 20
                        //passwordCharacter: "*"
                        anchors.centerIn: parent
                        verticalAlignment: Text.AlignVCenter

                        //horizontalAlignment : Text.AlignHCenter
                        background: Rectangle {
                            border.width: 1
                            border.color: "#FFFFFF"
                            radius: 4
                            color: Qt.rgba(43 / 255, 43 / 255, 43 / 255, 0.2)
                            implicitHeight: 100
                            implicitWidth: 580
                        }
                        //activeFocusOnPress: false;
                        Keys.onPressed: event => {
                                            if (Qt.Key_Enter === event.key
                                                || Qt.Key_Return === event.key) {
                                                //focus = false
                                                //activeFocusOnPress = false
                                                console.log(
                                                    "当前里程数为：" + currentMileage)
                                                console.log(
                                                    "km_id onPressed km: " + text)
                                                // 更新文本值，最大值四位数
                                                mile_text.text = Math.min(text,
                                                                          9999)
                                                // 发送信号将里程数保存到数据库
                                                qmlSignalSaveMileage(
                                                    "mileage", mile_text.text,
                                                    gConfig.fileId) // 保存配置信息的信号
                                            }
                                        }
                    }
                    Text {
                        width: 51
                        height: 45
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("KM")
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }
                }
                Button {
                    id: unselect_id
                    x: 605
                    y: 253
                    width: 200
                    height: 60
                    background: Rectangle {
                        color: gConfig.carSettingButtonColor[currentIndex]
                        Text {
                            text: qsTr("取消")
                            anchors.centerIn: parent
                            font.pixelSize: 32
                            font.styleName: "Regular"
                            color: gConfig.textColor[currentIndex]
                        }
                    }
                    onClicked: {
                        km_id.text = ""
                    }
                }
                Button {
                    id: select_id
                    x: 1045
                    y: 253
                    width: 200
                    height: 60
                    background: Rectangle {
                        color: "#5b89ff"
                        Text {
                            text: qsTr("确定")
                            anchors.centerIn: parent
                            font.pixelSize: 32
                            font.styleName: "Regular"
                            color: gConfig.textColor[currentIndex]
                        }
                    }
                    onClicked: {
                        // 更新文本值
                        mile_text.text = Math.min(km_id.text, 9999)
                        // 发送信号将里程数保存到数据库
                        qmlSignalSaveMileage("mileage", mile_text.text,
                                             gConfig.fileId)
                    }
                }
            }
        }
        //复位保养记录
        Component {
            id: reset_maintenance_recordid
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle {
                    x: 48
                    y: 50
                    width: 192
                    height: 45
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        width: 192
                        height: 45
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("当前保养记录")
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }
                }

                Rectangle {
                    id: maintenance_record_rect
                    x: 254
                    y: 44
                    width: 70
                    height: 45
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        id: maintenance_days_txt
                        width: 70
                        height: 56
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("253")
                        font.pixelSize: 48
                        font.styleName: "Regular"
                    }
                }
                Rectangle {
                    x: 350
                    y: 50
                    width: 64
                    height: 45
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        width: 64
                        height: 45
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("天,")
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }
                }

                Rectangle {
                    x: 402
                    y: 44
                    width: 93
                    height: 56
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        id: maintenance_miles_txt
                        width: 93
                        height: 56
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("5422")
                        font.pixelSize: 48
                        font.styleName: "Regular"
                    }
                }

                Rectangle {
                    x: 525
                    y: 68
                    width: 33
                    height: 28
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        width: 33
                        height: 28
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("KM")
                        font.pixelSize: 20
                        font.styleName: "Regular"
                    }
                }

                Rectangle {
                    x: 747
                    y: 50
                    width: 256
                    height: 45
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    Text {
                        width: 256
                        height: 45
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("是否复位保养记录")
                        font.pixelSize: 32
                        font.styleName: "Regular"
                    }
                }
                Button {
                    id: reset_id
                    x: 1130
                    y: 30
                    width: 240
                    height: 80
                    background: Rectangle {
                        color: "#5e89f8"
                        Text {
                            text: qsTr("立即复位")
                            anchors.centerIn: parent
                            font.pixelSize: 32
                            font.styleName: "Regular"
                            color: gConfig.textColor[currentIndex]
                        }
                    }
                    onClicked: {
                        maintenance_days_txt.text = 0
                        maintenance_miles_txt.text = 0
                    }
                }
            }
        }

        Connections {
            target: car_setting_id
            function onQmlSignalSaveMileage(key, value, fileId) {
                // 保养里程保存到数据库中
                console.log("通知Settings对象保存配置文件：key = " + key + ", value = " + value)
                ConfigManager.setConfigToDB(key, value, fileId)
            }
        }
    }
}
