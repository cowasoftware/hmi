import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import WorkClass 1.0



// 左上角仪表盘
Item {
    id: rootid
    property int    m_nSpeed: 0
    property int    m_nRotatingSpeed: 0
    property string m_strGear: ""
    property string m_strCruiseSpeed: "0.0"
    property int    m_nCruiseStatus: 0

    property bool   m_bLeftLight: false
    property bool   m_bRightLight: false

    signal qmlSignalCruise(int mode, int onOff) //定速巡航开关和加减速信号
    signal qmlSignalUpdateData(int dataType) //切换界面的时候更新数据
    width: 664
    height: parent.height
    Image { // 背景图
        anchors.fill: parent
        source: "qrc:/resource/asset/image/tops/background.png"
        fillMode: Image.PreserveAspectCrop
    }

    // 左上角 仪表, 一个图 和 两个文字速度
    Item {
        x: 24
        y: 65
        width: 171
        height: 155


        // 仪表图
        Image {
            x: 10
            y: 16
            width: 151
            height: 94
            source: !control_switch_id.controlSts ? "qrc:/resource/asset/image/tops/cruisecontroloff.png" : "qrc:/resource/asset/image/tops/cruisecontrolon.png"
            fillMode: Image.PreserveAspectFit
        }

        // 仪表图的刻度
        Repeater {
            model : ["0", "1", "2", "3", "4", "5", "6", "7", "8"]

            Text {
                width: 6
                height: 12
                text: modelData
                color: "#FFFFFF"
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                font.pixelSize: 10
                // 刻度位置是个弧形
                x: 85 - width/2 - (80 * Math.cos(Math.PI * index / 8) + (index - 4))
                y: 100 - height/2 - 90 * Math.sin(Math.PI * index / 8)
            }
        }

        Text {
            width: 120
            height: 30
            y:56
            x: (parent.width - width )/2
            //text: "8"
            text: m_strCruiseSpeed
            color: "#FFFFFF"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            font.pixelSize: 32
        }

        // Text {
        //     width: 120
        //     height: 30
        //     x: (parent.width - width )/2
        //     y: 80
        //     text: "km/h"
        //     color: "#FFFFFF"
        //     verticalAlignment : Text.AlignVCenter
        //     horizontalAlignment : Text.AlignHCenter
        //     font.pixelSize: 20
        // }

        Rectangle {
            id: control_switch_id
            x: 38
            y: 90
            width: 95
            height: 37
            color: "#141414"
            property int controlSts: 0
            Text {
                width: 95
                height: 37
                text: !control_switch_id.controlSts ? "点击开启定速巡航" : "KM/H"
                color: "#FFFFFF"
                //verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                font.pixelSize: 12
            }
            function onLongPressItem() {
                    rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_START, 1)
            }
             MouseArea  {
                    anchors.fill:  parent
                     onClicked:  {
                            control_switch_id.state  ==  'selected'  ?  control_switch_id.state  =  ""  :  control_switch_id.state  =  'selected';
                            if (control_switch_id.state  ==  'selected')
                            {
                                control_switch_id.controlSts = 1
                                control_switch_id.onLongPressItem()
                                cru_timer_id.start() 
                              
                            }else
                            {
                                control_switch_id.controlSts = 0
                                cru_timer_id.stop()
                                rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_START, 0)
                            }
                        }
            
                    }
                    Timer {
                        id: cru_timer_id
                        interval: 100; 
                        running: false; 
                        repeat: true;
                        onTriggered: {
                            control_switch_id.onLongPressItem()
                            //control_switch_id.cruiseSts = m_nCruiseStatus
                        }
                }
            }

            Rectangle {
                x:5
                y:127
                width:160
                height:60
                color: Qt.rgba(65/255, 65/255, 65/255, 0.37) 
                Button{
                  id: minusselect_id
                  x: 10
                  y: 0
                  width: 60
                  height: 60
                  background: Rectangle {
                    color: Qt.rgba(65/255, 65/255, 65/255, 0) 
                 }
                onPressed: {
                    rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_DEC, 1)
                }
                onReleased: {
                    rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_DEC, 0)
                }
                Image {
                    x: 10
                    y: 0
                    width: 60
                    height: 60
                    anchors.centerIn: parent
                    source: !control_switch_id.controlSts ? "qrc:/resource/asset/image/tops/decelerationUnopened.png" : "qrc:/resource/asset/image/tops/deceleration.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
                Image {
                    x: 50
                    y: 0
                    width: 60
                    height: 60
                    source: !control_switch_id.controlSts ? "qrc:/resource/asset/image/tops/Dividingline.png" : "qrc:/resource/asset/image/tops/Dividing.png"
                    fillMode: Image.PreserveAspectFit
                }
                Button{
                  id: addselect_id
                  x: 90
                  y: 0
                  width: 60
                  height: 60
                  background: Rectangle {
                    color: Qt.rgba(65/255, 65/255, 65/255, 0) 
                 }
                onPressed: {
                    rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_ACC, 1)
                }
                onReleased : {
                    rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_ACC, 0)
                }
                Image {
                    x: 90
                    y: 0
                    width: 60
                    height: 60
                    anchors.centerIn: parent
                    source: !control_switch_id.controlSts ? "qrc:/resource/asset/image/tops/accelerationUnopened.png" : "qrc:/resource/asset/image/tops/acceleration.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
            }


        // Row {
        //     x: 8
        //     y:115
        //     width: 151
        //     height: 40
        //     property int subItemSize : 40
        //     spacing: (width - 3*subItemSize)/2
        //     Item {
        //         width: parent.subItemSize
        //         height: parent.height
        //         Button{
        //           id: minusselect_id
        //           x: 5
        //           y: 10
        //           width: 24
        //           height: 20
        //           background: Rectangle {
        //             color: "#141414"
        //          }
        //         onClicked: {
        //             rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_DEC)
        //         }
        //         Image {
        //             width: 24
        //             height: 4

        //             anchors.centerIn: parent
        //             source: "qrc:/resource/asset/image/tops/minus.png"
        //             fillMode: Image.PreserveAspectFit
        //         }
        //     }

        //     }
        //     Item {
        //         id: cruise_control_id
        //         width: parent.subItemSize
        //         height: parent.height

        //         function onLongPressItem() {
        //             rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_START)
                           
        //         }
        //         Button{
        //           id: controlselect_id
        //           width: 37
        //           height: 33
        //           property int cruiseSts: m_nCruiseStatus
        //           background: Rectangle {
        //             color: "#141414"
        //           }
        //         onCruiseStsChanged:
        //         {
        //             if (cruiseSts)//停止定速巡航
        //             {
        //                 timer_id.stop()
        //                 controlselect_image_id.source = "qrc:/resource/asset/image/tops/cruise_control_indicator_off.png"
        //                 cruiseSts = 0 //停止后置位
        //                 rootid.m_nCruiseStatus = 0
        //             }
        //         }
        //         onClicked: {
        //             if (!cruiseSts) {//开启定速巡航,持续下发指令
        //               //rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_START)
        //               cruise_control_id.onLongPressItem()
        //               timer_id.start() 
        //               controlselect_image_id.source = "qrc:/resource/asset/image/tops/cruise_control_indicator.png"
        //             } else {
        //               //rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_STOP)
        //               timer_id.stop() 
        //               controlselect_image_id.source = "qrc:/resource/asset/image/tops/cruise_control_indicator_off.png"
        //             }
        //         }
                
                
        //         Timer {
        //                 id: timer_id
        //                 interval: 100; 
        //                 running: false; 
        //                 repeat: true;
        //                 //property real index : -1;
        //                 onTriggered: {
        //                     //console.log("timer trigger", index)
        //                     cruise_control_id.onLongPressItem()
        //                     controlselect_id.cruiseSts = m_nCruiseStatus
        //                 }
        //         }
        //         Image {
        //             id: controlselect_image_id
        //             width: 37
        //             height: 33

        //             anchors.centerIn: parent
        //             source: "qrc:/resource/asset/image/tops/cruise_control_indicator_off.png"
        //             fillMode: Image.PreserveAspectFit
        //         }
        //       }

        //     }
        //     Item {
        //         width: parent.subItemSize
        //         height: parent.height
        //         Button{
        //           id: addselect_id
        //           y: 5
        //           width: 24
        //           height: 24
        //           background: Rectangle {
        //                 color: "#141414"
        //             }
        //             onClicked: {
        //                 rootid.qmlSignalCruise(CMsgType.CmdType.CURISE_ACC)
        //             }
        //             Image {
        //                 width: 24
        //                 height: 24
        //                 anchors.centerIn: parent
        //                 source: "qrc:/resource/asset/image/tops/add.png"
        //                 fillMode: Image.PreserveAspectFit
        //             }
        //         }

        //     }
        // }

    }

    // 中间的R N D
    Row {
        id: rnd_selector_id
        width: 170
        height: 68
        y:62
        x: (parent.width - width) /2
        spacing: (width - 3*36)/2


        Text {
            id: r_id
            width: 36
            height: 68
            text: "R"
            color: "#666666"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            font.pixelSize: 44
            MouseArea  {
                 anchors.fill:  parent
                 onClicked:  {
                     //rnd_selector_id.state  ===  'R'  ?  rnd_selector_id.state  =  ""  :  rnd_selector_id.state  =  'R';
                 }
             }
        }
        Text {
            id: n_id
            width: 36
            height: 68
            text: "N"
            color: "#666666"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            font.pixelSize: 44
            MouseArea  {
                 anchors.fill:  parent
                 onClicked:  {
                     //rnd_selector_id.state  ===  'N'  ?  rnd_selector_id.state  =  ""  :  rnd_selector_id.state  =  'N';
                 }
             }
        }
        Text {
            id: d_id
            width: 36
            height: 68
            text: "D"
            color: "#666666"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            font.pixelSize: 44
            MouseArea  {
                 anchors.fill:  parent
                 onClicked:  {
                     //rnd_selector_id.state  ===  'D'  ?  rnd_selector_id.state  =  ""  :  rnd_selector_id.state  =  'D';
                 }
             }
        }
        state: m_strGear

        states: [
            State {
                name: "non"
                PropertyChanges {
                }
            },
            State {
                name: "R"
                PropertyChanges {
                    target: r_id
                    color: "#006AFF"
                    font.pixelSize: 48
                }
            },
            State {
                name: "N"
                PropertyChanges {
                    target: n_id
                    color: "#006AFF"
                    font.pixelSize: 48
                }
            },
            State {
                name: "D"
                PropertyChanges {
                    target: d_id
                    color: "#006AFF"
                    font.pixelSize: 48
                }
            }
        ]

    }


    // 中间的大仪表
    Item {
        id : middle_rate_panel_id
        width: 274
        height: 257
        anchors.horizontalCenter: parent.horizontalCenter
        y:141
        //property int rate: 100 // 当前时速
        property int rate: m_nSpeed
        //property var ctxclear
        onRateChanged: {
            //var ctx = middle_canvas_id.getContext('2d');
             //if(ctxclear)
            {
                //ctxclear.clearRect(0,0,middle_canvas_id.width,middle_canvas_id.height);
                middle_canvas_id.requestPaint()
            }
        }

        Canvas{
            id: middle_canvas_id
            height:206
            width: parent.width
            onPaint: {
                var center_x = 137
                var center_y = 143
                var begin = Math.PI - Math.PI / 6  // 150角度
                var end = Math.PI/ 6  // 30角度
                var rate_angle = (middle_rate_panel_id.rate / 120.0) * (Math.PI + Math.PI / 3) + begin  // 算以下时速在仪表上的位置

                var ctx = getContext("2d")
                ctx.clearRect(0,0,middle_canvas_id.width,middle_canvas_id.height);
                //middle_rate_panel_id.ctxclear = ctx
                // 先画最外层的 两个弧
                ctx.beginPath();
                ctx.lineWidth = 2;
                ctx.strokeStyle = Qt.rgba(80, 80, 80, 0.4)
                ctx.arc(center_x, center_y, 125 , rate_angle, end)
                ctx.stroke()
                ctx.closePath();


                ctx.beginPath();
                ctx.lineWidth = 8;
                ctx.strokeStyle = Qt.rgba(80, 80, 80, 0.3) // "#505050, alpha 0.59"
                ctx.arc(center_x, center_y, 114, rate_angle, end)
                ctx.stroke()
                ctx.closePath();

                // 画 时速表上 3层红色的部分
                ctx.beginPath();
                ctx.lineWidth = 2;
                ctx.strokeStyle = "#FFFFFF"
                ctx.arc(center_x, center_y, 125 , begin, rate_angle)
                ctx.stroke()
                ctx.closePath();


                ctx.beginPath();
                ctx.lineWidth = 8;
                ctx.strokeStyle = "#fc5656"
                ctx.arc(center_x, center_y, 114, begin, rate_angle)
                ctx.stroke()
                ctx.closePath();


                ctx.beginPath();
                ctx.lineWidth = 20;
                ctx.strokeStyle = Qt.rgba(192/255, 73/255, 73/255, 0.41) // "#c04949, alpha 0.41"
                ctx.arc(center_x, center_y, 95, begin, rate_angle)
                ctx.stroke()
                ctx.closePath();

                // 画 时速表上 分段线
                var index = 1
                while (index < middle_rate_panel_id.rate / 30) {
                    ctx.beginPath();
                    ctx.strokeStyle = Qt.rgba(0, 0, 0, 1)
                    ctx.lineWidth = 2;
                    var angle = -Math.PI/6 + index*Math.PI/3
                    var a_x = Math.round(Number(center_x - 85 * Math.cos(angle)))
                    var a_y = Math.round(Number(center_y - 85 * Math.sin(angle)))
                    var b_x = Math.round(Number(center_x - 126 * Math.cos(angle)))
                    var b_y = Math.round(Number(center_y - 126 * Math.sin(angle)))
                    console.log("index", index, a_x, a_y, b_x, b_y)
                    ctx.moveTo(a_x, a_y);
                    ctx.lineTo(b_x, b_y);
                    ctx.stroke()
                    ctx.closePath();
                    index = index + 1
                }
            }
        }

        // 仪表图的刻度
        Repeater {
            model : [
                {text : "00", x : 0, y: 190},
                {text : "30", x : 8, y: 65},
                {text : "60", x : middle_rate_panel_id.width/2 - 7, y: 0},
                {text : "90", x : middle_rate_panel_id.width - 25, y: 65},
                {text : "120", x :middle_rate_panel_id.width - 15, y: 190}
            ]

            Text {
                width: 13
                height: 15
                text: modelData.text
                color: "#FFFFFF"
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                font.pixelSize: 12
                // 刻度位置是个弧形
                x : modelData.x
                y : modelData.y
//                x: 137 - width/2 - 135 * Math.cos(Math.PI * (index*2 - 1)  / 6 )
//                y: 143 - height/2 - 135 * Math.sin(Math.PI * (index*2 - 1) / 6 ) - Math.abs(2 - index) * 5
            }
        }
        Text {
            id : rate_id
            width: 64
            height: 35
            x: (parent.width - width) / 2
            y: 110
            text: qsTr(middle_rate_panel_id.rate.toString())
            color: "#FFFFFF"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            font.pixelSize: 74
            font.bold: true
        }
        Text {
            width: 41
            height: 28
            x: (parent.width - width) / 2
            y: 180
            text: qsTr("KM/H")
            color: "#FFFFFF"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            font.pixelSize: 20
        }

    }

    // 右上角
    Item {
        width: 179
        height: 145
        x: 461
        y: 62
        id: right_mileage_panel_id
        //property int total_mileage: 7000
        property int total_mileage: m_nRotatingSpeed
        //property var ctxclear
        onTotal_mileageChanged: {
            //var ctx = mileage_canvas_id.getContext('2d');
            //if (ctxclear)
            {
                //ctxclear.clearRect(0,0,mileage_canvas_id.width,mileage_canvas_id.height);
                mileage_canvas_id.requestPaint()
            }
        }
        Canvas{
            id: mileage_canvas_id
            height:130
            width: 162
            y : 0
            anchors.horizontalCenter: parent.horizontalCenter
            onPaint: {
                var center_x = 81
                var center_y = 90
                var begin = Math.PI - Math.PI / 6
                var end = Math.PI/ 6
                var rate_angle = (right_mileage_panel_id.total_mileage / 8000.0) * (Math.PI + Math.PI / 3) + begin  // 算以下里程在仪表上的位置

                var ctx = getContext("2d")
                ctx.clearRect(0,0,mileage_canvas_id.width,mileage_canvas_id.height);
                //right_mileage_panel_id.ctxclear = ctx
//                ctx.fillStyle="#FF0000";  for debug
//                ctx.fillRect(0,0,161,121);

                // 先画 里程表上最外层的 两个弧
                ctx.beginPath();
                ctx.lineWidth = 1;
                ctx.strokeStyle = Qt.rgba(80, 80, 80, 0.4)
                ctx.arc(center_x, center_y, 80 , rate_angle, end)
                ctx.stroke()
                ctx.closePath();


                ctx.beginPath();
                ctx.lineWidth = 5;
                ctx.strokeStyle = Qt.rgba(80, 80, 80, 0.3) // "#505050, alpha 0.59"
                ctx.arc(center_x, center_y, 74, rate_angle, end)
                ctx.stroke()
                ctx.closePath();

                // 画 里程表上 3层蓝色的部分
                ctx.beginPath();
                ctx.lineWidth = 1;
                ctx.strokeStyle = "#FFFFFF"
                ctx.arc(center_x, center_y, 80 , begin, rate_angle)
                ctx.stroke()
                ctx.closePath();


                ctx.beginPath();
                ctx.lineWidth = 5;
                ctx.strokeStyle = "#006aff"
                ctx.arc(center_x, center_y, 74, begin, rate_angle)
                ctx.stroke()
                ctx.closePath();


                ctx.beginPath();
                ctx.lineWidth = 13;
                ctx.strokeStyle = Qt.rgba(0/255, 96/255, 255/255, 0.44) // "#006aff, alpha 0.41"
                ctx.arc(center_x, center_y, 62, begin, rate_angle)
                ctx.stroke()
                ctx.closePath();

                // 画 里程表上 分段线
                var index = 1
                while (index < right_mileage_panel_id.total_mileage / 1000) {
                  ctx.beginPath();
                  ctx.strokeStyle = Qt.rgba(0, 0, 0, 1)
                  ctx.lineWidth = 1;
                  var angle = Math.PI*(index - 1)/6
                  var a_x = Math.round(Number(center_x - 55 * Math.cos(angle)))
                  var a_y = Math.round(Number(center_y - 55 * Math.sin(angle)))
                  var b_x = Math.round(Number(center_x - 80 * Math.cos(angle)))
                  var b_y = Math.round(Number(center_y - 80 * Math.sin(angle)))
                  console.log("index", index, a_x, a_y, b_x, b_y)
                  ctx.moveTo(a_x, a_y);
                  ctx.lineTo(b_x, b_y);
                  ctx.stroke()
                  ctx.closePath();
                  index = index + 1
              }
            }
        }

        // 仪表图的刻度
        Repeater {
            model : ["0", "1", "2", "3", "4", "5", "6", "7", "8"]

            Text {
                width: 6
                height: 12
                text: modelData
                color: "#FFFFFF"
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                font.pixelSize: 10
                // 刻度位置是个弧形
                x: 88 - width/2 - 88 * Math.cos(Math.PI * (index - 1) / 6)
                y: 90 - height/2 - 88 * Math.sin(Math.PI * (index - 1) / 6)
            }
        }

        Text {
            width: 64
            height: 35
            x: (parent.width - width) / 2
            y: 68
            text: qsTr(right_mileage_panel_id.total_mileage.toString())
            color: "#FFFFFF"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            font.pixelSize: 32
            font.bold: true
        }
        Text {
            width: 41
            height: 28
            x: (parent.width - width) / 2
            y: 113
            text: qsTr("RPH")
            color: "#FFFFFF"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            font.pixelSize: 20
        }
    }


    Item {
        width:565
        height:27
        x:50
        y:270

        Image {
            width:  50
            height: parent.height
            anchors.left: parent.left
            source: m_bLeftLight ? "qrc:/resource/asset/image/tops/turnleft.png" : ""
            fillMode: Image.PreserveAspectFit
        }
        Image {
            width:  50
            height: parent.height
            anchors.right: parent.right
            source: m_bRightLight ? "qrc:/resource/asset/image/tops/turnright.png" : ""
            fillMode: Image.PreserveAspectFit
        }
    }
    //CUIDataHandle {
    //    id: datahandleid
    //}

    function dashboarddata(nSpeed, strCruiseSpeed, nCruiseStatus) {
        m_nSpeed = nSpeed
        m_strCruiseSpeed = strCruiseSpeed.toString()
        m_nCruiseStatus = nCruiseStatus
        console.log("on dashboarddata cru spd = ", nSpeed)
    }
    function leftrightlight(bLeft, bRight) {
        m_bLeftLight = bLeft
        m_bRightLight = bRight
    }

    /*MouseArea{
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: (mouse) => {
            if(mouse.button === Qt.LeftButton){ //调试触发信号
                console.log(' Qt.LeftButton')
                //CUIDataHandle.sendSignal()
            }else{
                console.log(' Qt.RightButton')
                //rootid.qmlSignal1()
                //rootid.qmlSignalCruise(1)
            }
        }
    }*/
    Component.onCompleted: {
    //    CUIDataHandle.onSignalDashBoard.connect(dashboarddata) //绑定qml中的函数
    //    CUIDataHandle.onSignalLeftRightLight.connect(leftrightlight)
    //    rootid.qmlSignalCruise.connect(CUIDataHandle.slotSetCruiseControlCmd)//绑定c++层的槽函数
        CUIDataHandle.getCanData(CMsgType.GetCanDataType.DASHBOARD_DATA);//获取更新仪表盘数据
        rootid.qmlSignalUpdateData(CMsgType.GetCanDataType.DIAGNOSIS_MAINDRI_DATA)//从诊断信息中获取档位信息
        //console.log("connect signal")
    }
    //采用Connections方式绑定信号，避免切换页面重复操作
    Connections {
        target: CUIDataHandle
        function onSignalDashBoard(nSpeed, strCruiseSpeed, nCruiseStatus)
        {
            dashboarddata(nSpeed, strCruiseSpeed, nCruiseStatus)
        }
        function onSignalLeftRightLight(bLeft, bRight)
        {
            leftrightlight(bLeft, bRight)
        }
        function onSignalDiagnosisMainDri(nMotSpeed,
                                nMotTorque,
                                nRotaryWarning,
                                nIntePass,
                                nGearSts,
                                nBackBrake,
                                nAccPdlSts,
                                nBusbardischarg,
                                nBrakeActive,
                                nMotSpeedValid)
        {
            m_nRotatingSpeed = Math.abs(nMotSpeed)
            if (nGearSts == 0)
            {
                m_strGear = "N"
            }else if (nGearSts == 1)
            {
                m_strGear = "R"
            }else if (nGearSts == 2)
            {
                m_strGear = "D"
            }
        }
    }
    Connections {
        target: rootid
        function onQmlSignalCruise(val, onoff)
        {
            CUIDataHandle.slotSetTopCleanCmd(val, onoff)
        }
        function onQmlSignalUpdateData(dataType)
        {
            CUIDataHandle.slotDiagnosisUpdateData(dataType)
        }
    }
}
