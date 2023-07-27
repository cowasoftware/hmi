import QtQuick 2.0
import QtGraphicalEffects 1.15
//import Qt5Compat.GraphicalEffects 6.0

import WorkClass 1.0

// 上装页面的 左下角  灯光屏幕设置
Item {
    id: rootid
    property bool    m_bDoubleFlash: false
    property bool    m_bLightReady: false
    property bool    m_bLightParking: false
    property bool    m_bLeftSteering: false
    property bool    m_bRightSteering: false
    property bool    m_bWorkLight: false
    property bool    m_bPositionLight: false
    property bool    m_bHeadLights: false
    property bool    m_bBatteryFailure: false
    property bool    m_bHighVoltageCutOff: false
    property bool    m_bOverheatAlarm: false
    property bool    m_bVehicleFailure: false
    property bool    m_bCriticalBatteryFailure: false
    property string  m_strVehicleChargingTips: ""
    property int     m_nCruisingRangeDisplay: 0
    property bool     m_bVehicleready: false
    property int     m_nTodayMile: -1

    width: 664
    height: 733
    signal qmlSignalSaveTotalMileage(string key, string value, int fileId)
    // 分割线  TODO: 需要重新画,不够
    Rectangle {
        x: 13
        y: 0
        width: 640
        height: 4
        LinearGradient {
            id : linear_gradient_id
            anchors.fill : parent
            start: Qt.point(0, 0)
            end: Qt.point(width, 0)        ///1、横向渐变
            gradient: Gradient {
                GradientStop {  position: 0.0;    color: "#141414" }
                GradientStop {  position: 0.5;    color: "#1677ff" }
                GradientStop {  position: 1.0;    color: "#141414" }
            }
        }
//        FastBlur {
//           anchors.fill: linear_gradient_id
//           source: linear_gradient_id
//           radius: 32
//       }
    }


    // 一排 灯光设置
    Item {
        width: 626
        height: 40
        x: 19
        y: 24
        Row {
            id: left_light_rectangle_id
            width: 254
            height: parent.height
            anchors.left: parent.left // 左边对齐父节点
            spacing: (width - 36*5)/4
            Repeater {
                model : [
                    {image: m_bHeadLights ? "qrc:/resource/asset/image/tops/light_icon/headlight.png" : ""},
                    {image: m_bPositionLight ? "qrc:/resource/asset/image/tops/light_icon/position_light.png" : ""},
                    {image: m_bDoubleFlash ? "qrc:/resource/asset/image/tops/light_icon/doubleflash.png" : ""},
                    {image: 0 ? "qrc:/resource/asset/image/tops/light_icon/working_lamp.png" : ""},
                    {image: m_bLightParking ? "qrc:/resource/asset/image/tops/light_icon/parking.png" : ""},
                ]
                Image {
                    width:  36
                    height: 36
                    source: modelData.image
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
        Rectangle {
            width : 84
            height: 40
            x: (parent.width - width)/2 // 居中
            color: Qt.rgba(0,0,0, 0.0) // 透明
            border.width : 1
            border.color:  m_bVehicleready ? "#1BF609" : "#141414"
            radius: 4
            Text {
                anchors.fill: parent
                color: "#1BF609"
                text: m_bVehicleready ? qsTr("READY") : ""
                font.pixelSize: 24
                font.styleName: "Regular"
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
            }
        }

        Row {
            id: right_light_rectangle_id
            width: 254
            height: parent.height
            anchors.right: parent.right // 右边对齐父节点
            spacing: (width - 36*5)/4
            Repeater {
                model : [
                    {image: m_bBatteryFailure ? "qrc:/resource/asset/image/tops/light_icon/general_battery_failure.png" : ""},
                    {image: m_bHighVoltageCutOff ? "qrc:/resource/asset/image/tops/light_icon/battery_high_voltage_cutting.png" : ""},
                    {image: m_bVehicleFailure ? "qrc:/resource/asset/image/tops/light_icon/vehicle_failure.png" : ""},
                    {image: m_bOverheatAlarm ? "qrc:/resource/asset/image/tops/light_icon/motor_overheating.png" : ""},
                    {image: m_bCriticalBatteryFailure ? "qrc:/resource/asset/image/tops/light_icon/critical_battery_failure.png" : ""},
                ]
                Image {
                    width:  36
                    height: 36
                    source: modelData.image
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }


    // 胎压 效果
    Item {
        x: 86
        y: 93
        width : 486
        height: 396


        Canvas{
            id: tire_pressure_canvas_id
            anchors.fill: parent
            onPaint: {
                var center_x = parent.width/2
                var center_y = parent.height/2
                var m_carPath = "/resource/asset/image/tops/cleanning/bodywork_operation_model.png"

                var ctx = getContext("2d")
//                ctx.fillStyle="#FF0000";
//                ctx.fillRect(0,0,parent.width,parent.height);

                // 中间的两个圆盘
                var gradient1 = ctx.createRadialGradient(center_x, center_y, 188, center_x, center_y, 198)
                gradient1.addColorStop(0.0, "#141414") //Qt.rgba(49/255, 68/255, 52/255, 0.1)); // "#314434"
                gradient1.addColorStop(1, Qt.rgba(255/255, 255/255, 255/255, 0.1));   //"#403e43"

                ctx.beginPath();
                ctx.lineWidth = 20;
                ctx.strokeStyle = gradient1
                ctx.arc(center_x, center_y, 188 , 0, Math.PI*2)
                ctx.stroke()
                ctx.closePath();

                var gradient2 = ctx.createRadialGradient(center_x, center_y, 150, center_x, center_y, 178)
                gradient2.addColorStop(0.0, "#141414");
                gradient2.addColorStop(1, Qt.rgba(255/255, 255/255, 255/255, 0.1));   //"#403e43"

                ctx.beginPath();
                ctx.lineWidth = 20;
                ctx.fillStyle = gradient2
                ctx.arc(center_x, center_y, 168 , 0, Math.PI*2)
                ctx.fill()
                ctx.closePath();

                // 中间的图片
//                ctx.drawImage(m_carPath, 0, 0, parent.width, parent.height);

                // 四个绿色的 小圆弧
                for (var index = 0; index < 4; index = index + 1) {
                    var begin = Math.PI/12 + Math.PI * index/2
                    var end = begin + Math.PI/3
                    //先画渐变
                    var gradient3 = ctx.createRadialGradient(center_x, center_y, 188, center_x, center_y, 198)
                    gradient3.addColorStop(1, Qt.rgba(40/255, 144/255, 51/255, 0.46)) // "#289033"
                    gradient3.addColorStop(0.0, Qt.rgba(29/255, 228/255, 25/255, 0.01)); // "#1DE419"
                    ctx.beginPath();
                    ctx.lineWidth = 80;
                    ctx.strokeStyle = gradient3
                    ctx.arc(center_x, center_y, 158 , begin, end)
                    ctx.stroke()
                    ctx.closePath();
                    // 再画蒙层
                    gradient3.addColorStop(1, Qt.rgba(40/255, 144/255, 51/255, 0.05))
                    gradient3.addColorStop(0.0, Qt.rgba(40/255, 144/255, 51/255, 0.05));
                    ctx.beginPath();
                    ctx.lineWidth = 80;
                    ctx.strokeStyle = gradient3
                    ctx.arc(center_x, center_y, 158 , begin, end)
                    ctx.stroke()
                    ctx.closePath();

                    // 画小圆弧内的两个小圆点
                    // x1 = x0 + r * cos(angle)
                    // y1 = y0 + r * sin(angle)
                    // 第一个小圆点
                    var bias1 = Math.PI/36
                    var cycle1_x = center_x + 178 * Math.cos(begin + bias1);
                    var cycle1_y = center_y + 178 * Math.sin(begin + bias1);
                    var radius = 5
                    draw_small_cycle(ctx, cycle1_x, cycle1_y, radius);

                    // 第二个小圆点
                    var bias2 = - Math.PI/36
                    var cycle2_x = center_x + 178 * Math.cos(end + bias2);
                    var cycle2_y = center_y + 178 * Math.sin(end + bias2);
                    draw_small_cycle(ctx, cycle2_x, cycle2_y, radius);

                    // 绘制内部的小三角形
                    var x0 = center_x + 158 * Math.cos(begin + Math.PI/6);
                    var y0 = center_y + 158 * Math.sin(begin + Math.PI/6);
                    var x1 = x0 - 5 * Math.cos(Math.PI / 3)
                    var y1 = y0 + 5 * Math.cos(Math.PI / 6)
                    var x2 = x0 + 5 * Math.cos(Math.PI / 3)
                    var y2 = y0 + 5 * Math.cos(Math.PI / 6)
                    draw_triangle(ctx, x0, y0, x1, y1, x2, y2)

                }

                // 先画 胎压两边的 4个弧
                var gradient4 = ctx.createRadialGradient(center_x - 240, center_y, 0, center_x - 240, center_y, 70)
                gradient4.addColorStop(0.0, "#7aff84");
                gradient4.addColorStop(1,  Qt.rgba(5/255, 36/255, 7/255, 0.05)); //"#052407"
                var gradient5 = ctx.createRadialGradient(center_x + 240, center_y, 0, center_x + 240, center_y, 70)
                gradient5.addColorStop(0.0, "#7aff84");
                gradient5.addColorStop(1,  Qt.rgba(5/255, 36/255, 7/255, 0.05)); //"#052407"

                var span = Math.PI / 6
                ctx.beginPath();
                ctx.lineWidth = 5;
                ctx.strokeStyle = gradient4
                ctx.arc(center_x - 80, center_y, 160 , Math.PI - span, Math.PI + span)
                ctx.stroke()
                ctx.closePath();
                ctx.beginPath();
                ctx.strokeStyle = gradient5
                ctx.arc(center_x + 80, center_y, 160 ,  -span, span)
                ctx.stroke()
                ctx.closePath();

                var gradient6 = ctx.createRadialGradient(center_x - 220, center_y, 0, center_x - 220, center_y, 40)
                gradient6.addColorStop(0.0, "#7aff84");
                gradient6.addColorStop(1,  Qt.rgba(5/255, 36/255, 7/255, 0.01)); //"#052407"
                var gradient7 = ctx.createRadialGradient(center_x + 220, center_y, 0, center_x + 220, center_y, 40)
                gradient7.addColorStop(0.0, "#7aff84");
                gradient7.addColorStop(1,  Qt.rgba(5/255, 36/255, 7/255, 0.01)); //"#052407"
                span = Math.PI / 12
                ctx.beginPath();
                ctx.lineWidth = 5;
                ctx.strokeStyle = gradient6
                ctx.arc(center_x - 80, center_y, 140 , Math.PI - span, Math.PI + span)
                ctx.stroke()
                ctx.closePath();
                ctx.beginPath();
                ctx.strokeStyle = gradient7
                ctx.arc(center_x + 80, center_y, 140 ,  -span, span)
                ctx.stroke()
                ctx.closePath();

//                ctx.beginPath();
//                ctx.fillStyle = gradient6;
//                ctx.arc(center_x -220, center_y, 40, 0, Math.PI*2);
//                ctx.fill()
//                ctx.closePath();


                /*
                  画小圆弧内的两个小圆点
                  */
                function draw_small_cycle(ctx, center_x, center_y, radius) {
                    ctx.beginPath();
                    ctx.lineWidth = 4;
                    ctx.fillStyle = "#289033"
                    ctx.strokeStyle = "#289033"
                    ctx.arc(center_x, center_y, radius, 0, Math.PI * 2);
                    ctx.stroke()
                    ctx.fill()
                    ctx.closePath();
                }

                /*
                  绘制胎压数字
                  */
                function draw_triangle(ctx, x0, y0, x1, y1, x2, y2) {
                    ctx.strokeStyle = "#13AD1B";
                    ctx.lineWidth = 2
                    ctx.beginPath()
                    ctx.moveTo(x0, y0)
                    ctx.lineTo(x1, y1)
                    ctx.lineTo(x2, y2)
                    ctx.closePath()
                    ctx.stroke()
                }



            }

//            property string m_carPath : "/resource/asset/image/tops/cleanning/bodywork_operation_model.png"
//            Component.onCompleted: {
//                loadImage(m_carPath)
//            }
//            onImageLoaded: {
//                requestPaint();
//                //其他处理
//            }
        }


        // 绘制中间的车图片
        Image {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            x: 0
            y: 0
            scale: 0.95
            source: "qrc:/resource/asset/image/tops/tire_pressure/tirepressuredisplaymodel.png"
            fillMode: Image.PreserveAspectFit
        }

        // 胎压数值
        Repeater {
            id: repeater1
            model : [
                {text_content: "1.9", text_color: "#13AD1B"}, // 暂时先不使用 #C4123C 这个颜色
                {text_content: "2.5", text_color: "#13AD1B"},
                {text_content: "2.5", text_color: "#13AD1B"},
                {text_content: "2.5", text_color: "#13AD1B"}
            ]
            Text {
                id: tire_pressure_number
                width: 35
                height: 34
                text: modelData.text_content
                color: modelData.text_color
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                rotation:  index < 2 ? (15 + 90 * index - 60) : (15 + 90 * index - 60) + 180
                font.pixelSize: 30
                // x = x0 + r * cos(begin + bias)
                // y = y0 + r * sin(begin + bias)
                x: parent.width/2 + 168 * Math.cos(Math.PI/12 + Math.PI * index/2 + Math.PI/6)
                y: parent.height/2 + 168 * Math.sin(Math.PI/12 + Math.PI * index/2 + Math.PI/6)
            }
        }

        // 胎压单位
        Repeater {
            model : [
                {text_content: "bar", text_color: "#1A9520"}, // 暂时先不使用 #821A3D 这个颜色
                {text_content: "bar", text_color: "#1A9520"},
                {text_content: "bar", text_color: "#1A9520"},
                {text_content: "bar", text_color: "#1A9520"}
            ]

            Text {
                id: tire_pressure_unit
                width: 27
                height: 23
                text: modelData.text_content
                color: modelData.text_color
                rotation:  index < 2 ? (15 + 90 * index - 60) : (15 + 90 * index - 60) + 180
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                font.pixelSize: 20
                x: index < 2 ? parent.width/2 + 168 * Math.cos(Math.PI/12 + Math.PI * index/2 + Math.PI/12) :
                               parent.width/2 + 168 * Math.cos(Math.PI/12 + Math.PI * index/2 + Math.PI/4)
                y: index < 2 ? parent.height/2 + 168 * Math.sin(Math.PI/12 + Math.PI * index/2 + Math.PI/12) :
                               parent.height/2 + 168 * Math.sin(Math.PI/12 + Math.PI * index/2 + Math.PI/4)
            }
        }
    }


    // 底部 里程
    Row {
        width: 616
        height: 75
        x: 24
        y: 607
        spacing : 108
        Item {
            width: 96
            height: 70
            Text {
                id : mileage_id
                anchors.top: parent.top // 顶部对齐

                width: parent.width
                height: 34
                color: "#FFFFFF"
                text: m_nTodayMile != -1 ? qsTr(m_nTodayMile.toString()) : qsTr("----")
                font.pixelSize: 28
                font.styleName: "Regular"
            }
            Text {
                anchors.bottom: mileage_id.bottom // 底部和前面的里程 对齐
                anchors.right: parent.right // 右侧对齐
                width: 26
                height: 23
                color: Qt.rgba(1,1,1, 0.69)

                text: qsTr("KM")
                font.pixelSize: 16
                font.styleName: "Regular"
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
            }
            Text {
                width: parent.width
                height: 34
                anchors.bottom: parent.bottom // 底部对齐
                color: "#FFFFFF"
                text: qsTr("今日里程")
                font.pixelSize: 24
                font.styleName: "Regular"
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
            }
        }

        // 剩余续航
        Item {
            width: 181
            height: 60
            x: 0
            y: 15
            Image {
                width: parent.width
                height: 12
                anchors.left: parent.left
                source: "qrc:/resource/asset/image/tops/remaining_battery.png"
                fillMode: Image.Stretch
            }
            Text {
                id : remaining_text_id
                width: 96
                height: 34
                anchors.left: parent.left
                y : 20
                color: Qt.rgba(1,1,1, 0.80)
                text: qsTr("剩余续航")
                font.pixelSize: 24
                font.styleName: "Regular"
                horizontalAlignment : Text.AlignHCenter
            }
            Text {
                width: 59
                height: 50
                x: remaining_text_id.width
                y : 20
                color: Qt.rgba(1,1,1,1)
                text: qsTr("---")
                font.pixelSize: 36
                font.styleName: "Regular"
                horizontalAlignment : Text.AlignHCenter
            }
            Text {
                width: 26
                height: 22
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                color: Qt.rgba(1,1,1, 0.69)
                text: qsTr("KM")
                font.pixelSize: 16
                font.styleName: "Regular"
                horizontalAlignment : Text.AlignHCenter
            }
        }

        // 总里程
        Item {
            width: 122
            height: 70
            Text {
                id : total_mileage_id
                anchors.top: parent.top // 顶部对齐

                width: parent.width
                height: 34
                color: "#FFFFFF"
                //text: qsTr("0123")
                text: m_nCruisingRangeDisplay ? qsTr(m_nCruisingRangeDisplay.toString()) : "---"
                font.pixelSize: 28
                font.styleName: "Regular"
            }
            Text {
                anchors.bottom: total_mileage_id.bottom // 底部和前面的里程 对齐
                anchors.right: parent.right // 右侧对齐
                width: 26
                height: 23
                color: Qt.rgba(1,1,1, 0.69)

                text: qsTr("KM")
                font.pixelSize: 16
                font.styleName: "Regular"
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
            }
            Text {
                width: parent.width
                height: 34
                anchors.bottom: parent.bottom // 底部对齐
                color: "#FFFFFF"
                text: qsTr("总行驶里程")
                font.pixelSize: 24
                font.styleName: "Regular"
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
            }
        }

    }
    //CUIDataHandle {
    //    id: datahandleid
    //}

    function lightscreendata(bDoubleFlash, bLightReady, bLightParking, bLeftSteering, bRightSteering,
                             bWorkLight,
                             bPositionLight,
                             bHeadLights,
                             bBatteryFailure,
                             bHighVoltageCutOff,
                             bOverheatAlarm,
                             bVehicleFailure,
                             bCriticalBatteryFailure,
                             strVehicleChargingTips,
                             bVehicleready
                             /*nCruisingRangeDisplay*/) {
        //m_bDoubleFlash = bDoubleFlash
        m_bLightReady = bLightReady
        m_bLightParking = bLightParking
        m_bLeftSteering = bLeftSteering
        m_bRightSteering = bRightSteering
        m_bWorkLight = bWorkLight
        m_bPositionLight = bPositionLight
        m_bHeadLights = bHeadLights
        m_bBatteryFailure = bBatteryFailure
        m_bHighVoltageCutOff = bHighVoltageCutOff
        m_bOverheatAlarm = bOverheatAlarm
        m_bVehicleFailure = bVehicleFailure
        m_bCriticalBatteryFailure = bCriticalBatteryFailure
        m_strVehicleChargingTips = strVehicleChargingTips
        //m_nCruisingRangeDisplay = nCruisingRangeDisplay
        m_bVehicleready = bVehicleready
        console.log("on signal lightscreendata: ", bDoubleFlash)
    }
    function traveldistance(distance, todayMile) {
        m_nCruisingRangeDisplay = distance
        m_nTodayMile = todayMile
        console.log("---------------------- m_nCruisingRangeDisplay", m_nCruisingRangeDisplay)
        console.log("---------------------- m_nTodayMile", m_nTodayMile)
    }

    /*MouseArea{
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: (mouse) => {
            if(mouse.button === Qt.LeftButton){
                console.log(' Qt.LeftButton')
                //CUIDataHandle.strValue = "HelloCpp"
                //CUIDataHandle.intValue = 2022
                //CUIDataHandle.sendSignal()
            }else{
                console.log(' Qt.RightButton')
                //rootid.qmlSignal1()
                //rootid.qmlSignalCruise(true, false)
            }
        }
    }*/
    Component.onCompleted: {
    //    CUIDataHandle.onSignalLightScreen.connect(lightscreendata) //绑定qml中的函数 处理灯光设置
    //    CUIDataHandle.onSignalTravelDistance.connect(traveldistance)
    //    console.log("connect signal")
        CUIDataHandle.getCanData(CMsgType.GetCanDataType.LIGHTSCREEN_DATA);
    }
    Connections {
        target: CUIDataHandle
        function onSignalLightScreen(bDoubleFlash, bLightReady, bLightParking, bLeftSteering, bRightSteering,
                                     bWorkLight,
                                     bPositionLight,
                                     bHeadLights,
                                     bBatteryFailure,
                                     bHighVoltageCutOff,
                                     bOverheatAlarm,
                                     bVehicleFailure,
                                     bCriticalBatteryFailure,
                                     strVehicleChargingTips, bVehicleready)
        {
            lightscreendata(bDoubleFlash, bLightReady, bLightParking, bLeftSteering, bRightSteering,
                            bWorkLight,
                            bPositionLight,
                            bHeadLights,
                            bBatteryFailure,
                            bHighVoltageCutOff,
                            bOverheatAlarm,
                            bVehicleFailure,
                            bCriticalBatteryFailure,
                            strVehicleChargingTips, bVehicleready)
        }
        function onSignalTravelDistance(distance, todayMile)
        {
            traveldistance(distance, todayMile)
        }
        function onSignalDoubleFlash(doubleFlash)
        {
            m_bDoubleFlash = doubleFlash
        }
    }

}
