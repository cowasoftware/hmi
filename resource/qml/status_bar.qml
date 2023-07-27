import QtQuick 2.0
import BarClass 1.0
import UpgradeMgrClass 1.0
import WorkClass 1.0

Item {
    id: top_bar_id
    x: 0
    y: 0
    width: 1689
    height: 35
    property var currentIndex: gConfig.currentIndex
    property var energy_image: ["qrc:///resource/asset/image/bar/energy_light.png", "qrc:///resource/asset/image/bar/energy.png"]
    property var communication_image: ["qrc:///resource/asset/image/bar/communication5G_light.png", "qrc:///resource/asset/image/bar/communication5G.png"]
    property var main_card_image: ["qrc:///resource/asset/image/bar/main_card_light.png", "qrc:///resource/asset/image/bar/main_card.png"]
    property var update_icon_image: ["qrc:///resource/asset/image/bar/update_light.png", "qrc:///resource/asset/image/bar/update_dark.png"]
    property int x_pos: 32
    property int y_pos: 15
    property int m_nWaterLine: 0
    property var statusbar_color: [""]

    Rectangle {
        id: top_bar_rect
        width:  parent.width
        height: parent.height
        // color: gConfig.background[currentIndex]
        color: gConfig.statusBarColor

        Rectangle {
            x: 770
            y: 18
            width: 18
            height: 24
            color: Qt.rgba(0, 0, 0, 0.0)
            Image {
                width: 18
                height: 24
                source: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/waterline.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
        }

        Rectangle {
            x: 786
            y: 15
            width: 46
            height: 29
            
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Text {
                width: 46
                height: 29
                anchors.fill: parent
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr(m_nWaterLine.toString() + "%")
                font.pixelSize: 24
                font.styleName: "Regular"
                
            }
        }

        Text {
            id: date_id
            x: x_pos
            y: 0
            width: 123
            height: 30
            text: qsTr("正在加载日期")
            font.styleName: "Regular"
            color: gConfig.textColor[currentIndex]
            font.pixelSize: 22
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: time_id
            x: 280
            y: 0
            width: 60
            height: 30
            text: qsTr("正在加载时间")
            font.styleName: "Regular"
            color: gConfig.textColor[currentIndex]
            font.pixelSize: 22
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: week_id
            x: 550
            y: 0
            width: 66
            height: 30
            text: qsTr("正在加载星期")
            font.styleName: "Regular"
            color: gConfig.textColor[currentIndex]
            font.pixelSize: 22
            anchors.verticalCenter: parent.verticalCenter
        }

        //Row {
        //    id: row
        //    x: 900
        //    y: 0
        //    width: 750
        //    height: 35
        //    layoutDirection : Qt.RightToLeft
        //
        //    // TODO: add children
        //
        //
        //}

        Image {
            id: energy_image_id
            x: 0
            y: 7
            width: 53
            height: 25
            source: energy_image[currentIndex]
            fillMode: Image.PreserveAspectFit
            anchors.right: parent.right
            anchors.rightMargin: 80
            anchors.verticalCenter: parent.verticalCenter

            Rectangle {
                id: energy_background_id
                x: 3
                y: 3
                width: 0
                height: 18
                radius: 2
                color:"#75C8C8C8"
            }

            Text {
                id: energy_percent_id
                x: 3
                y: 3
                width: 42
                height: 18
                text: qsTr("")
                font.styleName: "Regular"
                color: gConfig.textColor[currentIndex]
                font.pixelSize: 21
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Text {
            id: energy_electricity_id
            y: 15
            width: 90
            height: 18
            text: qsTr("0A")
            font.styleName: "Regular"
            color: gConfig.textColor[currentIndex]
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            anchors.right: energy_image_id.left
            anchors.rightMargin: 10
        }

        Text {
            id: energy_voltage_id
            width: 90
            height: 18
            text: qsTr("0V")
            font.styleName: "Regular"
            color: gConfig.textColor[currentIndex]
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            anchors.right: energy_electricity_id.left
            anchors.rightMargin: 10
            anchors.top: energy_electricity_id.top
        }

        // TODO 增加升级图标
        Image {
            id: update_image_id
            x: 0
            y: 7
            width: 17
            height: 22
            source: update_icon_image[currentIndex]
            fillMode: Image.PreserveAspectFit
            anchors.right: energy_voltage_id.left
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: card1_id
            x: 0
            y: 10
            width: 100
            height: 18
            text: qsTr("")
            font.styleName: "Regular"
            color: gConfig.textColor[currentIndex]
            font.pixelSize: 24
            anchors.right: update_image_id.left
            anchors.rightMargin: 10
        }

        Rectangle {
            id: card1_communication_id
            x: 0
            y: 11
            width: 35
            height: 30
            anchors.right: card1_id.left
            anchors.rightMargin: 3
            color: "#00000000"

            Image {
                id: card1_communication_5G_id
                x: 0
                y: 6
                width: 9
                height: 7
                source: communication_image[currentIndex]
                fillMode: Image.PreserveAspectFit
            }

            Rectangle {
                id: card1_communication1_id
                x: 3
                width: 4
                height: 9.6
                radius: 1.6
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
            }

            Rectangle {
                id: card1_communication2_id
                x: 0
                width: 4
                height: 14.4
                radius: 1.6
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
                anchors.left: card1_communication1_id.right
                anchors.leftMargin: 4
            }

            Rectangle {
                id: card1_communication3_id
                x: 0
                width: 4
                height: 19.2
                radius: 1.6
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
                anchors.left: card1_communication2_id.right
                anchors.leftMargin: 4
            }

            Rectangle {
                id: card1_communication4_id
                x: 0
                width: 4
                height: 24
                radius: 1.6
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
                anchors.left: card1_communication3_id.right
                anchors.leftMargin: 4
            }
        }

        Image {
            id: card1_main_card_id
            x: 0
            y: 6
            width: 20
            height: 12
            source: main_card_image[currentIndex]
            fillMode: Image.PreserveAspectFit
            anchors.bottom: card1_communication_id.bottom
            anchors.right: card1_communication_id.left
            anchors.rightMargin: 4
        }

        Text {
            id: card2_id
            x: 0
            y: 0
            width: 100
            height: 18
            text: qsTr("")
            font.styleName: "Regular"
            //style
            //{
            //    background.border.color:"#ffffff"
            //}
            color: gConfig.textColor[currentIndex]
            font.pixelSize: 24
            //console.log(energy_image_id.left)
            anchors.right: card1_main_card_id.left
            anchors.rightMargin: 10
        }

        Rectangle {
            id: card2_communication_id
            x: 0
            y: 1
            width: 35
            height: 30
            anchors.right: card2_id.left
            anchors.rightMargin: 3
            color: "#00000000"

            Image {
                id: card2_communication_5G_id
                x: 0
                y: 6
                width: 9
                height: 7
                source: communication_image[currentIndex]
                fillMode: Image.PreserveAspectFit
                //anchors.right: parent.right
            }

            Rectangle {
                id: card2_communication1_id
                x: 3
                width: 4
                height: 9.6
                radius: 1.6
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
            }

            Rectangle {
                id: card2_communication2_id
                x: 0
                width: 4
                height: 14.4
                radius: 1.6
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
                anchors.left: card2_communication1_id.right
                anchors.leftMargin: 4
            }

            Rectangle {
                id: card2_communication3_id
                x: 0
                width: 4
                height: 19.2
                radius: 1.6
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
                anchors.left: card2_communication2_id.right
                anchors.leftMargin: 4
            }

            Rectangle {
                id: card2_communication4_id
                x: 0
                width: 4
                height: 24
                radius: 1.6
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
                anchors.left: card2_communication3_id.right
                anchors.leftMargin: 4
            }
        }

        Image {
            id: card2_main_card_id
            x: 0
            y: 6
            width: 20
            height: 12
            source: main_card_image[currentIndex]
            fillMode: Image.PreserveAspectFit
            anchors.bottom: card2_communication_id.bottom
            anchors.right: card2_communication_id.left
            anchors.rightMargin: 4
        }

    }


    Component.onCompleted: {
        card1_id.visible = false
        card1_communication_id.visible = false
        card1_main_card_id.visible = false
        card2_id.visible = false
        card2_communication_id.visible = false
        card2_main_card_id.visible = false
        update_image_id.visible = false
    }

    Connections {
        target: CUIBarHandle
        function onSignalUpdateEnergyPercent(percent)
        {
            energy_percent_id.text = percent
            energy_background_id.width = 42 * percent / 100
        }

        function onSignalUpdateEnergyIsCharge(isCharge)
        {
            energy_background_id.color = isCharge ? "#7500C800" : "#75C8C8C8"
        }

        function onSignalUpdateDate(dateString)
        {
            date_id.text = dateString
        }

        function onSignalUpdateTime(timeString)
        {
            time_id.text = timeString
        }

        function onSignalUpdateWeek(weekString)
        {
            week_id.text = weekString
        }

        function onSignalUpdateVoltage(voltage)
        {
            energy_voltage_id.text = voltage + "V"
        }

        function onSignalUpdateElectricity(electricity)
        {
            energy_electricity_id.text = electricity + "A"
        }

        function onSignalUpdateCard(cardString, quality)
        {
            card1_id.visible = true
            card1_communication_id.visible = true

            card1_id.text = cardString;
            card1_communication1_id.color = "#666666"
            card1_communication2_id.color = "#666666"
            card1_communication3_id.color = "#666666"
            card1_communication4_id.color = "#666666"
            if (quality == 1)
            {
                card1_communication1_id.color = "#FFFFFF"
            }
            else if (quality == 2)
            {
                card1_communication1_id.color = "#FFFFFF"
                card1_communication2_id.color = "#FFFFFF"
            }
            else if (quality == 3)
            {
                card1_communication1_id.color = "#FFFFFF"
                card1_communication2_id.color = "#FFFFFF"
                card1_communication3_id.color = "#FFFFFF"
            }
            else if (quality == 4)
            {
                card1_communication1_id.color = "#FFFFFF"
                card1_communication2_id.color = "#FFFFFF"
                card1_communication3_id.color = "#FFFFFF"
                card1_communication4_id.color = "#FFFFFF"
            }
            else if (quality == 99)
            {
                card1_communication_5G_id.source = "qrc:///resource/asset/image/bar/communicationError.png"
            }
            console.log("QML Receive Net Work Msg...is: ", cardString, quality)
        }
    }

    Connections {
        target: UpgradeMgr
        function onSignalNotifyPkgInfo(pkg_name, old_version, new_version) {
            // 接收到有版本更新时显示更新图标
            if(old_version !== new_version) {
                console.log("set update icon to be visible.")
                update_image_id.visible = true
            }
        }
        // 更新升级图标
        function onSignalNotifyUpgradeStatus(status) {
            console.log("onSignalNotifyUpgradeStatus: status = " + status)
            if(status === 3) {
                console.log("set update icon to be invisible.")
                update_image_id.visible = false
            }
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
