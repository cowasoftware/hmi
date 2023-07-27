import QtQuick 2.15
import UpgradeMgrClass 1.0
import WorkClass 1.0

Item {
    id: rootid
    width: 1446;
    height: 960;
    property int currentIndex: gConfig.currentIndex
    signal qmlSignalReqServer() // 向服务端请求待升级的数据
    signal qmlSignalNotifyInstall() // 通知服务端开始升级安装
    property var packageLists: []
    property bool button_visible : false
    property bool indicator_visible: false
    property string m_strSoftVersion: "----"

    /* 版本升级提示 */
    Rectangle {
        id: upgrade_id
        width: 823
        height: 310
        x: 312
        y: 51
        color: gConfig.background[currentIndex]
        Text {
            id: current_version
            text: qsTr("当前版本")
            width: 126
            height: 45
            x: 250
            color: gConfig.textColor[currentIndex]
            font.pixelSize: 32
            font.styleName: "Regular"
        }

        Text {
            id: new_version
            text: qsTr("最新版本")
            width: 126
            height: 45
            color: gConfig.textColor[currentIndex]
            font.pixelSize: 32
            font.styleName: "Regular"
            anchors.left: current_version.right
            anchors.leftMargin: 200
        }

        // 电机控制版本
        Rectangle {
            id: control_version_info
            width: parent.width
            height: 45
            color: gConfig.background[currentIndex]
            property var version_code: rootid.m_strSoftVersion
            anchors.top: current_version.bottom
            anchors.topMargin: 10
            Text {
                id: control_version_id
                text: qsTr("电控程序版本")
                width: 126
                height: 45
                color: gConfig.textColor[currentIndex]
                font.pixelSize: 32
                font.styleName: "Regular"
            }
            Text {
                id: control_version_txt
                text: qsTr(control_version_info.version_code)
                width: 126
                height: 45
                color: gConfig.textColor[currentIndex]
                font.pixelSize: 32
                font.styleName: "Regular"
                anchors.left: control_version_id.right
                anchors.leftMargin: 150
            }
        }

        // 固件版本
        Rectangle {
            id: version_info_id
            width: parent.width
            height: 45
            color: gConfig.background[currentIndex]
            property var curr_version_code: "----"
            property var lasted_version_code: "----"
            anchors.top: control_version_info.bottom
            anchors.topMargin: 10
            Text {
                id: hardwarm_version_txt
                text: qsTr("固件")
                width: 126
                height: 45
                color: gConfig.textColor[currentIndex]
                font.pixelSize: 32
                font.styleName: "Regular"
            }
            Text {
                id: curr_version_txt
                text: qsTr(version_info_id.curr_version_code)
                width: 126
                height: 45
                color: gConfig.textColor[currentIndex]
                font.pixelSize: 32
                font.styleName: "Regular"
                anchors.left: hardwarm_version_txt.right
                anchors.leftMargin: 150
            }
            // 更新提示的小圆点
            Rectangle {
                id: hardwarm_indicator_id
                height: 10
                width:  10
                color: "#FF4D4B"
                radius: 10
                // y: 70
                anchors.top: curr_version_txt.top
                anchors.topMargin: 12
                anchors.left: curr_version_txt.right
                anchors.leftMargin: 180
                visible: indicator_visible
            }
            Text {
                id: lasted_version_txt
                text: qsTr(version_info_id.lasted_version_code)
                width: 126
                height: 45
                color: gConfig.textColor[currentIndex]
                font.pixelSize: 32
                font.styleName: "Regular"
                anchors.left: hardwarm_indicator_id.right
                anchors.leftMargin: 10
            }
        }

        // app版本信息
        ListView {
            id: list
            anchors.fill: parent
            width: parent.width
            spacing: 50
            orientation: ListView.Vertical
            anchors.top: version_info_id.bottom
            anchors.topMargin: 100
            model: ListModel {
                id: dataModel
                property bool completedFlag: false

                Component.onCompleted: {
                    // 向服务端请求数据
                    rootid.qmlSignalReqServer();
                    // dataModel.append({name: "HMI", oldVersion: "V1.0.0", newVersion: "V1.0.1"})
                    completedFlag = true
                }
            }

            delegate: Row {
                id: row_id
                Rectangle {
                    id: row_rect_id
                    width: parent.width
                    height: 45

                    Text {
                        id: app_name_txt
                        text: qsTr(name);
                        // leftPadding: 200 - contentWidth;
                        width: 126;
                        y: 70
                        color: gConfig.textColor[currentIndex];
                        font.pixelSize: 32
                    }
                    Text {
                        id: old_version_txt
                        text: qsTr(oldVersion);
                        // leftPadding: 200 - contentWidth;
                        width: 126;
                        y: 70
                        color: gConfig.textColor[currentIndex];
                        font.pixelSize: 32
                        anchors.left: app_name_txt.right
                        anchors.leftMargin: 150
                    }
                    // 更新提示的小圆点
                    Rectangle {
                        id: indicator_id
                        height: 10
                        width:  10
                        color: "#FF4D4B"
                        radius: 10
                        // y: 70
                        anchors.top: old_version_txt.top
                        anchors.topMargin: 12
                        anchors.left: old_version_txt.right
                        anchors.leftMargin: 180
                        visible: indicator
                    }
                    Text {
                        id: new_version_txt
                        text: newVersion;
                        // leftPadding: 400;
                        width: 126;
                        y: 70
                        anchors.left: indicator_id.right
                        anchors.leftMargin: 10
                        color: gConfig.textColor[currentIndex];
                        opacity: text_opacity
                        font.pixelSize: 32
                    }
                }
            }
        }
    }

    /* 确认升级 */
    Rectangle {
        id: confirm_update_rect
        width: 240
        height: 80
        color: "#BDBDBD"
        x: 603
        // y: 410
        anchors.top: upgrade_id.bottom
        anchors.topMargin: 78
        radius: 2
        visible: false
        Text {
            id: update_btn
            width: 126
            height: 45
            x: 56
            y: 17.5
            text: qsTr("一键升级")
            color: gConfig.buttonColor[gConfig.currentIndex]
            font.pixelSize: 32
            font.styleName: "Regular"
        }
        MouseArea  {
            anchors.fill:  parent
            // visible: button_visible
            onClicked:  {
                confirm_update_rect.state  ==  'selected'  ?  confirm_update_rect.state  =  ""  :  confirm_update_rect.state  =  'selected';
                if(confirm_update_rect.state  ==  'selected') {
                    update_btn.color = "#FFFFFF"
                    // 向主升级程序发送升级确认
                    rootid.qmlSignalNotifyInstall();
                }
            }
        }
        states: [
            State {
                name: "selected"
                PropertyChanges {
                    target: confirm_update_rect
                    color: "#5B89FF"
                }
            }
        ]
    }

    Connections {
        target: rootid
        function onQmlSignalReqServer()
        {
            console.log("onQmlSignalReqServer.")
            // 请求服务端发送最新的数据
            UpgradeMgr.req_server()
        }

        function onQmlSignalNotifyInstall() {
            console.log("onQmlSignalNotifyInstall.")
            // 通知服务端可以开始升级安装
            UpgradeMgr.notify_server()
        }
    }

    Connections {
        target: UpgradeMgr
        function onSignalNotifyMajorVersionInfo(curr_version_code, new_version_code) {
            console.log("onSignalNotifyMajorVersionInfo: curr_version = " + curr_version_code + ", new_version = " + new_version_code)
            version_info_id.curr_version_code = curr_version_code
            version_info_id.lasted_version_code = new_version_code
            if(curr_version_code !== new_version_code) {
                indicator_visible = true
            } else {
                indicator_visible = false
            }
        }

        function onSignalClearData() {
            // 清空旧数据
            console.log("onSignalClearData: clear old data.")
            dataModel.clear()
        }
        
        function onSignalNotifyPkgInfo(pkg_name, old_version, new_version) {
            console.log("onSignalNotifyPkgInfo: name = " + pkg_name + ", old_version = ", old_version +", new_version = " + new_version)
            // 将接收到的版本信息设置上去
            if(old_version !== new_version) {
                // button_visible = true;
                confirm_update_rect.visible = true;
                dataModel.append({name: pkg_name, oldVersion: old_version, newVersion: new_version, indicator: true, text_opacity: 1})
            } else {
                dataModel.append({name: pkg_name, oldVersion: old_version, newVersion: new_version, indicator: false, text_opacity: 0.6})
            }
        }
        // 升级成功按钮不可见
        function onSignalNotifyUpgradeStatus(status) {
            if(status === 3) {
                confirm_update_rect.visible = false;
            }
        }
    }

    Connections {
        target: CUIDataHandle
        function onSignalSoftWareVersion(verson)
        {
            m_strSoftVersion = verson.toString()
        }
       
    }

}
