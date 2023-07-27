import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import ".."
import "../.."

Item {
    id: root
    anchors.fill: parent
    // 样式属性
    property alias popupVisible: popup.visible
    property alias contentItem: popup.contentItem
    property color barColor: "#1d1d1d"
    property alias backgroundItem: background
    property real backgroundWidth: 240
    property real backgroundHeight: 40
    property color borderColor: barColor
    property real borderWidth: 0
    // 文本属性
    property string textData: "hmi有新版本V1.2.2"
    property real verticalOffset: 24
    //矩形旋转45度，一半被toolTip遮住(重合)，另一半三角形和ToolTip组成一个带箭头的ToolTip
    Rectangle {
        id: bar
        visible: popup.visible
        rotation: 45
        width: verticalOffset
        height: width
        color: barColor
        border.color: borderColor
        x: 50
        y: 10
        //水平居中
        //        anchors.horizontalCenter: parent.horizontalCenter
        //垂直方向上，由ToolTip的y值，决定位置
        //        anchors.verticalCenter: parent.bottom
        //        anchors.verticalCenterOffset: verticalOffset
    }

    Popup {
        id: popup
        width: backgroundWidth
        height: backgroundHeight
        focus: true
        background: Rectangle {
            id: background
            color: barColor
            radius: 8
            border.color: borderColor
            border.width: borderWidth
            Label {
                id: label
                text: qsTr(textData)
                font.pixelSize: 22
                font.italic: true
                color: "#2b2b2b"
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
            console.log("timer trigger", index)
            hide()
            timer_id.stop()
        }
    }

    Connections {
        target: window
        function onQmlSignalShowDialog(pkg_name, old_version, new_version)
        {
            // 有新版本
            // console.log("onQmlSignalShowDialog, name: " + pkg_name + ", old version: "
            // + old_version + ", new version: " + new_version);
            textData = pkg_name + "有新版本为" + new_version;
            // 显示提示框
            show()
        }
    }

    function show()
    {
        console.log("show dialog")
        // popup.x = (root.width - popup.width) / 2
        // popup.y = root.height + verticalOffset
        popup.x = bar.x - popup.width / 2
        popup.y = bar.height / 2
        popupVisible = true
        timer_id.start()
    }

    function hide()
    {
        console.log("close dialog")
        popupVisible = false
    }

    Component.onCompleted: {
        // show()
    }
}
