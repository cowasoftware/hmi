import QtQuick 2.0
import QtQuick.Controls 2.15

import WorkClass 1.0
//import MsgType 1.0

Item {
    id: rootid
//    anchors.fill: parent
    width: 1082
    height: 1090
    property int cleanFlag:1
    property int dumpFlag:1
    property int m_nWaterLine: 0
    signal qmlSignalClean(int mode, int onOff) //清洗信号
    signal qmlSignalUpdateData(int dataType) //切换界面的时候更新数据
    // 一排 清扫按钮
    Row {
        x : 60
        y : 68
        width: 964
        height: 76

        Rectangle {  // 开关
            id : clean_swith_id
            width: 114
            height: 76
            color: "#333333"
            radius: 4
            property bool is_select: false
            Image {
                width:  45
                height: 45
                source: "qrc:/resource/asset/image/tops/cleanning/power_supply.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
            MouseArea  {
                 anchors.fill:  parent
                 onClicked:  {
                     clean_swith_id.is_select = !clean_swith_id.is_select
                     clean_swith_id.color = clean_swith_id.is_select ? "#5B89FF" : "#333333"
                     if (!clean_swith_id.is_select) { // 如果总开关关闭,其他模式选择要变灰色
                         //if (clean_mode_id.selected_id != null) {
                             //clean_mode_id.selected_id.color = "#333333"
                         //}
                     }
                 }
             }
            onIs_selectChanged: { //总开关状态切换，下发指令,一键启动
                if (clean_swith_id.is_select) {
                    rootid.qmlSignalClean(CMsgType.CmdType.WORK_START, 1)
                    if (rect_strong_id.state == 'selected')
                    {
                        rootid.qmlSignalClean(CMsgType.CmdType.FAN_STRONG_MODE, 1)
                    }else if (rect_standard_id.state == 'selected')
                    {
                        rootid.qmlSignalClean(CMsgType.CmdType.FAN_STANDARD_MODE, 1)
                    }else
                    {
                        rootid.qmlSignalClean(CMsgType.CmdType.FAN_CLEAN_MODE, 1)
                    }
                    // 删除抑尘模式
                    // if (rect_dustsupre_id.state == 'selected')
                    // {
                    //     rootid.qmlSignalClean(CMsgType.CmdType.DUST_SUPRE_MODE, 1)
                    // }else
                    // {
                    //     rootid.qmlSignalClean(CMsgType.CmdType.DUST_NORMAL_MODE, 1)
                    // }
                }else
                {
                    rootid.qmlSignalClean(CMsgType.CmdType.WORK_START, 0)
                }
            }
        }

        Item {
            width: 104
            height: 60
            anchors.verticalCenter: parent.verticalCenter
            Image {
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter : parent.horizontalCenter
                source: "qrc:/resource/asset/image/tops/cleanning/blower.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Rectangle { // 模式选择1
            width: 360
            height: 60
            y:8
            color: "#333333"
            Rectangle {
                id : rect_clean_id
                width: 120
                height: 60
                color: "#5B89FF"
                Image{
                    width: 35
                    height: 35
                    x:16
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/resource/asset/image/tops/cleanning/cleaning.png"
                    fillMode: Image.PreserveAspectFit
                }
                  Text {
                         width: 48
                         height: 34
                          x : 56
                          anchors.verticalCenter: parent.verticalCenter
                          color: "#ffffff"
                          verticalAlignment : Text.AlignVCenter
                           horizontalAlignment : Text.AlignHCenter
                           text: "保洁"
                            font.pixelSize: 24
                            font.styleName: "Regular"
                       }
                  MouseArea  {
                      anchors.fill:  parent
                      onClicked:  {
                          if (!clean_swith_id.is_select) 
                          { // 只有总开关打开时 才相应
                             return
                          }
                          rect_clean_id.state  ==  'selected'  ?  rect_clean_id.state  =  ""  :  rect_clean_id.state  =  'selected';
                          if (rect_clean_id.state  ==  'selected')
                          {
                              rect_strong_id.color = "#333333"
                              rect_standard_id.color = "#333333"
                              rect_clean_id.color = "#5B89FF"

                              rect_strong_id.state = "unselected"
                              rect_standard_id.state = "unselected"
                              rootid.qmlSignalClean(CMsgType.CmdType.FAN_CLEAN_MODE, 1)
                          }
                      }
                  }
//

            }
            Rectangle {
                id: rect_standard_id
                width: 120
                height: 60
                x: 120
                color: "#333333"
                Image{
                    width: 35
                    height: 35
                    x:16
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/resource/asset/image/tops/cleanning/standard.png"
                    fillMode: Image.PreserveAspectFit
                }
                  Text {
                         width: 48
                         height: 34
                          x : 56
                          anchors.verticalCenter: parent.verticalCenter
                          color: "#ffffff"
                          verticalAlignment : Text.AlignVCenter
                           horizontalAlignment : Text.AlignHCenter
                           text: "标准"
                            font.pixelSize: 24
                            font.styleName: "Regular"
                       }
                  MouseArea  {
                      anchors.fill:  parent
                      onClicked:  {
                          if (!clean_swith_id.is_select) 
                          { // 只有总开关打开时 才相应
                             return
                          }
                          rect_standard_id.state  ==  'selected'  ?  rect_standard_id.state  =  ""  :  rect_standard_id.state  =  'selected';
                          if (rect_standard_id.state  ==  'selected')
                          {
                              rect_clean_id.color = "#333333"
                              rect_strong_id.color = "#333333"
                              rect_standard_id.color = "#5B89FF"

                              rect_clean_id.state = "unselected"
                              rect_strong_id.state = "unselected"
                              rootid.qmlSignalClean(CMsgType.CmdType.FAN_STANDARD_MODE, 1)
                          }
                      }
                  }


            }
            Rectangle {
                id : rect_strong_id
                width: 120
                height: 60

                x: 240
                color: "#333333"
                Image{
                    width: 35
                    height: 35
                    x:16
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/resource/asset/image/tops/cleanning/strong.png"
                    fillMode: Image.PreserveAspectFit
                }
                  Text {
                         width: 48
                         height: 34
                          x : 56
                          anchors.verticalCenter: parent.verticalCenter
                          color: "#ffffff"
                          verticalAlignment : Text.AlignVCenter
                           horizontalAlignment : Text.AlignHCenter
                           text: "强劲"
                            font.pixelSize: 24
                            font.styleName: "Regular"
                       }
                  MouseArea  {
                      anchors.fill:  parent
                      onClicked:  {
                          if (!clean_swith_id.is_select) 
                          { // 只有总开关打开时 才相应
                                return
                          }
                          rect_strong_id.state  ==  'selected'  ?  rect_strong_id.state  =  ""  :  rect_strong_id.state  =  'selected';
                          if (rect_strong_id.state  ==  'selected')
                          {
                              rect_clean_id.color = "#333333"
                              rect_standard_id.color = "#333333"
                              rect_strong_id.color = "#5B89FF"

                              rect_clean_id.state = "unselected"
                              rect_standard_id.state = "unselected"

                              rootid.qmlSignalClean(CMsgType.CmdType.FAN_STRONG_MODE, 1)
                          }
                      }
                  }
            }

        
            // Row {
            //     anchors.fill: parent

            //     Repeater {
            //         id : clean_mode_id

            //         property var selected_id : null
            //         model: [
            //             {myColor: cleanFlag ? "#5B89FF" : "#333333", text : qsTr("保洁"), image: "qrc:/resource/asset/image/tops/cleanning/cleaning.png"},
            //             {myColor: "#333333", text : qsTr("标准"), image: "qrc:/resource/asset/image/tops/cleanning/standard.png"},
            //             {myColor: "#333333", text : qsTr("强劲"), image: "qrc:/resource/asset/image/tops/cleanning/strong.png"},
            //         ]
            //         Rectangle {
            //             id : clean_rectangle_id
            //             //color: "#333333"
            //             color: modelData.myColor
            //             radius: 4
            //             width: 120
            //             height: 60
            //             Image {
            //                 width: 35
            //                 height: 35
            //                 x:16
            //                 anchors.verticalCenter: parent.verticalCenter
            //                 source: modelData.image
            //                 fillMode: Image.PreserveAspectFit
            //             }
            //             Text {
            //                 width: 48
            //                 height: 34
            //                 x : 56
            //                 anchors.verticalCenter: parent.verticalCenter
            //                 color: "#ffffff"
            //                 verticalAlignment : Text.AlignVCenter
            //                 horizontalAlignment : Text.AlignHCenter
            //                 text: modelData.text
            //                 font.pixelSize: 24
            //                 font.styleName: "Regular"
            //             }
            //             MouseArea  {
            //                 anchors.fill:  parent
            //                 onClicked:  {
            //                     console.log(modelData)
            //                     console.log(index)
            //                     if (!clean_swith_id.is_select) { // 只有总开关打开时 才相应
            //                         return
            //                     }

            //                     if (clean_mode_id.selected_id != null) {
            //                         clean_mode_id.selected_id.color = "#333333"
            //                     }
            //                     clean_mode_id.selected_id = clean_rectangle_id
            //                     clean_mode_id.selected_id.color = "#5B89FF"
            //                     if (index == 0) { //保洁模式
            //                         rootid.qmlSignalClean(CMsgType.CmdType.FAN_CLEAN_MODE, 1)
            //                     }else if (index == 1) { //标准模式
            //                         rootid.qmlSignalClean(CMsgType.CmdType.FAN_STANDARD_MODE, 1)
            //                     }else {                 //强劲模式
            //                         rootid.qmlSignalClean(CMsgType.CmdType.FAN_STRONG_MODE, 1)
            //                     }
            //                     if (index != 0)
            //                     {
            //                         cleanFlag = 0
            //                     }
                                
            //                 }
            //             }
            //         }
            //     }
            // }
        }

        // Item {
        //     width: 104
        //     height: 60
        //     anchors.verticalCenter: parent.verticalCenter
        //     Image {
        //         width: 40
        //         height: 40
        //         anchors.verticalCenter: parent.verticalCenter
        //         anchors.horizontalCenter : parent.horizontalCenter
        //         source: "qrc:/resource/asset/image/tops/cleanning/predump.png"
        //         fillMode: Image.PreserveAspectFit
        //     }
        // }
        // Rectangle { // 模式选择2
        //     width: 240
        //     height: 60
        //     y:8
        //     x:0
        //     color: "#333333"
        //      Rectangle {
        //         id: rect_common_id
        //         width: 126
        //         height: 60
        //         x: 0
        //         color: "#5B89FF"
        //         Image{
        //             width: 35
        //             height: 35
        //             x:16
        //             anchors.verticalCenter: parent.verticalCenter
        //             source: "qrc:/resource/asset/image/tops/cleanning/ordinary_dust_removal.png"
        //             fillMode: Image.PreserveAspectFit
        //         }
        //           Text {
        //                  width: 48
        //                  height: 34
        //                   x : 56
        //                   anchors.verticalCenter: parent.verticalCenter
        //                   color: "#ffffff"
        //                   verticalAlignment : Text.AlignVCenter
        //                    horizontalAlignment : Text.AlignHCenter
        //                    text: "普通"
        //                     font.pixelSize: 24
        //                     font.styleName: "Regular"
        //                }
        //           MouseArea  {
        //               anchors.fill:  parent
        //               onClicked:  {
        //                    if (!clean_swith_id.is_select) 
        //                    { // 只有总开关打开时 才相应
        //                         return
        //                    }
        //                   rect_common_id.state  ==  'selected'  ?  rect_common_id.state  =  ""  :  rect_common_id.state  =  'selected';
        //                   if (rect_common_id.state  ==  'selected')
        //                   {
        //                       rect_dustsupre_id.color = "#333333"
        //                       rect_common_id.color = "#5B89FF"

        //                       rect_dustsupre_id.state = "unselected"
        //                       rootid.qmlSignalClean(CMsgType.CmdType.DUST_NORMAL_MODE, 1)
        //                   }
        //               }
        //           }


        //     }

        //     Rectangle {
        //         id: rect_dustsupre_id
        //         width: 126
        //         height: 60
        //         x: 126
        //         color: "#333333"
        //         Image{
        //             width: 35
        //             height: 35
        //             x:16
        //             anchors.verticalCenter: parent.verticalCenter
        //             source: "qrc:/resource/asset/image/tops/cleanning/dust_suppression_mode.png"
        //             fillMode: Image.PreserveAspectFit
        //         }
        //           Text {
        //                  width: 48
        //                  height: 34
        //                   x : 56
        //                   anchors.verticalCenter: parent.verticalCenter
        //                   color: "#ffffff"
        //                   verticalAlignment : Text.AlignVCenter
        //                    horizontalAlignment : Text.AlignHCenter
        //                    text: "抑尘"
        //                    font.pixelSize: 24
        //                    font.styleName: "Regular"
        //                }
        //           MouseArea  {
        //               anchors.fill:  parent
        //               onClicked:  {
        //                   if (!clean_swith_id.is_select) 
        //                    { // 只有总开关打开时 才相应
        //                         return
        //                    }
        //                   rect_dustsupre_id.state  ==  'selected'  ?  rect_dustsupre_id.state  =  ""  :  rect_dustsupre_id.state  =  'selected';
        //                   if (rect_dustsupre_id.state  ==  'selected')
        //                   {
        //                       rect_common_id.color = "#333333"
        //                       rect_dustsupre_id.color = "#5B89FF"

        //                       rect_common_id.state = "unselected"
        //                       rootid.qmlSignalClean(CMsgType.CmdType.DUST_SUPRE_MODE, 1)
        //                   }
        //               }
        //           }


        //     }
        //     // Row {
        //     //     anchors.fill: parent

        //     //     Repeater {
        //     //         id : clean_mode_id2

        //     //         property var selected_id : null
        //     //         model: [
        //     //            {myColor: dumpFlag ? "#5B89FF" : "#333333", text : qsTr("普通"), image: "qrc:/resource/asset/image/tops/cleanning/ordinary_dust_removal.png"},
        //     //            {myColor: "#333333", text : qsTr("抑尘"), image: "qrc:/resource/asset/image/tops/cleanning/dust_suppression_mode.png"},
        //     //         ]
        //     //         Rectangle {
        //     //            id : clean_rectangle_id2
        //     //            //color: "#333333"
        //     //            color: modelData.myColor
        //     //            radius: 4
        //     //            width: 120
        //     //            height: 60
        //     //            Image {
        //     //                width: 35
        //     //                height: 35
        //     //                x:16
        //     //                anchors.verticalCenter: parent.verticalCenter
        //     //                source: modelData.image
        //     //                fillMode: Image.PreserveAspectFit
        //     //            }
        //     //            Text {
        //     //                width: 48
        //     //                height: 34
        //     //                x : 56
        //     //                anchors.verticalCenter: parent.verticalCenter
        //     //                color: "#ffffff"
        //     //                verticalAlignment : Text.AlignVCenter
        //     //                horizontalAlignment : Text.AlignHCenter
        //     //                text: modelData.text
        //     //                font.pixelSize: 24
        //     //                font.styleName: "Regular"

        //     //            }
        //     //            MouseArea  {
        //     //                 anchors.fill:  parent
        //     //                 onClicked:  {
        //     //                     console.log(modelData)
        //     //                     console.log(index)

        //     //                     if (clean_mode_id2.selected_id != null) {
        //     //                         clean_mode_id2.selected_id.color = "#333333"
        //     //                     }
        //     //                     clean_mode_id2.selected_id = clean_rectangle_id2
        //     //                     clean_mode_id2.selected_id.color = "#5B89FF"
        //     //                     if (index == 0) { //普通模式
        //     //                         rootid.qmlSignalClean(CMsgType.CmdType.DUST_NORMAL_MODE, 1)
        //     //                     }else {                 //抑尘模式
        //     //                         dumpFlag = 0
        //     //                         rootid.qmlSignalClean(CMsgType.CmdType.DUST_SUPRE_MODE, 1)
        //     //                     }
        //     //                 }
        //     //             }
        //     //        }
        //     //     }
        //     // }
        // }
    }



    // 中间的车 部分
    Item {
        y : 150
        width: 1082
        height: 1080 - y
        Image {
            anchors.fill: parent
            source: "qrc:/resource/asset/image/tops/background.png"
            fillMode: Image.PreserveAspectCrop
        }
        Image {
            anchors.fill: parent
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter : parent.horizontalCenter
            source: "qrc:/resource/asset/image/tops/cleanning/bodywork_operation_model.png"
            fillMode: Image.PreserveAspectCrop
        }
        Image {
            x: 42
            y: 184
            width: 99
            height: 99
            //anchors.fill: parent
            //anchors.verticalCenter: parent.verticalCenter
            //anchors.horizontalCenter : parent.horizontalCenter
            source: "qrc:/resource/asset/image/tops/cleanning/Fanicon.png"
            fillMode: Image.PreserveAspectCrop
        }
        Image {
            x: 135
            y: 226
            width: 339
            height: 464
            //anchors.fill: parent
            //anchors.verticalCenter: parent.verticalCenter
            //anchors.horizontalCenter : parent.horizontalCenter
            source: "qrc:/resource/asset/image/tops/cleanning/fanSpeed.png"
            fillMode: Image.PreserveAspectCrop
        }
        Text {
            x:136
            y:188
            width:48
            height:34
            color: "#ffffff"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            text: qsTr("风速")
            font.pixelSize: 24
            font.styleName: "Regular"

        }
        Text {
            x:870
            y:180
            width:48
            height:34
            color: "#ffffff"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            text: qsTr("水位 " + m_nWaterLine.toString() + "%")
            font.pixelSize: 24
            font.styleName: "Regular"

        }
        Image {
            x: 687
            y: 219
            width: 284
            height: 256
            //anchors.fill: parent
            //anchors.verticalCenter: parent.verticalCenter
            //anchors.horizontalCenter : parent.horizontalCenter
            source: "qrc:/resource/asset/image/tops/cleanning/waterLine.png"
            fillMode: Image.PreserveAspectCrop
        }
        Image {
            x: 960
            y: 177
            width: 99
            height: 99
            source: "qrc:/resource/asset/image/tops/cleanning/watericon.png"
            fillMode: Image.PreserveAspectCrop
        }
    }
    Item {
        //顶工作灯按钮图标
        Rectangle {
            id: worklight_id
            height: 90
            width : 90
            x : 30
            y : 940

            color: "#141414"
            Image {
                    width: 70
                    height: 70
                    anchors.verticalCenter: parent.verticalCenter
                    source:  worklight_id.state  ==  'selected'  ? "qrc:/resource/asset/image/tops/cleanning/work_light_kai.png" : "qrc:/resource/asset/image/tops/cleanning/work_light_guan.png"
                    fillMode: Image.PreserveAspectFit
                    }

            MouseArea  {
                anchors.fill:  parent
                onClicked:  {
                    worklight_id.state  ==  'selected'  ?  worklight_id.state  =  ""  :  worklight_id.state  =  'selected';
                    if (worklight_id.state == 'selected')
                    {
                        rootid.qmlSignalClean(CMsgType.WORK_LIGHT, 1)
                    }else
                    {
                        rootid.qmlSignalClean(CMsgType.WORK_LIGHT, 0)
                    }
                }
            }

        }
    }

    // 底部按钮
    Item {
        height: 60
        width : 922
        x : 80
        y : 958

        
        Text {
            width: 96
            height: 34
            x : 56
            anchors.verticalCenter: parent.verticalCenter
            color: "#ffffff"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            text: qsTr("高压清洗")
            font.pixelSize: 24
            font.styleName: "Regular"
        }

        Rectangle { // 高压清洗开关
            id: rectSwitchid
            property int onOff: 0
            width: 240
            height: 60
            x:172
            color: "#333333"
            radius: 4
            anchors.verticalCenter: parent.verticalCenter
            Rectangle {
                id: rect_on_id
                width: 126
                height: 60
                x: 0
                color: "#333333"

                  Text {
                      width: 50
                      height: 34
                      anchors.fill: parent
                      color: "#ffffff"
                      verticalAlignment : Text.AlignVCenter
                      horizontalAlignment : Text.AlignHCenter
                      text: "开"
                      font.pixelSize: 24
                      font.styleName: "Regular"
                       }
                  MouseArea  {
                      anchors.fill:  parent
                      onClicked:  {
                          rect_on_id.state  ==  'selected'  ?  rect_on_id.state  =  ""  :  rect_on_id.state  =  'selected';
                          if (rect_on_id.state  ==  'selected')
                          {
                              rect_off_id.color = "#333333"
                              rect_on_id.color = "#5B89FF"

                              rect_off_id.state = "unselected"
                              rootid.qmlSignalClean(CMsgType.HIGH_PRECLEAN_START_MODE, 1)
                              rectSwitchid.onOff = 1
                          }
                      }
                  }


            }

            Rectangle {
                id: rect_off_id
                width: 120
                height: 60
                x: 120
                color: "#5B89FF"

                  Text {
                      width: 50
                      height: 34
                      anchors.fill: parent
                      color: "#ffffff"
                      verticalAlignment : Text.AlignVCenter
                      horizontalAlignment : Text.AlignHCenter
                      text: "关"
                      font.pixelSize: 24
                      font.styleName: "Regular"
                       }
                  MouseArea  {
                      anchors.fill:  parent
                      onClicked:  {
                          rect_off_id.state  ==  'selected'  ?  rect_off_id.state  =  ""  :  rect_off_id.state  =  'selected';
                          if (rect_off_id.state  ==  'selected')
                          {
                              rect_on_id.color = "#333333"
                              rect_off_id.color = "#5B89FF"
                              
                              rect_on_id.state = "unselected"

                              rootid.qmlSignalClean(CMsgType.HIGH_PRECLEAN_STOP_MODE, 1)
                              rectSwitchid.onOff = 0
                          }
                      }
                  }


            }
            // Row {
            //     anchors.fill: parent
            //     Repeater {
            //         id : high_pressure_cleaning_mode_id
            //         anchors.fill: parent
            //         property var selected_id : null
            //         model: [
            //            {text : qsTr("ON")},
            //            {text : qsTr("OFF")},
            //         ]
            //         Rectangle {
            //            id : high_pressure_cleaning_button_id
            //            color: "#333333"
            //            radius: 4
            //            width: 120
            //            height: 60
            //            Text {
            //                width: 50
            //                height: 34
            //                anchors.fill: parent
            //                color: "#ffffff"
            //                verticalAlignment : Text.AlignVCenter
            //                horizontalAlignment : Text.AlignHCenter
            //                text: modelData.text
            //                font.pixelSize: 24
            //                font.styleName: "Regular"

            //            }
            //            MouseArea  {
            //                 anchors.fill:  parent
            //                 onClicked:  {
            //                     console.log(modelData)
            //                     console.log(index)

            //                     if (high_pressure_cleaning_mode_id.selected_id != null) {
            //                         high_pressure_cleaning_mode_id.selected_id.color = "#333333"
            //                     }
            //                     high_pressure_cleaning_mode_id.selected_id = high_pressure_cleaning_button_id
            //                     high_pressure_cleaning_mode_id.selected_id.color = "#5B89FF"
            //                     if (index == 0) { //高压清洗开启模式
            //                         rootid.qmlSignalClean(CMsgType.HIGH_PRECLEAN_START_MODE, 1)
            //                         rectSwitchid.onOff = 1
            //                     }else {                 //高压清洗关闭模式
            //                         rootid.qmlSignalClean(CMsgType.HIGH_PRECLEAN_STOP_MODE, 1)
            //                         rectSwitchid.onOff = 0
            //                     }
            //                 }
            //             }
            //        }
            //     }
            // }

        }

        Rectangle { // 箱体倾斜和归位
            width: 240
            height: 60
            anchors.right: parent.right
            color: "#333333"
            radius: 4
            anchors.verticalCenter: parent.verticalCenter

            Row {
                anchors.fill: parent
                Repeater {
                    id : box_mode_id
                    anchors.fill: parent
                    property var selected_id : null
                    model: [
                       {text : qsTr("箱体倾斜")},
                       {text : qsTr("箱体归位")},
                    ]
                    Rectangle {
                       id : box_button_id
                       color: "#333333"
                       radius: 4
                       width: 120
                       height: 60
                       Text {
                           width: 50
                           height: 34
                           anchors.fill: parent
                           color: "#ffffff"
                           verticalAlignment : Text.AlignVCenter
                           horizontalAlignment : Text.AlignHCenter
                           text: modelData.text
                           font.pixelSize: 24
                           font.styleName: "Regular"

                       }
                       function onLongPressItem(index) {
                           console.log("timer trigger", index)
                            box_button_id.state  =  'selected';
                            if (index === 0) {
                                rootid.qmlSignalClean(CMsgType.TANK_TILT, 1)
                            }else {
                                rootid.qmlSignalClean(CMsgType.TANK_RESET, 1)
                            }
                       }
                       function onLongPressItemFinish(index) {
                            box_button_id.state  =  "";
                            if (index === 0) {
                                rootid.qmlSignalClean(CMsgType.TANK_TILT, 0)
                            }else {
                                rootid.qmlSignalClean(CMsgType.TANK_RESET, 0)
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
                                   target: box_button_id
                                   color: "#5B89FF"
                               }
                           }
                       ]
                   }
                }
            }

        }

    }
   // CUIDataHandle {
    //    id: datahandleid
    //}

    Component.onCompleted: {
    //    //CUIDataHandle.onSignalDashBoard.connect(dashboarddata) //绑定qml中的函数
    //    rootid.qmlSignalClean.connect(CUIDataHandle.slotSetTopCleanCmd)//绑定c++层的上装清洗指令槽函数
    //    console.log("connect signal")
        //为了从诊断信息中户获取水位信息
        rootid.qmlSignalUpdateData(CMsgType.GetCanDataType.DIAGNOSIS_IO71_DATA)
    }

    Connections {
        target: rootid
        function onQmlSignalClean(val, onval)
        {
            CUIDataHandle.slotSetTopCleanCmd(val, onval)
        }
        function onQmlSignalUpdateData(dataType)
        {
            CUIDataHandle.slotDiagnosisUpdateData(dataType)
        }
    }
    Connections {
        target: CUIDataHandle
        function onSignalWaterLine(waterLine)
        {
            m_nWaterLine = waterLine
        }
       
    }
}
