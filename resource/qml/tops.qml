import QtQuick 2.0


// 上装页面的主体部分
Item {
    width: 1770
    height: 1080

    // 仪表盘
    Rectangle {
        id: dashboard_rectangle_id
        width: 664
        height: 350
        color: "#141414"
        Loader {
            id: dashboard_loader_id
            anchors.fill: parent
            source: "qrc:///resource/qml/tops/dashboard.qml"
        }
    }

    // 左下角的灯光屏幕 设置
    Rectangle {
        id: lightscreen_rectangle_id
        width: 664
        height: 733
        y:347
        color: "#141414"
        Loader {
            id: lightscreen_loader_id
            anchors.fill: parent
            source: "qrc:///resource/qml/tops/lightscreen.qml"
        }
    }

    // 右侧的上装操作
    Rectangle {
        x: dashboard_rectangle_id.width + 24
        width: parent.width - x
        height: parent.height
        color: "#141414"
        Loader {
            id: top_work_loader_id
            anchors.fill: parent
            source: "qrc:///resource/qml/tops/topsclean.qml"
        }
    }

}
