import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
// import QtWebView 1.15
import ConfigClass 1.0
import QtWebEngine 1.10
import QtWebChannel 1.0
import Cowa.NetworkPlugin 1.0

// 登录页面
Item {
    id: login_id
    width: 1920
    height: 1080
    visible: true
    property bool loginTypeFlag: true
    property alias popupVisible: popup.visible
    property color barColor: Qt.rgba(64/255, 64/255, 64/255, 1)
    property real backgroundWidth: 300
    property real backgroundHeight: 40
    property color borderColor: barColor
    property real borderWidth: 0
    // property real verticalOffset: 24
    property bool isActiveFocusOnPress: true
    property bool isNetworkError: false
    property var load_status: ""
    property string resp_url: ""
    property var user_name: "飞书用户"
    signal loginSuccess(string username)
    property string vehicle_token: ""
    property string vehicle_id: ""
    property string open_id: ""
    property string login_status: "online"

    // 盖住下方透上来的背景图
    Rectangle {
        id: webview_rect
        width: 350
        height: 350
        color: barColor
        x: 1270
        y: 300
        radius: 4
    }

    QtObject {
        id: web_object
        WebChannel.id: "web_object"

        // 登录成功，返回用户信息
        function getUserInfo(result) {
            if(result["name"] != undefined) {
                user_name = result["name"]
                open_id = result["open_id"]
                console.log("the current user is: " + user_name + ", open_id: " + open_id)
            } else {
                console.log("cannot get user info from server, the current user is: ", user_name)
            }
            ConfigManager.parseUrl(resp_url)
        }
    }

    WebChannel {
        id: channel_
        registeredObjects: [web_object]
    }

    // 展示一个登录页面
    WebEngineView {
        id: webView
        // anchors.centerIn: parent
        width: 350
        height: 350
        x: 1270
        y: 300
        // anchors.horizontalCenter: parent.horizontalCenter
        // url: "http://172.31.10.12:5173/qrlogin?id=" + vehicle_token
        url: "http://hmi.cowarobot.work/qrlogin/?id=" + vehicle_id
        visible: loginTypeFlag
        webChannel: channel_
        Connections {
            target: webView
            function onLoadingChanged(loadRequest) {
                console.log("onLoadingChanged: loadRequest.url = " + loadRequest.url)
                console.log("onLoadingChanged: loadRequest.status = " + loadRequest.status)
                resp_url = loadRequest.url.toString();
                // 保存加载状态
                load_status = loadRequest.status
                if(loadRequest.status == WebEngineLoadRequest.LoadSucceededStatus) {
                    webview_rect.visible = false
                    isNetworkError = false
                } else if(loadRequest.status == WebEngineLoadRequest.LoadFailedStatus) {
                    // 加载失败时重试__FUNCTION__ 
                    isNetworkError = true
                }
            }
        }

        Component.onCompleted: {
            console.log("WebEngineView load finished!")
            ConfigManager.getVehicleInfo();
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                load_reflush()
            }
        }
    }

    // 网络连接异常提示
    Rectangle {
        id: network_error_id
        width: 350
        height: 350
        x: 1270
        y: 300
        color: barColor
        radius: 4
        visible: isNetworkError
        Text {
            id: error1
            width: 256
            height: 45
            text: qsTr("网络异常")
            color: "#ffffff"
            x: 150
            y: 100
            font.pixelSize: 20
            font.styleName: "Regular"
            // anchors.horizontalCenter: parent.horizontalCenter
            
        }
        Text {
            id: error2
            width: 315
            height: 45
            text: qsTr("请点击刷新或检查网络！")
            color: "#ffffff"
            x: 90
            y: 140
            font.pixelSize: 20
            font.styleName: "Regular"
            // anchors.horizontalCenter: parent.horizontalCenter
            // horizontalAlignment: Text.AlignHCenter
            // verticalAlignment: Text.AlignVCenter
        }
    }

    Image {
        id: background_image_id
        source: "qrc:///resource/asset/image/login/login_bg.png"
        fillMode: Image.PreserveAspectFit
    }

    // Rectangle {
    //     id: login_rect_id
    //     width: 520
    //     height: 650
    //     color: "#929292"
    //     // color: "#F06060"
    //     x: 1200
    //     y: 150
        
    // }

    Text {
        id: login_tip_id
        width: 142
        height: 36
        text: qsTr("欢迎登录")
        color: "#ffffff"
        x: 1381
        y: 210
        font.pixelSize: 40
        font.styleName: "Regular"
        // anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: open_feishu_txt
        width: 170
        height: 28
        text: qsTr("打开飞书“扫一扫”")
        x: 1375
        y: 641
        color: "#ffffff"
        visible: loginTypeFlag
        font.pixelSize: 20
        font.styleName: "Regular"
        // anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: visitor_pwd_id
        width: 300
        height: 300
        x: 1310
        y: 300
        visible: !loginTypeFlag
        color: barColor
        radius: 4
        // 访客密码登录
        FocusScope {
            //FocusScope needs to bind to visual properties of the Rectangle
            width: 240
            height: 80
            x: 30
            y: 80
            focus: true
            visible: true
            anchors.horizontalCenter: parent.horizontalCenter
            Row {
                id: password_input_row_id
                width: 240
                height: 80
                spacing: 50
                property string target_password: "1234"
                property var input_password: ["", "", "", ""]
                property string new_input_password: ""
                property int current: 0
                Rectangle {
                    width: 240
                    height: 80
                    color: Qt.rgba(0, 0, 0, 0.0)
                    radius: 4
                    TextField {
                        id: password_id_4
                        width: 240
                        height: 80
                        color: "#ffffff"
                        maximumLength: 4
                        echoMode: TextInput.Password
                        font.pixelSize: 60
                        font.weight: Font.Bold
                        font.letterSpacing: 20
                        passwordCharacter: "*"
                        anchors.centerIn: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter

                        background: Rectangle {
                            border.width: 1
                            border.color: "#FFFFFF"
                            radius: 4
                            color: Qt.rgba(43 / 255, 43 / 255, 43 / 255, 0.2)
                            implicitHeight: 100
                            implicitWidth: 580
                        }

                        activeFocusOnPress: isActiveFocusOnPress
                        focus: true
                        onTextEdited: {
                            password_input_row_id.new_input_password = text
                            if (text !== "") {
                                // 输入密码长度为4
                                if (password_input_row_id.new_input_password.length == 4) {
                                    isActiveFocusOnPress = false
                                    if (password_input_row_id.new_input_password
                                            !== password_input_row_id.target_password) {
                                        console.log("input_password is not right!")
                                        // 显示一个dialog
                                        show();
                                        // return
                                    } else {
                                        // 密码验证成功
                                        focus = false
                                        user_name = "访客"
                                        handleLoginSuccess()
                                    }
                                }
                            }
                        }
                        Keys.onPressed: event => {
                                            if (Qt.Key_Delete === event.key
                                                || Qt.Key_Backspace === event.key) {
                                            }
                                        }
                    }
                }
            }
        }
    }

    // 登录错误提示框
    Popup {
        id: popup
        width: backgroundWidth
        height: backgroundHeight
        focus: true
        x: 1310
        y: 320
        background: Rectangle {
            id: background
            color: barColor
            radius: 8
            border.color: borderColor
            border.width: borderWidth
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            Label {
                id: label
                text: qsTr("密码不正确，请重新输入！")
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
            // console.log("timer trigger", index)
            hide()
            timer_id.stop()
        }
    }

    Text {
        id: input_password_txt
        width: 170
        height: 28
        text: qsTr("请输入密码进行登录")
        x: 1375
        y: 641
        color: "#ffffff"
        visible: !loginTypeFlag
        font.pixelSize: 20
        font.styleName: "Regular"
        // anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: visitor_login_bt
        width: 79
        height: 28
        x: 1421
        y: 712
        text: qsTr("访客登录")
        color: "#027FB9"
        font.pixelSize: 20
        font.styleName: "Regular"
        anchors.top: open_feishu_txt.bottom
        anchors.topMargin: 44
        // anchors.horizontalCenter: parent.horizontalCenter
        MouseArea {
            anchors.fill: parent
            onClicked: {
                // 当前为扫码登录，要切换为访客登录
                if (webView.visible == true) {
                    // console.log("当前为访客登录")
                    visitor_login_bt.text = qsTr("扫码登录")
                } else {
                    // console.log("当前为扫码登录")
                    visitor_login_bt.text = qsTr("访客登录")
                    // 重新加载
                    // load_reflush()
                }
                loginTypeFlag = !loginTypeFlag
            }
        }
    }

    function show()
    {
        // console.log("show dialog")
        // popup.x = (bar.width - popup.width) / 2
        // popup.y = bar.height + verticalOffset
        // popup.x = bar.x - popup.width / 2
        // popup.y = bar.height / 2
        popupVisible = true
        timer_id.start()
    }

    function hide()
    {
        // console.log("close dialog")
        popupVisible = false
        isActiveFocusOnPress = true
        // 清空密码输入框内容
        password_id_4.text = ""
    }

    // 二维码加载重试
    function load_reflush() {
        console.log("reflush qrCode.")
        webView.url = "http://hmi.cowarobot.work/qrlogin/?id=" + vehicle_id
        webView.reload();
    }

    function handleLoginSuccess() {
        login_page_id.source = ""
        ConfigManager.saveLoginInfo(user_name, vehicle_id, open_id, login_status);
    }

    Connections {
        target: window
        function onResetLogin() {
            console.log("onResetLogin")
            loginTypeFlag = true
            // 密码框焦点为true
            isActiveFocusOnPress = true
            // 清空密码输入框内容
            password_id_4.text = ""
        }
    }

    Connections {
        target: ConfigManager
        function onSignalCheckLoginStatus(key, value) {
            if(key == "state" && value == "success_login") {
                // TODO 登录成功，用户名需要从地址中解析
                // login_id.loginSuccess(user_name)
                handleLoginSuccess()
            }
        }

        function onNotifyVehicleInfo(vehicleName, openId, plateNumber) {
            console.log("vehicle info: vehicleName=", vehicleName, ", openId=" , openId, ", plateNumber=", plateNumber)
            login_id.vehicle_id = vehicleName
        }
    }
}
