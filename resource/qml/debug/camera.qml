import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import Cowa.ImageView 1.0


Item {
    id: camera_item_id
    width: 1446
    height: 960

    property int indexTemp: 0
    property int configIndex: gConfig.currentIndex
    // 左右切换tab按钮
    // 上一个tab
    property var lastTab: ["qrc:/resource/asset/image/debug/dark/left-button.png", "qrc:/resource/asset/image/debug/light/left-button.png"]
    // 下一个tab
    property var nextTab: ["qrc:/resource/asset/image/debug/dark/right-button.png", "qrc:/resource/asset/image/debug/light/right-button.png"]
    // 背景
    property var camera_background: ["qrc:/resource/asset/image/debug/light/camera_loading.png", "qrc:/resource/asset/image/debug/dark/camera_loading.png"]
    property var video_opretaion_image: ["qrc:/resource/asset/image/debug/light/play_icon.png", "qrc:/resource/asset/image/debug/light/pause_icon.png"]
    property var video_operation: ["播放", "暂停"]
    // TODO 
    property var resolution : 1 // 分辨率
    property var camera_show: [false, false, false, false, false, false]
    property int delay: 0   // 延迟
    property int frameRate: 0   // 帧率
    property int codeRate: 0    // 码率
    

    Rectangle {
        id: rootid
        x: 0
        y: 0
        width: parent.width
        height: parent.height

        TabView {
            id: tabview_id
            anchors.fill: parent
            property string selected_color : gConfig.selectedColor
            property string unselected_color : gConfig.tabButtonColor[configIndex]

            style: TabViewStyle {
                frameOverlap: 1
                tab: Rectangle { // for each tab
                    color: styleData.selected ? tabview_id.selected_color : gConfig.tabButtonColor[configIndex]
                    implicitWidth: 220
                    implicitHeight: 90
                    radius: 2
                    x: 22
                    Text {
                        width: 200
                        height: 40
                        anchors.centerIn: parent
                        verticalAlignment : Text.AlignVCenter
                        horizontalAlignment : Text.AlignHCenter
                        text: styleData.title
                        font.pixelSize: styleData.selected ? 32 : 28
                        color: gConfig.textColor[configIndex]
                    }
                }

                tabBar: Rectangle {
                    color: gConfig.tabButtonColor[configIndex]
                }
            }

            property int myIndex:indexTemp
                        currentIndex: 0
            onMyIndexChanged: {
                currentIndex = myIndex
            }

            onCurrentIndexChanged: {
                indexTemp = currentIndex
            }

            Component.onCompleted : {
                addTab("前环视", front_surround_id)
                addTab("后环视", back_surround_id)
                addTab("左环视", left_surround_id)
                addTab("右环视", right_surround_id)
                addTab("红绿灯", traffic_lights_id)
                addTab("1号周视-左后", panorama_1_id)
            }
        }

        // 前环视
        Component {
            id : front_surround_id
            Rectangle {
                width: 1446
                height: 870
                color: gConfig.background[configIndex]
                // 背景图，默认显示
                Image {
                    width: parent.width
                    height: 870
                    source:  camera_item_id.camera_background[configIndex]
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                }

                // TODO 切换相机时显示该数据
                Rectangle {
                    width: parent.width
                    height: 870
                    // TODO 有相机数据才显示
                    // visible: camera_show[0]
                    color: gConfig.background[configIndex]
                    // color: Qt.rgba(0,0,0,0.0)
                    CWImageView {
                        id: cimage_id
                        width: parent.width
                        height: 870
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        Component.onCompleted: {
                            cimage_id.updateImage()
                        }
                    }
                    // 上方文字
                    Item {
                        x: 489
                        y: 40
                        Rectangle {
                            id: delay_rect
                            width: 146
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            Text{
                                text: qsTr("延迟：" + delay.toString() + "ms")
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }

                        Rectangle {
                            id: frame_rate_rect
                            width: 99
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            anchors.left: delay_rect.right
                            anchors.leftMargin: 32
                            Text{
                                text: qsTr("帧率：" + frameRate.toString())
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }

                        Rectangle {
                            id: code_rate_rect
                            width: 160
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            anchors.left: frame_rate_rect.right
                            anchors.leftMargin: 32
                            Text{
                                text: qsTr("码率：" + codeRate.toString()+"mb/s")
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }
                    }

                    // 中间手势
                    Item {
                        // 左手势
                        Image {
                            width: 106
                            height: 164
                            x: 246
                            y: 298
                            source:  "qrc:/resource/asset/image/debug/light/Gesture-slide-left.png"
                            fillMode: Image.PreserveAspectFit
                            // anchors.fill: parent
                            MouseArea  {
                                anchors.fill:  parent
                                onPressed:  {
                                    console.log("鼠标按下");
                                }
                            }
                        }
                        // 右手势
                        Image {
                            width: 106
                            height: 164
                            x: 1208
                            y: 298
                            source:  "qrc:/resource/asset/image/debug/light/Gesture-slide-right.png"
                            fillMode: Image.PreserveAspectFit
                            // anchors.fill: parent
                        }
                        
                    }

                    Button {
                        id: play_video_id
                        x: 563
                        y: resolution == 1 ? 702:730
                        background: Rectangle {
                            width: 320
                            height: 82
                            color: Qt.rgba(0,0,0,0.0)
                            Image {
                                width: parent.width
                                height: parent.height
                                // TODO
                                source:  camera_item_id.video_opretaion_image[0]
                                fillMode: Image.PreserveAspectFit
                                anchors.fill: parent
                            }
                            Text{
                                x: 156
                                text: qsTr(video_operation[0].toString())
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 28
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }
                    }
                }
            }
        }

        // 后环视
        Component {
            id : back_surround_id
            Rectangle {
                width: 1446
                height: 870
                color: gConfig.background[configIndex]
                // 背景图，默认显示
                Image {
                    width: parent.width
                    height: 870
                    source:  camera_item_id.camera_background[configIndex]
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                }

                // TODO 切换相机时显示该数据
                Rectangle {
                    width: parent.width
                    height: 870
                    // TODO 有相机数据才显示
                    // visible: camera_show[0]
                    color: gConfig.background[configIndex]
                    // color: Qt.rgba(0,0,0,0.0)
                    CWImageView {
                        id: cimage_id
                        width: parent.width
                        height: 870
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        Component.onCompleted: {
                            cimage_id.updateImage()
                        }
                    }
                    // 上方文字
                    Item {
                        x: 489
                        y: 40
                        Rectangle {
                            id: delay_rect
                            width: 146
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            Text{
                                text: qsTr("延迟：" + delay.toString() + "ms")
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }

                        Rectangle {
                            id: frame_rate_rect
                            width: 99
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            anchors.left: delay_rect.right
                            anchors.leftMargin: 32
                            Text{
                                text: qsTr("帧率：" + frameRate.toString())
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }

                        Rectangle {
                            id: code_rate_rect
                            width: 160
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            anchors.left: frame_rate_rect.right
                            anchors.leftMargin: 32
                            Text{
                                text: qsTr("码率：" + codeRate.toString()+"mb/s")
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }
                    }

                    // 中间手势
                    Item {
                        // 左手势
                        Image {
                            width: 106
                            height: 164
                            x: 246
                            y: 298
                            source:  "qrc:/resource/asset/image/debug/light/Gesture-slide-left.png"
                            fillMode: Image.PreserveAspectFit
                            // anchors.fill: parent
                            MouseArea  {
                                anchors.fill:  parent
                                onPressed:  {
                                    console.log("鼠标按下");
                                }
                            }
                        }
                        // 右手势
                        Image {
                            width: 106
                            height: 164
                            x: 1208
                            y: 298
                            source:  "qrc:/resource/asset/image/debug/light/Gesture-slide-right.png"
                            fillMode: Image.PreserveAspectFit
                            // anchors.fill: parent
                        }
                        
                    }

                    Button {
                        id: play_video_id
                        x: 563
                        y: resolution == 1 ? 702:730
                        background: Rectangle {
                            width: 320
                            height: 82
                            color: Qt.rgba(0,0,0,0.0)
                            Image {
                                width: parent.width
                                height: parent.height
                                // TODO
                                source:  camera_item_id.video_opretaion_image[0]
                                fillMode: Image.PreserveAspectFit
                                anchors.fill: parent
                            }
                            Text{
                                x: 156
                                text: qsTr(video_operation[0].toString())
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 28
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }
                    }
                }
            }
        }

        // 左环视
        Component {
            id : left_surround_id
            Rectangle {
                width: 1446
                height: 870
                color: gConfig.background[configIndex]
                // 背景图，默认显示
                Image {
                    width: parent.width
                    height: 870
                    source:  camera_item_id.camera_background[configIndex]
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                }

                // TODO 切换相机时显示该数据
                Rectangle {
                    width: parent.width
                    height: 870
                    // TODO 有相机数据才显示
                    // visible: camera_show[0]
                    color: gConfig.background[configIndex]
                    // color: Qt.rgba(0,0,0,0.0)
                    CWImageView {
                        id: cimage_id
                        width: parent.width
                        height: 870
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        Component.onCompleted: {
                            cimage_id.updateImage()
                        }
                    }
                    // 上方文字
                    Item {
                        x: 489
                        y: 40
                        Rectangle {
                            id: delay_rect
                            width: 146
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            Text{
                                text: qsTr("延迟：" + delay.toString() + "ms")
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }

                        Rectangle {
                            id: frame_rate_rect
                            width: 99
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            anchors.left: delay_rect.right
                            anchors.leftMargin: 32
                            Text{
                                text: qsTr("帧率：" + frameRate.toString())
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }

                        Rectangle {
                            id: code_rate_rect
                            width: 160
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            anchors.left: frame_rate_rect.right
                            anchors.leftMargin: 32
                            Text{
                                text: qsTr("码率：" + codeRate.toString()+"mb/s")
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }
                    }

                    // 中间手势
                    Item {
                        // 左手势
                        Image {
                            width: 106
                            height: 164
                            x: 246
                            y: 298
                            source:  "qrc:/resource/asset/image/debug/light/Gesture-slide-left.png"
                            fillMode: Image.PreserveAspectFit
                            // anchors.fill: parent
                            MouseArea  {
                                anchors.fill:  parent
                                onPressed:  {
                                    console.log("鼠标按下");
                                }
                            }
                        }
                        // 右手势
                        Image {
                            width: 106
                            height: 164
                            x: 1208
                            y: 298
                            source:  "qrc:/resource/asset/image/debug/light/Gesture-slide-right.png"
                            fillMode: Image.PreserveAspectFit
                            // anchors.fill: parent
                        }
                        
                    }

                    Button {
                        id: play_video_id
                        x: 563
                        y: resolution == 1 ? 702:730
                        background: Rectangle {
                            width: 320
                            height: 82
                            color: Qt.rgba(0,0,0,0.0)
                            Image {
                                width: parent.width
                                height: parent.height
                                // TODO
                                source:  camera_item_id.video_opretaion_image[0]
                                fillMode: Image.PreserveAspectFit
                                anchors.fill: parent
                            }
                            Text{
                                x: 156
                                text: qsTr(video_operation[0].toString())
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 28
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }
                    }
                }
            }
        }

        // 右环视
        Component {
            id : right_surround_id
            Rectangle {
                width: 1446
                height: 870
                color: gConfig.background[configIndex]
                // 背景图，默认显示
                Image {
                    width: parent.width
                    height: 870
                    source:  camera_item_id.camera_background[configIndex]
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                }

                // TODO 切换相机时显示该数据
                Rectangle {
                    width: parent.width
                    height: 870
                    // TODO 有相机数据才显示
                    // visible: camera_show[0]
                    color: gConfig.background[configIndex]
                    // color: Qt.rgba(0,0,0,0.0)
                    CWImageView {
                        id: cimage_id
                        width: parent.width
                        height: 870
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        Component.onCompleted: {
                            cimage_id.updateImage()
                        }
                    }
                    // 上方文字
                    Item {
                        x: 489
                        y: 40
                        Rectangle {
                            id: delay_rect
                            width: 146
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            Text{
                                text: qsTr("延迟：" + delay.toString() + "ms")
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }

                        Rectangle {
                            id: frame_rate_rect
                            width: 99
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            anchors.left: delay_rect.right
                            anchors.leftMargin: 32
                            Text{
                                text: qsTr("帧率：" + frameRate.toString())
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }

                        Rectangle {
                            id: code_rate_rect
                            width: 160
                            height: 34
                            color: Qt.rgba(0,0,0,0.0)
                            anchors.left: frame_rate_rect.right
                            anchors.leftMargin: 32
                            Text{
                                text: qsTr("码率：" + codeRate.toString()+"mb/s")
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 24
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }
                    }

                    // 中间手势
                    Item {
                        // 左手势
                        Image {
                            width: 106
                            height: 164
                            x: 246
                            y: 298
                            source:  "qrc:/resource/asset/image/debug/light/Gesture-slide-left.png"
                            fillMode: Image.PreserveAspectFit
                            // anchors.fill: parent
                            MouseArea  {
                                anchors.fill:  parent
                                onPressed:  {
                                    console.log("鼠标按下");
                                }
                            }
                        }
                        // 右手势
                        Image {
                            width: 106
                            height: 164
                            x: 1208
                            y: 298
                            source:  "qrc:/resource/asset/image/debug/light/Gesture-slide-right.png"
                            fillMode: Image.PreserveAspectFit
                            // anchors.fill: parent
                        }
                        
                    }

                    Button {
                        id: play_video_id
                        x: 563
                        y: resolution == 1 ? 702:730
                        background: Rectangle {
                            width: 320
                            height: 82
                            color: Qt.rgba(0,0,0,0.0)
                            Image {
                                width: parent.width
                                height: parent.height
                                // TODO
                                source:  camera_item_id.video_opretaion_image[0]
                                fillMode: Image.PreserveAspectFit
                                anchors.fill: parent
                            }
                            Text{
                                x: 156
                                text: qsTr(video_operation[0].toString())
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 28
                                font.styleName: "Regular"
                                color: "#FFFFFF"
                            }
                        }
                    }
                }
            }
        }

        // 红绿灯
        Component {
            id : traffic_lights_id
            Rectangle {
            }
            
        }

        // 1号周视-左后
        Component {
            id : panorama_1_id
            Rectangle {
            }
            
        }

        // TODO 暂时不用
        function addCameraElement(x, y, width, height, image_url, resolution, index) {
            var component = Qt.createComponent("qrc:///resource/qml/debug/CameraElement.qml")
            if (component.status === Component.Ready)
            {
                var element = component.createObject({
                    "x": x,
                    "y": y,
                    "width": width,
                    "height": height,
                    "camera_image_url": image_url,
                    "resolution": resolution,
                    "configIndex": index
                })
            }
        }
    }

    Button{
        id: lastTab_page_id
        x: 16
        y: 0
        width: 26
        height: 90
        background: Rectangle {
            color: gConfig.tabButtonColor[configIndex]
            Image {
                width: 26
                height: 26
                anchors.verticalCenter: parent.verticalCenter
                source:  lastTab[configIndex]
            }
        }
        onClicked: {
            var lastIndex = indexTemp
            if (indexTemp == 0){
                indexTemp = 0
            } else{
                indexTemp--
            }
            camera_item_id.updateCameraShow(lastIndex, indexTemp)
        }
    }

    Button{
        id: nextTab_page_id
        x: 1408
        y: 0
        width: 26
        height: 90
        background: Rectangle {
            // color: "#3b3b3b"
            color: gConfig.tabButtonColor[configIndex]
            Image {
                width: 26
                height: 26
                anchors.verticalCenter: parent.verticalCenter
                source:  nextTab[configIndex]
            }
        }
        onClicked: {
            var lastIndex = indexTemp
            if (indexTemp >= 5) {
                indexTemp = 5
            } else {
                indexTemp++
            }
            camera_item_id.updateCameraShow(lastIndex, indexTemp)
        }
    }

    function updateCameraShow(last, current) {
        console.log("last = " + last + ", current = " + current);
        camera_show[last] = false
        camera_show[current] = true
    }

}
