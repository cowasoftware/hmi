import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import WorkClass 1.0
//import MsgType 1.0

Item {
    id: rootid
    //    anchors.fill: parent
    width: 1082
    height: 1090
    property int cleanFlag: 1
    property int dumpFlag: 1
    property int m_nWaterLine: 0
    signal qmlSignalClean(int mode, int onOff) //清洗信号
    signal qmlSignalUpdateData(int dataType) //切换界面的时候更新数据
    signal qmlSignalTopDebug(int mode, int onOff) //上装调试信号
    
    //一键启动
    Rectangle {
        id: swith_id
        x: 42
        y: 90
        width: 1002
        height: 166
        //color: "#333333"
        radius: 14
        
        Image {
            width: 1006
            height: 170
            source: "qrc:/resource/asset/image/tops/cleanning/background/background.png"
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
        
        Rectangle {
            id: clean_swith_id
            x: 40
            y: 26
            width: 100
            height: 100
            radius: 60
            property bool is_select: false
            //opacity: 0.5
            color: Qt.rgba(0, 0, 0, 0.0)
            Image {
                width: 110
                height: 110
                source: clean_swith_id.is_select ? "qrc:/resource/asset/image/tops/cleanning/button/open/one-buttonstart.png" : "qrc:/resource/asset/image/tops/cleanning/button/Unopened/one-buttonstart.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    clean_swith_id.is_select = !clean_swith_id.is_select
                    //clean_swith_id.color = clean_swith_id.is_select ? "#5B89FF": "#333333"
                    if (!clean_swith_id.is_select) { // 如果总开关关闭, 其他模式选择要变灰色
                        //if (clean_mode_id.selected_id != null) {
                        //clean_mode_id.selected_id.color = "#333333"
                        //}
                    }
                }
            }
            onIs_selectChanged: { //总开关状态切换，下发指令, 一键启动
                if (clean_swith_id.is_select)
                {
                    if (rect_clean_id.color == "#3f4963")
                    {
                        rect_clean_id.color = "#5B89FF"
                    }
                    if (rect_standard_id.color == "#3f4963")
                    {
                        rect_standard_id.color = "#5B89FF"
                    }
                    if (rect_strong_id.color == "#3f4963")
                    {
                        rect_strong_id.color = "#5B89FF"
                    }
                    rootid.qmlSignalClean(CMsgType.CmdType.WORK_START, 1)
                    if (rect_strong_id.state == 'selected')
                    {
                        rootid.qmlSignalClean(CMsgType.CmdType.FAN_STRONG_MODE, 1)
                    }else if (rect_standard_id.state == 'selected')
                    {
                        rootid.qmlSignalClean(CMsgType.CmdType.FAN_STANDARD_MODE, 1)
                    }else
                    {
                        rootid.qmlSignalClean(CMsgType.CmdType.FAN_CLEAN_MODE, 1)
                    }
                    
                }else
                {
                    if (rect_clean_id.color == "#5b89ff")
                    {
                        rect_clean_id.color = "#3f4963"
                    }
                    if (rect_standard_id.color == "#5b89ff")
                    {
                        rect_standard_id.color = "#3f4963"
                    }
                    if (rect_strong_id.color == "#5b89ff")
                    {
                        rect_strong_id.color = "#3f4963"
                    }
                    rootid.qmlSignalClean(CMsgType.CmdType.WORK_START, 0)
                }
            }
        }
        
        
        Rectangle { // 模式选择1
            x: 463
            y: 43
            width: 480
            height: 80
            color: "#333333"
            Rectangle {
                id: rect_clean_id
                width: 160
                height: 80
                color: "#3f4963"
                Text {
                    width: 48
                    height: 34
                    x: 56
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "保洁"
                    font.pixelSize: 24
                    font.styleName: "Regular"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // if (!clean_swith_id.is_select)
                        // { // 只有总开关打开时 才相应
                        //     return
                        // }
                        rect_clean_id.state == 'selected' ? rect_clean_id.state = "": rect_clean_id.state = 'selected';
                        if (rect_clean_id.state == 'selected')
                        {
                            rect_strong_id.color = "#333333"
                            rect_standard_id.color = "#333333"
                            rect_clean_id.color = clean_swith_id.is_select ? "#5B89FF" : "#3f4963"
                            
                            rect_strong_id.state = "unselected"
                            rect_standard_id.state = "unselected"
                            if (clean_swith_id.is_select)
                            { // 只有总开关打开时 才相应
                                rootid.qmlSignalClean(CMsgType.CmdType.FAN_CLEAN_MODE, 1)
                            }
                            
                        }
                    }
                }
            }
            Rectangle {
                id: rect_standard_id
                width: 160
                height: 80
                x: 160
                color: "#333333"
                Text {
                    width: 48
                    height: 34
                    x: 56
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "标准"
                    font.pixelSize: 24
                    font.styleName: "Regular"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // if (!clean_swith_id.is_select)
                        // { // 只有总开关打开时 才相应
                        //     return
                        // }
                        rect_standard_id.state == 'selected' ? rect_standard_id.state = "": rect_standard_id.state = 'selected';
                        if (rect_standard_id.state == 'selected')
                        {
                            rect_clean_id.color = "#333333"
                            rect_strong_id.color = "#333333"
                            rect_standard_id.color = clean_swith_id.is_select ? "#5B89FF" : "#3f4963"
                            
                            rect_clean_id.state = "unselected"
                            rect_strong_id.state = "unselected"
                            if (clean_swith_id.is_select)
                            { // 只有总开关打开时 才相应
                                rootid.qmlSignalClean(CMsgType.CmdType.FAN_STANDARD_MODE, 1)
                            }
                            
                        }
                    }
                }
                
                
            }
            Rectangle {
                id: rect_strong_id
                width: 160
                height: 80
                
                x: 320
                color: "#333333"
                Text {
                    width: 48
                    height: 34
                    x: 56
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "强劲"
                    font.pixelSize: 24
                    font.styleName: "Regular"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // if (!clean_swith_id.is_select)
                        // { // 只有总开关打开时 才相应
                        //     return
                        // }
                        rect_strong_id.state == 'selected' ? rect_strong_id.state = "": rect_strong_id.state = 'selected';
                        if (rect_strong_id.state == 'selected')
                        {
                            rect_clean_id.color = "#333333"
                            rect_standard_id.color = "#333333"
                            rect_strong_id.color = clean_swith_id.is_select ? "#5B89FF" : "#3f4963"
                            
                            rect_clean_id.state = "unselected"
                            rect_standard_id.state = "unselected"
                            if (clean_swith_id.is_select)
                            { // 只有总开关打开时 才相应
                                rootid.qmlSignalClean(CMsgType.CmdType.FAN_STRONG_MODE, 1)
                            }
                            
                        }
                    }
                }
            }
        }
    }
    
    //扫盘
    Rectangle {
        id: sweep_id
        x: 40
        y: 296
        width: 637
        height: 332
        radius: 14
        Image {
            width: 641
            height: 336
            source: "qrc:/resource/asset/image/tops/cleanning/background/sweepingbackground.png"
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
        
        Rectangle {
            x: 80
            y: 102
            width: 64
            height: 64
            color: Qt.rgba(0, 0, 0, 0.0)
            Image {
                width: 64
                height: 64
                source: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/Sweepthedisk.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
        }
        Rectangle {
            x: 77
            y: 194
            width: 64
            height: 48
            
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Text {
                width: 64
                height: 48
                anchors.fill: parent
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("扫盘")
                font.pixelSize: 32
                font.styleName: "Regular"
                
            }
        }
        
        GridLayout {
            x: 201
            y: 40
            columns: 3
            columnSpacing: 60
            rowSpacing: 92
            
            Repeater {
                model : [
                    {image: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/acceleration.png"},
                    {image: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/angledown.png"},
                    {image: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/heightraised.png"},
                    {image: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/deceleration.png"},
                    {image: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/angleopen.png"},
                    {image: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/altitudedrop.png"},
                ]
                Rectangle {
                    id: sweep_rectange_item_id
                    color: "#3f4963"
                    radius: 8
                    width: 80
                    height: 80
                    Image {
                        width: 44
                        height: 44
                        source: modelData.image
                        fillMode: Image.PreserveAspectFit
                        anchors.centerIn: parent
                    }
                    function onLongPressItem(index) {
                        console.log("timer trigger", index)
                        sweep_rectange_item_id.state  =  'selected';
                        if (index === 0) { //加速
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.BRUSH_SPEED_ACC, 1)
                        }else if (index === 1) {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.LEFT_BRUSH_EXTEND, 1)
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.RIGHT_BRUSH_EXTEND, 1)
                        }else if (index === 2) {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.LEFT_BRUSH_UP, 1)
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.RIGHT_BRUSH_UP, 1)
                        }else if (index === 3) {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.BRUSH_SPEED_MIN, 1)
                        }else if (index === 4) {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.LEFT_BRUSH_NARROW, 1)
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.RIGHT_BRUSH_NARROW, 1)
                        }else {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.LEFT_BRUSH_DOWN, 1)
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.RIGHT_BRUSH_DOWN, 1)
                        }
                    }
                    function onLongPressItemFinish(index) {
                        sweep_rectange_item_id.state  =  "";
                        if (index === 0) { //加速
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.BRUSH_SPEED_ACC, 0)
                        }else if (index === 1) {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.LEFT_BRUSH_EXTEND, 0)
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.RIGHT_BRUSH_EXTEND, 0)
                        }else if (index === 2) {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.LEFT_BRUSH_UP, 0)
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.RIGHT_BRUSH_UP, 0)
                        }else if (index === 3) {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.BRUSH_SPEED_MIN, 0)
                        }else if (index === 4) {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.LEFT_BRUSH_NARROW, 0)
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.RIGHT_BRUSH_NARROW, 0)
                        }else {
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.LEFT_BRUSH_DOWN, 0)
                            rootid.qmlSignalTopDebug(CMsgType.CmdType.RIGHT_BRUSH_DOWN, 0)
                        }
                    }
                    Timer {
                        id: timer_id
                        interval: 500; 
                        running: false; 
                        repeat: true;
                        property real index : -1;
                        onTriggered: {
                            console.log("timer trigger", index)
                            onLongPressItem(index)
                        }
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onPressed:  {
                            console.log("onPressed", modelData)
                            console.log(index)
                            onLongPressItem(index)
                            timer_id.index = index
                            timer_id.start()
                        }
                        onReleased: {
                            console.log("onReleased", modelData)
                            console.log(index)
                            timer_id.stop()
                            onLongPressItemFinish(index)
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: sweep_rectange_item_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }
            }
            
            
            
            
        }
        GridLayout {
            x: 213
            y: 145
            columns: 3
            columnSpacing: 84
            Repeater {
                model: [qsTr("速度"), qsTr("角度"), qsTr("高度")]
                
                Rectangle {
                    id: text_rectange_item_id
                    color: Qt.rgba(0, 0, 0, 0.0)
                    width: 56
                    height: 42
                    Text {
                        width: 56
                        height: 42
                        anchors.centerIn: parent
                        color: "#ffffff"
                        text: qsTr(modelData)
                        font.pixelSize: 28
                        font.styleName: "Regular"
                    }
                }
            }
            
        }
        
    }
    
    //风机
    Rectangle {
        id: fan_id
        x: 717
        y: 296
        width: 325
        height: 332
        radius: 14
        Image {
            width: 329
            height: 336
            source: "qrc:/resource/asset/image/tops/cleanning/background/fanbackground.png"
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
        
        Rectangle {
            x: 60
            y: 90
            width: 64
            height: 64
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Image {
                width: 64
                height: 64
                source: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/fan.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
        }
        
        Rectangle {
            x: 60
            y: 194
            width: 64
            height: 48
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Text {
                width: 64
                height: 48
                anchors.fill: parent
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("风机")
                font.pixelSize: 32
                font.styleName: "Regular"
                
            }
        }
        
        GridLayout {
            x: 184
            y: 40
            columns: 1
            //columnSpacing: 60
            rowSpacing: 92
            
            Repeater {
                model : [
                    {image: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/acceleration.png"},
                    {image: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/deceleration.png"},
                ]
                Rectangle {
                    id: fan_rectange_item_id
                    color: "#293143"
                    width: 80
                    height: 80
                    radius: 8
                    Image {
                        width: 44
                        height: 44
                        source: modelData.image
                        fillMode: Image.PreserveAspectFit
                        anchors.centerIn: parent
                    }
                    function onLongPressItem(index) {
                        console.log("timer trigger", index)
                        if (index === 0) {
                                fan_rectange_item_id.state  =  'selected';
                                rootid.qmlSignalTopDebug(CMsgType.CmdType.FAN_SPEEDACC, 1)
                            }else if (index === 1) {
                                fan_rectange_item_id.state  =  'selected';
                                rootid.qmlSignalTopDebug(CMsgType.CmdType.FAN_SPEEDMIN, 1)
                            }
                        
                    }
                    function onLongPressItemFinish(index) {
                        fan_rectange_item_id.state  =  "";
                            if (index === 0) {
                                rootid.qmlSignalTopDebug(CMsgType.CmdType.FAN_SPEEDACC, 0)
                            }else if (index === 1) {
                                rootid.qmlSignalTopDebug(CMsgType.CmdType.FAN_SPEEDMIN, 0)
                            } else {
                                // nothing to do
                            }
                        
                    }
                    Timer {
                        id: timer_id
                        interval: 500; 
                        running: false; 
                        repeat: true;
                        property real index : -1;
                        onTriggered: {
                            console.log("timer trigger", index)
                            onLongPressItem(index)
                        }
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onPressed:  {
                            console.log("onPressed", modelData)
                            console.log(index)
                            onLongPressItem(index)
                            timer_id.index = index
                            timer_id.start()
                        }
                        onReleased: {
                            console.log("onReleased", modelData)
                            console.log(index)
                            timer_id.stop()
                            onLongPressItemFinish(index)
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: fan_rectange_item_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }
            }
            
            
            
            
        }
        Rectangle {
            x: 196
            y: 145
            width: 56
            height: 42
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Text {
                width: 56
                height: 42
                anchors.fill: parent
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("速度")
                font.pixelSize: 28
                font.styleName: "Regular"
                
            }
        }
    }
    
    //顶工作灯
    Rectangle {
        id: top_light_id
        x: 40
        y: 668
        width: 1002
        height: 166
        radius: 14
        Image {
            width: 1006
            height: 170
            source: "qrc:/resource/asset/image/tops/cleanning/background/background.png"
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
        Rectangle {
            x: 40
            y: 61
            width: 44
            height: 44
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Image {
                width: 44
                height: 44
                source: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/Topworklight.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
        }
        Rectangle {
            x: 104
            y: 59
            width: 128
            height: 48
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Text {
                width: 128
                height: 48
                anchors.fill: parent
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("顶工作灯")
                font.pixelSize: 32
                font.styleName: "Regular"
                
            }
        }
        // 开关
        Switch {
            id: top_light_switch_id
            x: 272
            y: 53
            width: 120
            height: 60
            
            indicator: Rectangle {
                width: 120
                height: 60
                radius: height / 2
                property bool sw_sts: top_light_switch_id.checked
                color: top_light_switch_id.checked ? "#5B89FF": "#3B3B3B"
                border.width: 1
                border.color: top_light_switch_id.checked ? "#5B89FF": "#3B3B3B"
                onSw_stsChanged: {
                    if (top_light_switch_id.checked)
                    {
                        rootid.qmlSignalClean(CMsgType.WORK_LIGHT, 1)
                    }else
                    {
                        rootid.qmlSignalClean(CMsgType.WORK_LIGHT, 0)
                    }
                    
                }
                
                Rectangle {
                    x: top_light_switch_id.checked ? parent.width - width - 2: 1
                    width: top_light_switch_id.checked ? parent.height - 4: parent.height - 2
                    height: width
                    radius: width / 2
                    anchors.verticalCenter: parent.verticalCenter
                    color: "white"
                    border.color: "#D5D5D5"
                    
                    Behavior on x {
                        NumberAnimation {
                            duration: 100
                        }
                    }
                }
            }
        }
        
        Rectangle {
            x: 593
            y: 62
            width: 42
            height: 42
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Image {
                width: 42
                height: 42
                source: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/highpressurecleaning.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
        }
        
        Rectangle {
            x: 656
            y: 59
            width: 128
            height: 48
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Text {
                width: 128
                height: 48
                anchors.fill: parent
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("高压清洗")
                font.pixelSize: 32
                font.styleName: "Regular"
                
            }
        }
        // 开关
        Switch {
            id: hig_pre_switch_id
            x: 824
            y: 53
            width: 120
            height: 60
            
            
            indicator: Rectangle {
                width: 120
                height: 60
                radius: height / 2
                property bool sw_sts: hig_pre_switch_id.checked
                color: hig_pre_switch_id.checked ? "#5B89FF": "#3B3B3B"
                border.width: 1
                border.color: hig_pre_switch_id.checked ? "#5B89FF": "#3B3B3B"
                onSw_stsChanged: {
                    if (hig_pre_switch_id.checked)
                    {
                        rootid.qmlSignalClean(CMsgType.HIGH_PRECLEAN_START_MODE, 1)
                    }else
                    {
                        rootid.qmlSignalClean(CMsgType.HIGH_PRECLEAN_STOP_MODE, 1)
                    }
                }
                
                Rectangle {
                    x: hig_pre_switch_id.checked ? parent.width - width - 2: 1
                    width: hig_pre_switch_id.checked ? parent.height - 4: parent.height - 2
                    height: width
                    radius: width / 2
                    anchors.verticalCenter: parent.verticalCenter
                    color: "white"
                    border.color: "#D5D5D5"
                    
                    Behavior on x {
                        NumberAnimation {
                            duration: 100
                        }
                    }
                }
            }
        }
        
        
    }
    
    //箱体操作
    Rectangle {
        id: dump_id
        x: 40
        y: 874
        width: 1002
        height: 166
        radius: 14
        Image {
            width: 1006
            height: 170
            source: "qrc:/resource/asset/image/tops/cleanning/background/background.png"
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
        Rectangle {
            x: 53
            y: 57
            width: 64
            height: 64
            color: Qt.rgba(0, 0, 0, 0.0) //透明背景色
            Image {
                width: 64
                height: 64
                source: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/Boxtilt.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
        }
        
        Rectangle {
            x: 516
            y: 57
            width: 64
            height: 64
            color: Qt.rgba(0, 0, 0, 0.0)
            Image {
                width: 64
                height: 64
                source: "qrc:/resource/asset/image/tops/cleanning/icon/turnon-开启/Boxhoming.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
        }
        Row {
            leftPadding: 144
            topPadding: 43
            spacing: 304
            anchors.fill: parent
            Repeater {
                id: box_mode_id
                anchors.fill: parent
                property var selected_id: null
                model: [
                    {text: qsTr("箱体倾斜")},
                    {text: qsTr("箱体归位")},
                ]
                Rectangle {
                    id: box_button_id
                    radius: 10
                    width: 160
                    height: 80
                    color: "#3f4963"
                    Text {
                        width: 120
                        height: 48
                        anchors.fill: parent
                        color: "#ffffff"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: modelData.text
                        font.pixelSize: 32
                        font.styleName: "Regular"
                        
                    }
                    function onLongPressItem(index)
                    {
                        console.log("timer trigger", index)
                        box_button_id.state = 'selected';
                        if (index === 0)
                        {
                            rootid.qmlSignalClean(CMsgType.TANK_TILT, 1)
                        }else {
                            rootid.qmlSignalClean(CMsgType.TANK_RESET, 1)
                        }
                    }
                    function onLongPressItemFinish(index)
                    {
                        box_button_id.state = "";
                        if (index === 0)
                        {
                            rootid.qmlSignalClean(CMsgType.TANK_TILT, 0)
                        }else {
                            rootid.qmlSignalClean(CMsgType.TANK_RESET, 0)
                        }
                    }
                    Timer {
                        id: timer_id
                        interval: 500;
                        running: false;
                        repeat: true;
                        property real index: -1;
                        onTriggered: {
                            console.log("timer trigger", index)
                            onLongPressItem(index)
                        }
                    }
                    
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            onLongPressItem(index)
                            timer_id.index = index
                            timer_id.start()
                        }
                        onReleased: {
                            timer_id.stop()
                            onLongPressItemFinish(index)
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: box_button_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }
            }
        }
        
    }
    Connections {
        target: rootid
        function onQmlSignalClean(val, onval)
        {
            CUIDataHandle.slotSetTopCleanCmd(val, onval)
        }
        function onQmlSignalUpdateData(dataType)
        {
            CUIDataHandle.slotDiagnosisUpdateData(dataType)
        }
        function onQmlSignalTopDebug(val, onOff)
        {
            CUIDataHandle.slotSetTopCleanCmd(val, onOff)
        }
    }
    
}
