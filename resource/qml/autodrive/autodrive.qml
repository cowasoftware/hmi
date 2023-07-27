import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.10
// import QtWebView 1.15
import QtWebEngine 1.10
import QtWebChannel 1.15
import CoordinateUtilClass 1.0
import ConfigClass 1.0
import CAduProxyClass 1.0
import Cowa.HMI2.Plugins 1.0
import TrafficLightTypeEnum 1.0
import WorkClass 1.0
import Cowa.HMI2.VModel 1.0

Item {
    width: 1770
    height: 1080
    id : root_id
    property string key: "favorites"
    // 位置
    property var targetAddress: null
    // 经度
    property var longitude: null
    // 纬度
    property var latitude: null

    // 控制2d与3d显示
    property bool show3D: true
    // 开启自动驾驶
    property bool enableAutodrive: true
    // 控制导航、收藏按钮
    property bool navigationBtnVisible: false
    // 控制收藏夹显示
    property bool isFavoritesShow: false
    property int favoriteClickTimes: 0
    // 目标路线上的点
    property var targetPoints: []
    // 选中的点
    property var requiredPoints: []
    property int pointCounts: 0
    property double curve_longtitude: 0
    property double curve_latitude: 0

    property double curr_x: 0
    property double curr_y: 0
    property int m_nSpeed: 0

    // 驾驶模式
    property int m_driving_mode: 0

    property var m_driving_mode_item: ["手动驾驶", "自动驾驶", ""]

    property var driveModeImagPath: ["qrc:/resource/asset/image/autodrive/dashboard/activation.png", "qrc:/resource/asset/image/autodrive/dashboard/Ash.png"]

    // Text {
    //     id: text1
    //     x: 338
    //     y: 250
    //     width: 872
    //     height: 358
    //     text: qsTr("auto drive on the way...")
    //     font.pixelSize: 30
    //     font.styleName: "Regular"
    // }
    //  WebView{
    //     id:webView
    //     anchors.centerIn: parent
    //     width: parent.width
    //     height: parent.height
    //     // url:"http://192.168.1.2:8888";
    //     url: "qrc:///resource/asset/html/baiduMap.html";
    //     onLoadProgressChanged: {
    //         if(webView.loadProgress == 100){
    //             console.log("Load Completed !");
    //             var queryStr = "loadMap();";
    //             webView.runJavaScript(queryStr,function(result){
    //                 console.log(result);
    //                 });
    //         }
    //     }
    // }

    // 2d地图部分
    Rectangle {
        id: bdMap_rect
        width: parent.width
        height: parent.height
        visible: !show3D
        property alias popupVisible: popup.visible

        QtObject {
            id: webObject
            WebChannel.id: "webObject"
            signal sendCurrentPos(double curr_x, double curr_y)
            signal sendCurvePath(var paths)
            signal clearPoint()
            signal markDestination(double curr_x, double curr_y)
            signal locate();
            property bool cancleClickEvent: false

            // 槽函数，给html/js 调用
            function notify_current_location(message) {
                sendCurrentPos(curr_x, curr_y)
                return "send ok!"
            }

            function addPoint(address, lng, lat) {
                console.log("位置：" + address)
                console.log("经度：" + lng)
                console.log("纬度：" + lat)
                navigationBtnVisible = true
                favoriteClickTimes = 0
                // 保存选点坐标
                longitude = lng
                latitude = lat
                targetAddress = address
                pointCounts = pointCounts + 1
                CAduProxy.addPoint(lng, lat)
                console.log("addPoint::pointCounts = " + pointCounts)
            }

            function removePoint(lng, lat) {
                pointCounts = pointCounts - 1
                console.log("removePoint::pointCounts = " + pointCounts)
                if(pointCounts == 0) {
                    navigationBtnVisible = false
                }
                CAduProxy.removePoint(lng, lat)
                console.log("navigationBtnVisible= " + navigationBtnVisible)
            }
        }

        Connections {
            target: CAduProxy
            function onNotifyCurrentPosition(x, y) {
                if(show3D)
                    return;
                curr_x = x
                curr_y = y
                if(bdMap_rect.visible) {
                    webObject.sendCurrentPos(x, y)
                }
            }

            // 行驶路线上的点
            function onNotifyTargetCurvePath(data) {
                if(show3D)
                    return;
                console.log("before draw curve path: " + Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss.zzz ddd"));
                for (var i = 0; i < data.length; i++) {
                    var point = new Array()
                    point[0] = data[i][0]
                    point[1] = data[i][1]
                    targetPoints.push(point)
                }
                webObject.sendCurvePath(targetPoints)
                targetPoints = []
                console.log("after draw curve path: " + Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss.zzz ddd"));
            }

            function onNotifyPathUnreachable() {
                if(show3D)
                    return;
                // 路径不可达
                console.log("当前路径不可达")
                bdMap_rect.show();
                webObject.clearPoint();
            }
        }

        WebChannel {
            id: channel
            registeredObjects: [webObject]
        }

        WebEngineView {
            id: webEngineView
            width: parent.width
            height: parent.height
            url: "qrc:///resource/asset/html/gaodeMap.html"
            webChannel: channel
        }

        // 上方收藏夹
        Rectangle {
            id: favorites_rect
            width: 158
            height: 96
            x: 24
            y: 94
            // color: "#202530"
            color: Qt.rgba(0,0,0,0.0)
            radius: 12
            opacity: 1
            visible: enableAutodrive
            Image {
                // width:  48
                // height: 48
                source: "qrc:/resource/asset/image/autodrive/map_icon/Favorite_button.png"
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: favorites_txt_id
                text: qsTr("收藏")
                x: 79
                y: 31
                color: "#333333"
                font.pixelSize: 24
                font.styleName: "Regular"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    isFavoritesShow = !isFavoritesShow
                    if (isFavoritesShow) {
                        // 展开收藏夹
                        showFavorites()
                    }
                }
            }
        }

        // 收藏列表
        Item {
            width: 516
            height: 100 * dataModel.count < 420 ? 420: 100 * dataModel.count
            x: 24
            y: 190
            visible: isFavoritesShow

            Image {
                id: favorites_item_bg
                width: 516
                height: parent.height
                source: "qrc:/resource/asset/image/autodrive/background/favorites_items_bg.png"
            }
       
            ListView {
                id: favorites_list
                width: parent.width
                height: parent.height
                x: 24
                y: 20
                // spacing: 50
                orientation: ListView.Vertical
                model: ListModel {
                    id: dataModel
                }

                delegate: ColumnLayout {
                    id: column_id
                    // Layout.margins: 16
                    // Layout.leftMargin: 16
                    RowLayout {
                        id: row_id
                        width: parent.width
                        spacing: 12
                        Image {
                            id: favorites_location_icon
                            width: 24
                            height: 24
                            y: 24
                            source: "qrc:/resource/asset/image/autodrive/map_icon/favorites_location_icon.png"
                        }
                        Rectangle {
                            id: favorites_item_id
                            width: 376
                            height: 66
                            y: 16
                            color: Qt.rgba(0,0,0,0.0)
                            radius: 4
                            // opacity: 0.8
                            Text {
                                id: target_id
                                width: 376
                                text: qsTr(address)
                                color: "#333333"
                                font.pixelSize: 20
                                font.styleName: "Regular"
                                wrapMode: Text.WrapAnywhere
                                // maximumLineCount: 2
                            }
                        }
                        Image {
                            id: favorites_navigation_icon
                            width: 36
                            height: 36
                            y: 26
                            source: "qrc:/resource/asset/image/autodrive/map_icon/favorites_items_navigation.png"
                            // 点击前往目的地
                            MouseArea {
                                anchors.fill: parent
                                onClicked:  {
                                    console.log("前往位置: ", coordinate.x + "," + coordinate.y)
                                    isFavoritesShow = false
                                    webObject.clearPoint();
                                    // 清空pointCounts
                                    pointCounts = 0
                                    navigationBtnVisible = false
                                    // 清空vetor
                                    CAduProxy.clearAllPoints()
                                    CAduProxy.addPoint(coordinate.x, coordinate.y)
                                    webObject.markDestination(coordinate.x, coordinate.y)
                                    CAduProxy.drivingRoute()
                                }
                            }
                        }
                    }

                    RowLayout {
                        id: row_line_id
                        Layout.topMargin: 16
                        Layout.bottomMargin: 16
                        // Layout.margins: 16
                        Rectangle {
                            width: 468
                            height: 1
                            color: "#EAEBED"
                            radius: 8
                        } 
                    }
                }
            }
        }

        Button {
            id: favorite_btn
            width: 96
            height: 96
            x: 657
            y: 806
            property var image_source: ["qrc:/resource/asset/image/autodrive/map_icon/Not_favorited.png", "qrc:/resource/asset/image/autodrive/map_icon/collect.png"]
            visible: (enableAutodrive && navigationBtnVisible)
            background: Rectangle {
                id: favorite_rect
                width: 96
                height: 96
                color: Qt.rgba(0,0,0,0.0)
                radius: 12
                opacity: 1
                // 收藏按钮
                Image {
                    id: favorite_image
                    // width:  48
                    // height: 48
                    source: favoriteClickTimes %2 === 1 ? favorite_btn.image_source[1] : favorite_btn.image_source[0]
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    // anchors.verticalCenter: parent.verticalCenter
                    // anchors.horizontalCenter: parent.horizontalCenter
                }
                Text{
                    id: favorite_txt
                    text: favoriteClickTimes %2 === 1 ? qsTr("已收藏") : qsTr("收藏")
                    y: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                    font.styleName: "Regular"
                    color: "#333333"
                    // verticalAlignment: Text.AlignVCenter
                    // horizontalAlignment: Text.AlignHCenter
                }
            }
            onClicked: {
                favoriteClickTimes += 1
                isFavoritesShow = false
                if(favoriteClickTimes %2 === 1) {
                    // 奇数次
                    addToFavorites()
                } else {
                    removeFromFavorites()
                }
            }

             // 添加到收藏夹
            function addToFavorites() {
                // console.log("当前点添加到收藏夹！！！")
                ConfigManager.saveToFavorites(key, targetAddress, longitude, latitude)
            }

            function removeFromFavorites() {
                ConfigManager.removeFromFavorites(key, targetAddress, longitude, latitude)
            }
        }
        
        Button {
            id: navigation_btn
            width: 216
            height: 96
            x: 777
            y: 806
            visible: (enableAutodrive && navigationBtnVisible)
            background: Rectangle {
                id: navigation_rect
                width: 216
                height: 96
                color: Qt.rgba(0,0,0,0.0)
                opacity: 1
                radius: 12

                // 导航按钮
                Image {
                    // width:  48
                    // height: 48
                    y: 4
                    source: "qrc:/resource/asset/image/autodrive/map_icon/Favorite_Navigation_Background.png"
                    fillMode: Image.PreserveAspectFit
                }
                Text{
                    text: qsTr("开始导航")
                    anchors.centerIn: parent
                    font.pixelSize: 28
                    y: 25
                    font.weight: Font.DemiBold
                    font.styleName: "Regular"
                    color: "#ffffff"
                    // verticalAlignment: Text.AlignVCenter
                    // horizontalAlignment: Text.AlignHCenter
                }
            }
            onClicked: {
                // TODO  开启导航
                navigate()
            }

            function navigate() {
                console.log("导航前往这些目的地")
                // 清空pointCounts
                pointCounts = 0
                navigationBtnVisible = false
                isFavoritesShow = false
                CAduProxy.drivingRoute()
            }
        }

        // 规划错误提示
        Popup {
            id: popup
            width: 300
            height: 60
            focus: true
            x: 700
            y: 600
            background: Rectangle {
                id: background
                color: Qt.rgba(64/255, 64/255, 64/255, 1)
                radius: 8
                border.color: Qt.rgba(64/255, 64/255, 64/255, 1)
                border.width: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                Label {
                    id: label
                    text: qsTr("当前路径不可达！")
                    font.pixelSize: 22
                    font.italic: true
                    color: "#ffffff"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
        Timer {
            id: timer_id
            interval: 2000;
            running: false;
            repeat: false;
            property real index: -1;
            onTriggered: {
                bdMap_rect.hide()
                timer_id.stop()
            }
        }

        function show()
        {
            popupVisible = true
            timer_id.start()
        }

        function hide()
        {
            popupVisible = false
        }
    }
    FocusScope
    {
        width: parent.width
        height: parent.height

        AutodriveItem2
        {
            id: autodriveItem
            anchors.fill: parent
            visible: show3D
            focus: visible
        }

        FPSText{
            id: fps_text
            width: 200
            height: 100
            anchors.right: parent.right
            anchors.top: parent.top

            Text {
                anchors.centerIn: parent
                text: 'fps: ' + fps_text.fps.toFixed(2)
            }
        }
    }

    // 自动驾驶、手动驾驶开关
    Rectangle {
        id: auto_drive_rect
        width: 200
        height: 60
        x: 180
        y: 924
        // color: "#5B89FF"
        color: Qt.rgba(0,0,0,0.0)
        radius: 8
        state: "selected"
        visible: ApplicationInfoVModel.vehicle === ApplicationInfoVModel.PassengeVehicle

        Image {
            id: autodrive_img
            source: m_driving_mode === DrivingModeEnum.MANUAL_DRIVE ? driveModeImagPath[1] : driveModeImagPath[0]
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: auto_drive_txt
            width: 95
            height: 34
            text: m_driving_mode === DrivingModeEnum.MANUAL_DRIVE ? qsTr("手动驾驶") : qsTr("自动驾驶")
            color: "#ffffff"
            font.pixelSize: 24
            font.styleName: "Regular"
            // horizontalAlignment : Text.AlignHCenter
            // verticalAlignment : Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                // if(auto_drive_rect.state == 'selected') {
                //     return;
                // } else {
                //     auto_drive_rect.state = 'selected';
                //     // manual_drive_rect.color = "#17365F"
                //     // auto_drive_rect.color = "#5B89FF"
                //     manual_drive_rect.state = "unselected"
                //     // TODO 开启自动驾驶
                //     switchDrivingMode(DrivingModeEnum.ATUO_DRIVE)
                // }
            }
        }
    }

 
    // Rectangle {
    //     id: manual_drive_rect
    //     width: 130
    //     height: 52
    //     // color: "#17365F"
    //     color: Qt.rgba(0,0,0,0.0)
    //     x: 1300
    //     y: 887
    //     radius: 12
    //     visible: ApplicationInfoVModel.vehicle === ApplicationInfoVModel.PassengeVehicle

    //     Image {
    //         id: manualdrive_img
    //         source: manual_drive_rect.state == 'selected' ? driveModeImagPath[0] : driveModeImagPath[1]
    //         fillMode: Image.PreserveAspectFit
    //     }

    //     Text {
    //         id: manual_drive_txt
    //         width: 95
    //         height: 34
    //         text: qsTr("手动驾驶")
    //         color: "#ffffff"
    //         font.pixelSize: 24
    //         font.styleName: "Regular"
    //         anchors.horizontalCenter: parent.horizontalCenter
    //         anchors.verticalCenter: parent.verticalCenter
    //     }
    //     MouseArea {
    //         anchors.fill: parent
    //         onClicked: {
    //             if(manual_drive_rect.state == 'selected') {
    //                 return;
    //             } else {
    //                 manual_drive_rect.state = 'selected';
    //                 // auto_drive_rect.color = "#17365F"
    //                 // manual_drive_rect.color = "#5B89FF"
    //                 auto_drive_rect.state = "unselected"
    //                 // TODO 开启手动驾驶
    //                 switchDrivingMode(DrivingModeEnum.MANUAL_DRIVE)
    //             }
    //         }
    //     }
    // }

    Button {
        // width: 60
        // height: 60
        id: switch_btn
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: show3D == false ? 172 : 180 
        anchors.bottomMargin: show3D == false ? 84 : 96
        visible: enableAutodrive && ApplicationInfoVModel.vehicle === ApplicationInfoVModel.PassengeVehicle
        property var image_source: ["qrc:/resource/asset/image/autodrive/dashboard/Map-2D.png", "qrc:/resource/asset/image/autodrive/dashboard/map.png"]
        background: Image {
            source: show3D == false ? switch_btn.image_source[0] : switch_btn.image_source[1]
        }

        function switchMap() {
            show3D = !show3D
            isFavoritesShow = false
            webObject.locate()
            if(!show3D) {
                // 2d map
                gConfig.statusBarColor = "#1d1d1d"
            } else {
                gConfig.statusBarColor = Qt.rgba(0,0,0,0.0)
            }
        }
        onClicked: switchMap()
        // Component.onCompleted: jump()
    }

    // 交通信号灯
    Rectangle {
        id: traffic_light_rect
        visible: show3D
        property int index: 0
        width: index == 0 ? 252 : 144
        height: 72
        //x: index == 0 ? 758 : 813
        
        anchors.horizontalCenter: parent.horizontalCenter
        
        y: 66
        color: Qt.rgba(0,0,0,0.0)
        radius: 4

        property var gray_image_source: "qrc:/resource/asset/image/autodrive/light/grey.png"
        property var uturn_image_source: ["qrc:/resource/asset/image/autodrive/light/red_light/uturn.png", "qrc:/resource/asset/image/autodrive/light/green_light/uturn.png", "qrc:/resource/asset/image/autodrive/light/yellow_light/uturn.png"]
        property var left_image_source: ["qrc:/resource/asset/image/autodrive/light/red_light/left.png", "qrc:/resource/asset/image/autodrive/light/green_light/left.png", "qrc:/resource/asset/image/autodrive/light/yellow_light/left.png"]
        property var forward_image_source: ["qrc:/resource/asset/image/autodrive/light/red_light/straight.png", "qrc:/resource/asset/image/autodrive/light/green_light/straight.png", "qrc:/resource/asset/image/autodrive/light/yellow_light/straight.png"]
        property var right_image_source: ["qrc:/resource/asset/image/autodrive/light/red_light/right.png", "qrc:/resource/asset/image/autodrive/light/green_light/right.png", "qrc:/resource/asset/image/autodrive/light/yellow_light/right.png"]
        property var handle_all_lights: [false, false, false, false]
        // 4个交通信号灯
        Image {
            width:  252
            height: 72
            id: traffic_light_img4
            visible: traffic_light_rect.index == 0 ? true : false
            source: "qrc:/resource/asset/image/autodrive/light/light_background.png"
            fillMode: Image.PreserveAspectFit
            property var image_ids: [uturn_img4, left_img4, forward_img4, right_img4]
            
            Image {
                id: uturn_img4
                width: 48
                height: 48
                x: 12
                y: 12
                source: traffic_light_rect.gray_image_source
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: left_img4
                width: 48
                height: 48
                y: 12
                source: traffic_light_rect.gray_image_source
                anchors.left: uturn_img4.right
                anchors.leftMargin: 12
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: forward_img4
                width: 48
                height: 48
                y: 12
                source: traffic_light_rect.gray_image_source
                anchors.left: left_img4.right
                anchors.leftMargin: 12
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: right_img4
                width: 48
                height: 48
                y: 12
                source: traffic_light_rect.gray_image_source
                anchors.left: forward_img4.right
                anchors.leftMargin: 12
                fillMode: Image.PreserveAspectFit
            }
        }

        Image {
            id: straight_img
            property var image_source: ["qrc:/resource/asset/image/autodrive/light/red_light/red_one.png", "qrc:/resource/asset/image/autodrive/light/green_light/green_one.png", "qrc:/resource/asset/image/autodrive/light/yellow_light/yellow_one.png", "qrc:/resource/asset/image/autodrive/light/grey.png"]
            visible: traffic_light_rect.index == 1 ? true : false
            source: image_source[0]
            fillMode: Image.PreserveAspectFit
        }

        Connections {
            target: CAduProxy
            function onNotifyTrafficLight(traffic_light) {
                if(traffic_light.length > 1)
                    traffic_light_rect.index = 0
                for(var i=0; i<traffic_light.length; i++) {
                    var direction = traffic_light[i][0]
                    var color = traffic_light[i][1]
                    handleTrafficLight(direction, color, traffic_light_rect.index);
                }
                // 处理本次信号未收到的交通灯信息
                handleRemainTrafficLight()
            }

            function handleTrafficLight(direction, color, index) {
                // 处理只有1个方向的信号灯
                if(index == 1) {
                    if(color == TrafficLightEnum.RED) {
                        straight_img.source = image_source[0]
                    } else if(color == TrafficLightEnum.YELLOW) {
                        straight_img.source = image_source[2]
                    } else if(color == TrafficLightEnum.GREEN) {
                        straight_img.source = image_source[1]
                    } else if(color == TrafficLightEnum.UNKNOWN) {
                        straight_img.source = image_source[3]
                    }
                } else {
                    switch(direction) {
                        case TrafficLightEnum.FORWARD:
                            if(color == TrafficLightEnum.RED) {
                                traffic_light_img4.image_ids[2].source = traffic_light_rect.forward_image_source[0]
                            } else if(color == TrafficLightEnum.YELLOW) {
                                traffic_light_img4.image_ids[2].source = traffic_light_rect.forward_image_source[2]
                            } else if(color == TrafficLightEnum.GREEN) {
                                traffic_light_img4.image_ids[2].source = traffic_light_rect.forward_image_source[1]
                            } else if(color == TrafficLightEnum.UNKNOWN) {
                                traffic_light_img4.image_ids[2].source = traffic_light_rect.gray_image_source
                            }
                            traffic_light_rect.handle_all_lights[2] = true
                            break;
                        case TrafficLightEnum.LEFT:
                            if(color == TrafficLightEnum.RED) {
                                traffic_light_img4.image_ids[1].source = traffic_light_rect.left_image_source[0]
                            } else if(color == TrafficLightEnum.YELLOW) {
                                traffic_light_img4.image_ids[1].source = traffic_light_rect.left_image_source[2]
                            } else if(color == TrafficLightEnum.GREEN) {
                                traffic_light_img4.image_ids[1].source = traffic_light_rect.left_image_source[1]
                            } else if(color == TrafficLightEnum.UNKNOWN) {
                                traffic_light_img4.image_ids[1].source = traffic_light_rect.gray_image_source
                            }
                            traffic_light_rect.handle_all_lights[1] = true
                            break;
                        case TrafficLightEnum.RIGHT: 
                            if(color == TrafficLightEnum.RED) {
                                traffic_light_img4.image_ids[3].source = traffic_light_rect.right_image_source[0]
                            } else if(color == TrafficLightEnum.YELLOW) {
                                traffic_light_img4.image_ids[3].source = traffic_light_rect.right_image_source[2]
                            } else if(color == TrafficLightEnum.GREEN) {
                                traffic_light_img4.image_ids[3].source = traffic_light_rect.right_image_source[1]
                            } else if(color == TrafficLightEnum.UNKNOWN) {
                                traffic_light_img4.image_ids[3].source = traffic_light_rect.gray_image_source
                            }
                            traffic_light_rect.handle_all_lights[3] = true
                            break;
                        case TrafficLightEnum.UTURN:
                            if(color == TrafficLightEnum.RED) {
                                traffic_light_img4.image_ids[0].source = traffic_light_rect.uturn_image_source[0]
                            } else if(color == TrafficLightEnum.YELLOW) {
                                traffic_light_img4.image_ids[0].source = traffic_light_rect.uturn_image_source[2]
                            } else if(color == TrafficLightEnum.GREEN) {
                                traffic_light_img4.image_ids[0].source = traffic_light_rect.uturn_image_source[1]
                            } else if(color == TrafficLightEnum.UNKNOWN) {
                                traffic_light_img4.image_ids[0].source = traffic_light_rect.gray_image_source
                            }
                            traffic_light_rect.handle_all_lights[0] = true
                            break;
                        default:
                            traffic_light_img4.image_ids[2].source = traffic_light_rect.gray_image_source
                            traffic_light_img4.image_ids[1].source = traffic_light_rect.gray_image_source
                            traffic_light_img4.image_ids[3].source = traffic_light_rect.gray_image_source
                            traffic_light_img4.image_ids[0].source = traffic_light_rect.gray_image_source
                            break;
                    }
                }
            }

            function handleRemainTrafficLight() {
                for(var i = 0; i < traffic_light_rect.handle_all_lights.length; i++) {
                    if(traffic_light_rect.handle_all_lights[i] == false) {
                        image_ids[i].source = traffic_light_rect.gray_image_source
                        traffic_light_rect.handle_all_lights[i] = true
                    }
                }
                // 重置所有信号灯
                traffic_light_rect.handle_all_lights = [false, false, false, false]
            }

            function onNotifyVehicleDriveMode(mode) {
                m_driving_mode = mode;
            }
        }

    }

    Rectangle{
        id: speedView
        width: 144
        height: 144
        radius: 12
        color: "#BF1B6DE0"
        visible: ApplicationInfoVModel.vehicle === ApplicationInfoVModel.MiniBusVehicle
        anchors.left: parent.left
        anchors.leftMargin: 64
        anchors.top: parent.top
        anchors.topMargin: 150
        ColumnLayout{
            anchors.centerIn: parent
            Text{
                id: speedLabel
                text: qsTr(m_nSpeed.toString())
                font.pixelSize: 80
                Layout.preferredWidth: 144
                Layout.preferredHeight: 72
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "#FFFFFF"
            }
            Text{
                text: qsTr("km/h")
                font.pixelSize: 36
                Layout.preferredWidth: 144
                Layout.preferredHeight: 36
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "#DBE4EC"
            }
        }

        // Connections {
        //     target: CAduProxy
        //     function onNotifyVehicleDriveSpeed(speed) {
        //         speedLabel.text = parseInt(speed);
        //     }
        // }
    }
    // 仪表盘灯光
    Rectangle {
        id: dashboard_rect
        width: parent.width
        height: 156
        color: Qt.rgba(0,0,0,0.0)
        anchors.bottom: bdMap_rect.bottom
        visible: ApplicationInfoVModel.vehicle === ApplicationInfoVModel.PassengeVehicle
        Loader {
            id: dashboard_loader
            anchors.fill: parent
            source: dashboard_rect.visible === true ? "qrc:/resource/qml/autodrive/dashboard.qml" : ""
        }
    }

    // 切换驾驶模式
    function switchDrivingMode(driving_model) {
        CAduProxy.switchDrivingMode(driving_model)
        console.log("driving mode is: " + driving_model);
        if(driving_model == DrivingModeEnum.MANUAL_DRIVE) {
            enableAutodrive = false
            webObject.clearPoint()
            // 清空vetor
            CAduProxy.clearAllPoints()
            pointCounts = 0
            webObject.cancleClickEvent = true
            show3D = false
            isFavoritesShow = false
            navigationBtnVisible = false
        } else {
            enableAutodrive = true
            webObject.cancleClickEvent = false
        }
    }

    // Component.onCompleted: {
    //     console.log("autodrive page create completed.")
    // }
    Component.onDestruction: {
        console.log("autodrive page destruction.")
    }

    function showFavorites() {
        ConfigManager.showFavorites(key)
    }

    Connections {
        target: ConfigManager
        function onClearFavorites() {
            dataModel.clear()
        }
        
        function onSendFavorites(addr, lng, lat) {
            // console.log("addr: " + addr)
            dataModel.append({
                "address": addr,
                "coordinate": {
                    "x": lng,
                    "y": lat
                }
            })
        }
    }

    Connections {
        target: CAduProxy
        function onNotifyVehicleDriveSpeed(speed) {
            // speedLabel.text = parseInt(speed);
            m_nSpeed = speed
        }
    }
}
