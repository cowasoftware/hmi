import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.15
import CAduProxyClass 1.0
import TrafficLightTypeEnum 1.0
import WorkClass 1.0
import Cowa.HMI2.VModel 1.0

Item {
    id: autodrive_dashboard_id
    width: 1770
    height: 261

    property int m_nSpeed: 0
    // 方向盘转角、刹车状态
    property int m_drive_steer: 0
    property int m_drive_throttle: 0

    // 仪表盘部分
    Image {
        id: dashboard_background
        width: parent.width
        height: parent.height
        source: "qrc:/resource/asset/image/autodrive/dashboard/bg.png"
        smooth: true
    }

    // 2、速度表
    Text {
        id: speed_id
        width: 84
        height: 97
        x: 904
        text: qsTr(root_id.m_nSpeed.toString())
        color: "#ffffff"
        font.pixelSize: 80
        font.styleName: "Regular"
        verticalAlignment : Text.AlignVCenter
        horizontalAlignment : Text.AlignHCenter
    }
    Text {
        id: speed_unit
        width: 62
        height: 34
        x: 993
        y: 52
        text: qsTr("KM/H")
        color: "#ffffff"
        // opacity: 0.6
        font.pixelSize: 24
        font.styleName: "Regular"
    }

    // 4、方向盘转角、刹车状态
    // Item {
    // RowLayout {
    //     //x: 227
    //     width: parent.width
    //     y: 187
    //     // 方向盘转角

    //     RowLayout{
    //         Layout.preferredWidth: 400
    //         Layout.leftMargin:250
    //         Text {
    //             // x: 6
    //             // y: 13
    //             Layout.preferredWidth: 50
    //             color: "#FFFFFF"
    //             text: qsTr(m_drive_steer.toString())
    //             font.pixelSize: 28
    //             font.styleName: "Regular"
    //             verticalAlignment : Text.AlignVCenter
    //             horizontalAlignment : Text.AlignHCenter
    //         }
    //         Rectangle {
    //             id: streer_process_bar_id
    //             width: 300
    //             height: 18
    //             // x: 48
    //             // y: 21
    //             color: Qt.rgba(0,0,0,0.0)
    //             // border.color: "#55BBFF"
    //             // border.width: 1
    //             radius: 1

    //             Image {
    //                 id: streer_bg_id
    //                 width: 300
    //                 height: 18
    //                 source: "qrc:/resource/asset/image/autodrive/map_icon/steer_bg.png"
    //                 fillMode: Image.PreserveAspectFit
    //             }

    //             Image {
    //                 id: streer_process_id
    //                 // width:  m_drive_steer / 100 * parent.width
    //                 height: 16
    //                 x: (1 + m_drive_steer / 540) * streer_bg_id.width / 2
    //                 y: 2
    //                 // rotation: 180
    //                 // anchors.right: streer_bg_id.right
    //                 // anchors.rightMargin: 15
    //                 source: "qrc:/resource/asset/image/autodrive/map_icon/steer_cursor.png"
    //                 fillMode: Image.PreserveAspectFit
    //             }
    //         }
    //         Image {
    //             width:  44
    //             height: 44
    //             // x: 366
    //             // y: 8
    //             source: "qrc:/resource/asset/image/autodrive/map_icon/steering_wheel.png"
    //             fillMode: Image.PreserveAspectFit
    //         }
    //     }

    //     Item{
    //         Layout.fillWidth: true
    //     }
    //     // 刹车状态
    //     RowLayout{
    //         Layout.preferredWidth: 400
    //         Layout.rightMargin:250
    //         Image {
    //             width:  44
    //             height: 44
    //             // x: 903
    //             // y: 8
    //             source: "qrc:/resource/asset/image/autodrive/map_icon/brake.png"
    //             fillMode: Image.PreserveAspectFit
    //         }

    //         Rectangle {
    //             id: brake_process_bar_id
    //             width: 300
    //             height: 18
    //             // x: 966
    //             // y: 21
    //             color: Qt.rgba(0,0,0,0.0)
    //             // border.color: "#55BBFF"
    //             // border.width: 1
    //             radius: 1
    //             Image {
    //                 id: brake_process_id
    //                 width:  m_drive_throttle < 1000 ? m_drive_throttle * (brake_bg_id.width) / 1000 : brake_bg_id.width
    //                 height: 18
    //                 // y: 2
    //                 anchors.left: brake_bg_id.left
    //                 anchors.leftMargin: 15
    //                 source: "qrc:/resource/asset/image/autodrive/background/progress.png"
    //                 fillMode: Image.PreserveAspectFit
    //             }
    //         }
    //         Text {
    //             // x: 1278
    //             // y: 13
    //             Layout.preferredWidth: 50
    //             color: "#FFFFFF"
    //             text: qsTr(m_drive_throttle.toString())
    //             font.pixelSize: 28
    //             font.styleName: "Regular"
    //             verticalAlignment : Text.AlignVCenter
    //             horizontalAlignment : Text.AlignHCenter
    //         }
    //     }
    // }

    // // 方向盘转角2
    // Item {
    //     width: parent.width
    //     y: 81
    //     Image {
    //         id: streer_process_id
    //         // width:  m_drive_steer / 100 * 460
    //         height: 24
    //         x: 124 + 460 / 2 - (m_drive_steer / 540 * 460)
    //         y: 10
    //         // rotation: 180
    //         // anchors.right: streer_bg_id.right
    //         // anchors.rightMargin: 15
    //         source: "qrc:/resource/asset/image/autodrive/map_icon/steer_cursor.png"
    //         fillMode: Image.PreserveAspectFit
    //     }
    //     Text {
    //         x: 608
    //         Layout.preferredWidth: 50
    //         color: "#FFFFFF"
    //         text: qsTr(m_drive_steer.toString())
    //         font.pixelSize: 28
    //         font.styleName: "Regular"
    //         verticalAlignment : Text.AlignVCenter
    //         horizontalAlignment : Text.AlignHCenter
    //     }
    // }

    // // 刹车状态2
    // Item {
    //     width: parent.width
    //     y: 81
    //     Text {
    //         x: 1274
    //         Layout.preferredWidth: 50
    //         color: "#FFFFFF"
    //         text: qsTr(m_drive_throttle.toString() + "%")
    //         font.pixelSize: 28
    //         font.styleName: "Regular"
    //         verticalAlignment : Text.AlignVCenter
    //         horizontalAlignment : Text.AlignHCenter
    //     }
    //     Image {
    //         id: brake_process_id
    //         width:  m_drive_throttle < 100 ? m_drive_throttle * 460 / 100 : 460
    //         height: 26
    //         x: 1339
    //         y: 8
    //         // rotation: 180
    //         // anchors.right: streer_bg_id.right
    //         // anchors.rightMargin: 15
    //         source: "qrc:/resource/asset/image/autodrive/background/progress.png"
    //         fillMode: Image.TileVertically
    //     }
    // }

    // 方向盘转角3
    Item {
        Text {
            x: 36
            y: 92
            Layout.preferredWidth: 50
            color: "#FFFFFF"
            text: qsTr(m_drive_steer.toString() + "%")
            font.pixelSize: 36
            font.styleName: "Regular"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
        }
        Image {
            id: streer_process_id
            height: 24
            x: 146 + 560 / 2 - (m_drive_steer / 300 * (560 / 2))
            y: 104
            source: "qrc:/resource/asset/image/autodrive/dashboard/progress-bar.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    // 刹车状态3
    Item {
        Text {
            x: 1830
            y: 92
            Layout.preferredWidth: 50
            color: "#FFFFFF"
            text: qsTr(m_drive_throttle.toString() + "%")
            font.pixelSize: 36
            font.styleName: "Regular"
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
        }

        Image {
            id: brake_process_id
            width:  m_drive_throttle < 100 ? m_drive_throttle * 560 / 100 : 560
            x: 1217
            y: 103
            source: "qrc:/resource/asset/image/autodrive/background/progress.png"
            fillMode: Image.TileVertically
        }
    }

    Connections {
        target: CUIDataHandle
        function onSignalDashBoard(nSpeed, strCruiseSpeed, nCruiseStatus)
        {
            handleDashboardData(nSpeed, strCruiseSpeed, nCruiseStatus)
        }
    }

    function handleDashboardData(nSpeed, strCruiseSpeed, nCruiseStatus) {
        // m_nSpeed = nSpeed
        // console.log("on dashboarddata cru spd = ", nSpeed)
    }

    Component.onCompleted: {
    }

    Connections {
        target: CAduProxy
        function onNotifyVehicleDriveSteer(steer) {
            m_drive_steer = steer
        }

        function onNotifyVehicleDriveThrottle(throttle) {
            m_drive_throttle = throttle
        }

        // deprecated
        // function onNotifyVehicleDriveSpeed(speed) {
        //     m_nSpeed = speed
        //     // console.log("on dashboarddata cru spd = ", speed)
        // }
    }
}