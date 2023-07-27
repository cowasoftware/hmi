import QtQuick 2.15
import QtQuick.Controls 2.15
import ConfigClass 1.0

Item {
    id: user_setting_id
    width: 1446;
    height: 960;
    property int currentIndex: gConfig.currentIndex
    property var username: "访客"
    signal logout() // 退出登录

    Rectangle {
        id: user_rect_id
        // width: 786
        // height: 80
        width: parent.width
        height: parent.height
        // x: 330
        // y: 91
        color: gConfig.background[currentIndex]
        Text {
            id: username_txt
            width: 360
            height: 80
            x: 330
            y: 91
            text: qsTr("用户名: " + username)
            color: gConfig.buttonColor[gConfig.currentIndex]
            font.pixelSize: 32
            font.styleName: "Regular"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            id: logout_btn
            width: 200
            height: 80
            x: 916
            y: 91
            highlighted: false
            //设置按钮背景颜色
            background: Rectangle {
                color: "#5B89FF"
                radius: 4
                Text{
                    text: qsTr("退出登录")
                    anchors.centerIn: parent
                    font.pixelSize: 32
                    font.styleName: "Regular"
                    color: gConfig.buttonColor[gConfig.currentIndex]
                }
            }
            onClicked: {
                console.log("退出登录")
                // login_page_id.visible = true
                // TODO 发送退出登录的信号
                user_setting_id.logout()
            }
        }
    }
    
    Connections {
        target: user_setting_id
        function onLogout() {
            ConfigManager.logout()
        }
    }

    Component.onCompleted: {
        getLoginUser();
    }

    function getLoginUser() {
        user_setting_id.username = ConfigManager.getLoginUser();
        console.log("getLoginUser: username = " + user_setting_id.username);
    }

    Connections {
        target: ConfigManager
        function onSendLoginInfo(username, token, open_id) {
            console.log("onSendLoginInfo: username = " + username + "token = " + token + "open_id = " + openId)
            user_setting_id.username = username;
        }
    }

}
