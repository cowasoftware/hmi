import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4

// 通用的 4位密码组件, 半透明的
Rectangle {
    property int currentIndex: gConfig.currentIndex
    id: password_content_id
    x: 0
    y: 0
    width: 1446
    height: 860
    // color: Qt.rgba(43/255,43/255,43/255, 0.9)
    color: gConfig.background[currentIndex]
    signal passwordSuccess
    signal cancel

    Text {
        id: text2
        x: 643
        y: 15
        width: 160
        height: 45
        color: gConfig.textColor[currentIndex]
        text: qsTr("请输入密码")
        font.pixelSize: 32
        font.styleName: "Regular"
    }

    Image {
        width: 50
        height: 50
        anchors.right: parent.right
        anchors.top: parent.top
        source: "qrc:/resource/asset/image/cancel.png"
        fillMode: Image.PreserveAspectFit
        MouseArea {
            anchors.fill: parent
            onClicked: {
                password_content_id.cancel()
            }
        }
    }

    FocusScope {
        //FocusScope needs to bind to visual properties of the Rectangle
//        x: 429
        y: 80
        width: 400
        height: 100
        focus:true;
        anchors.horizontalCenter: parent.horizontalCenter

        Row {
            id: password_input_row_id
            width: 400
            height: 100
            spacing: 60
            property string target_password: "1234"
            property var input_password: ["", "", "", ""]
            property string new_input_password: ""
            property int current : 0

//            Rectangle {
//                width: 100
//                height: 100
//                color: Qt.rgba(0,0,0, 0.0)
//                TextField {
//                    id : password_id_1
//                    width: 100
//                    height: 100
//                    color: "#ffffff"
//                    maximumLength: 1
//                    echoMode: TextInput.Password
//                    font.pixelSize: 60
//                    font.weight: Font.Bold
//                    font.letterSpacing : 20
//                    passwordCharacter: "*"
//                    anchors.centerIn: parent
//                    verticalAlignment : Text.AlignVCenter
//                    horizontalAlignment : Text.AlignHCenter

//                    background: Rectangle {
//                       border.width: 1;
//                       border.color: "#FFFFFF"
//                       radius: 4;
//                       color: Qt.rgba(43/255,43/255,43/255, 0.2)
//                       implicitHeight: 100; implicitWidth: 580
//                    }

//                    activeFocusOnPress: true
//                    focus:true
//                    onTextEdited: {
//                        if (text !== "") {
//                            console.log("password_id_1 " + text)
//                            password_input_row_id.input_password[0] = text
//                            focus = false
//                            activeFocusOnPress = false
//                            password_id_2.activeFocusOnPress = true
//                            password_id_2.focus = true
//                        }
//                    }
//                }
//            }

//            Rectangle {
//                width: 100
//                height: 100
//                color: Qt.rgba(0,0,0, 0.0)
//                TextField {
//                    id : password_id_2
//                    width: 100
//                    height: 100
//                    color: "#ffffff"
//                    maximumLength: 1
//                    echoMode: TextInput.Password
//                    font.pixelSize: 60
//                    font.weight: Font.Bold
//                    font.letterSpacing : 20
//                    passwordCharacter: "*"
//                    anchors.centerIn: parent
//                    verticalAlignment : Text.AlignVCenter
//                    horizontalAlignment : Text.AlignHCenter

//                    background: Rectangle {
//                       border.width: 1;
//                       border.color: "#FFFFFF"
//                       radius: 4;
//                       color: Qt.rgba(43/255,43/255,43/255, 0.2)
//                       implicitHeight: 100; implicitWidth: 580
//                    }

//                    activeFocusOnPress: false;
//                    onTextEdited: {
//                        if (text !== "") {
//                            console.log("password_id_2 " + text)
//                            activeFocusOnPress = false
//                            password_input_row_id.input_password[1] = text
//                            password_id_3.focus = true
//                            password_id_3.activeFocusOnPress = true
//                        }
//                    }
//                    Keys.onPressed: (event)=> {
//                        if (Qt.Key_Delete === event.key || Qt.Key_Backspace === event.key) {
//                            focus = false
//                            activeFocusOnPress = false
//                            password_id_1.activeFocusOnPress = true
//                            password_id_1.focus = true
//                        }
//                        console.log("password_id_2 onPressed" + event.key)
//                    }
//                }
//            }

//            Rectangle {
//                width: 100
//                height: 100
//                color: Qt.rgba(0,0,0, 0.0)
//                TextField {
//                    id : password_id_3
//                    width: 100
//                    height: 100
//                    color: "#ffffff"
//                    maximumLength: 1
//                    echoMode: TextInput.Password
//                    font.pixelSize: 60
//                    font.weight: Font.Bold
//                    font.letterSpacing : 20
//                    passwordCharacter: "*"
//                    anchors.centerIn: parent
//                    verticalAlignment : Text.AlignVCenter
//                    horizontalAlignment : Text.AlignHCenter

//                    background: Rectangle {
//                       border.width: 1;
//                       border.color: "#FFFFFF"
//                       radius: 4;
//                       color: Qt.rgba(43/255,43/255,43/255, 0.2)
//                       implicitHeight: 100; implicitWidth: 580
//                    }

//                    activeFocusOnPress: false;
//                    onTextEdited: {
//                        if (text !== "") {
//                            console.log("password_id_3 " + text)
//                            activeFocusOnPress = false
//                            password_input_row_id.input_password[2] = text
//                            password_id_4.focus = true
//                            password_id_4.activeFocusOnPress = true
//                        }
//                    }
//                    Keys.onPressed: (event)=> {
//                        if (Qt.Key_Delete === event.key || Qt.Key_Backspace === event.key) {
//                            focus = false
//                            activeFocusOnPress = false
//                            password_id_2.activeFocusOnPress = true
//                            password_id_2.focus = true
//                        }
//                        console.log("password_id_3 onPressed" + event.key)
//                    }
//                }
//            }


            Rectangle {
                width: 400
                height: 100
                color: Qt.rgba(0,0,0, 0.0)
                TextField {
                    id : password_id_4
                    width: 400
                    height: 100
                    color: "#ffffff"
                    maximumLength: 4
                    echoMode: TextInput.Password
                    font.pixelSize: 60
                    font.weight: Font.Bold
                    font.letterSpacing : 20
                    passwordCharacter: "*"
                    anchors.centerIn: parent
                    verticalAlignment : Text.AlignVCenter
                    horizontalAlignment : Text.AlignHCenter

                    background: Rectangle {
                       border.width: 1;
                       border.color: "#FFFFFF"
                       radius: 4;
                       color: Qt.rgba(43/255,43/255,43/255, 0.2)
                       implicitHeight: 100; implicitWidth: 580
                    }

                    activeFocusOnPress: true;
                    focus:true
                    onTextEdited: {
                        //TODO 修改判断逻辑
                        // 更新输入的密码
                        password_input_row_id.new_input_password = text
                        if (text !== "") {
                            // console.log("password_id_4: " + text)
//                            activeFocusOnPress = false
//                            password_input_row_id.input_password[3] = text
//                            console.log("input_password: " + password_input_row_id.input_password)
//                            console.log("target_password: " + password_input_row_id.target_password)
//                            for(var i = 0; i < password_input_row_id.input_password.length; ++i) {
//                                if (password_input_row_id.input_password[i] !== password_input_row_id.target_password[i]) {
//                                    return
//                                }
//                            }
//                           console.log("input_password pass" )
//                           password_content_id.passwordSuccess()

                            // console.log("new_input_password: " + password_input_row_id.new_input_password)
                            // 输入密码长度为4
                            if(password_input_row_id.new_input_password.length == 4) {
                                activeFocusOnPress = false
                                // console.log("input_password: " + password_input_row_id.new_input_password)
                                // console.log("target_password: " + password_input_row_id.target_password)
                                if(password_input_row_id.new_input_password !== password_input_row_id.target_password) {
                                    console.log("input_password is not right!")
                                    return
                                }
                                console.log("input_password pass" )
                                password_content_id.passwordSuccess()
                            }
                        }
                    }
                    Keys.onPressed: (event)=> {
                        if (Qt.Key_Delete === event.key || Qt.Key_Backspace === event.key) {
                            // focus = false
                            // activeFocusOnPress = false
                            // password_id_3.activeFocusOnPress = true
                            // password_id_3.focus = true
                        }
                        console.log("password_id_4 onPressed: " + event.key)
                    }
                }
            }

        }

    }
}
