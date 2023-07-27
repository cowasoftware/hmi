import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import WorkClass 1.0

// 诊断信息
Item {
    id: item_id
    width: 1446
    height: 960

    DiaStatusCode{
        id: statuscode_id
    }

    signal qmlSignalDiagnosis(int mode, int onOff) //下发诊断指令
    signal qmlSignalUpdateData(int dataType) //切换界面的时候更新数据
    property int ioInit: 2
    //IO诊断
    property int m_nLeft: ioInit
    property int m_nRight: ioInit
    property int m_nWorkFlag:ioInit
    property int m_nTrunOnFlag:ioInit
    property int m_nLowBeam_I:ioInit
    property int m_nSmallLight:ioInit
    property int m_nAutoDrive:ioInit
    property int m_nEmergencyFlash:ioInit
    property int m_nStop:ioInit

    property int m_nBrakeOil_line:ioInit
    property int m_nBox_up:ioInit
    property int m_nBox_dowm:ioInit
    property int m_nBox_Arrive:ioInit
    property int m_nChengGan_Arrive:ioInit
    property int m_nEban_switch:ioInit
    property int m_nBoxDoor_switch:ioInit
    property int m_nLeftBrush_arrive:ioInit
    property int m_nRightBrush_arrive:ioInit
    property int m_nLeftBrush_open_s:ioInit
    property int m_nLeftBrush_close_s:ioInit
    property int m_nRightBrush_open_s:ioInit
    property int m_nRightBrush_close_s:ioInit
    property int m_ndustbin_returnSwitch:ioInit
    property string m_strWaterLine_show:"--"

    property int m_nTurnLeftLight:ioInit
    property int m_nTurnRightLight:ioInit
    property int m_nLowBeam:ioInit
    property int m_nWorkLight_relay:ioInit
    property int m_nsmall_light:ioInit
    property int m_nreversing_light:ioInit
    property int m_nbrake_light:ioInit
    property int m_nReversing_buzzer:ioInit

    property int m_nBoxDoor_open:ioInit
    property int m_nBoxDoor_close:ioInit
    property int m_nLeftBrush_up:ioInit
    property int m_nLeftBrush_down:ioInit
    property int m_nLeftBrush_open:ioInit
    property int m_nLeftBrush_close:ioInit
    property int m_nRightBrush_up:ioInit
    property int m_nRightBrush_down:ioInit
    property int m_nRightBrush_open:ioInit
    property int m_nRightBrush_close:ioInit
    property int m_nEban_switch_open:ioInit
    property int m_nEban_switch_close:ioInit
    property int m_nXiZwitch_up:ioInit
    property int m_nXiZwitch_down:ioInit
    property int m_nDustbin_up:ioInit
    property int m_nDustbin_down:ioInit
    property int m_nLVWaterRoad_relay:ioInit
    property int m_nSewagecyclevalve:ioInit
    property int m_nDelayCutDown:ioInit

    //电池诊断 12EF
    property string m_strBattOverTempFault:"--"
    property string m_strInsulationFault:"--"
    property string m_strCellLessVoltWarning:"--"
    property string m_strCellOverVoltWarning:"--"
    property string m_strBattLessElectWarning:"--"
    property string m_strPositiveRelayAdhesion:"--"
    property string m_strPTCRelayAdhesion:"--"
    property string m_strSOHWarning:"--"
    property string m_strPositionRelaySts:"--"
    property string m_strPTCRelaySts:"--"
    property string m_strBattVoltImbalance:"--"
    property string m_strDischgOverCurrent:"--"
    property string m_strChgOverCurrent:"--"
    property string m_strItselfCANerror:"--"
    property string m_strBattGeneralLessVolt:"--"
    property string m_strBattGeneralOverVolt:"--"
    property string m_strBMSHardwareFault:"--"
    property string m_strCANerror:"--"
    property string m_strCCsignConnetSts:"--"
    property string m_strPrechargeSts:"--"
    property string m_strBMSsts:"--"
    property string m_strBackChgEnb:"--"
    property string m_strWarmModel:"--"
    property string m_strBalanceSts:"--"
    property string m_strSOCLow:"--"
    property string m_strCurrentSensorFault:"--"
    property string m_strTempSensorFault:"--"
    property string m_strNegativeRelayAdhesion:"--"
    property string m_strPrechgRelaySts:"--"
    property string m_strNegativeRelaySts:"--"
    property string m_strDCchgPositiveRelaySts:"--"
    property string m_strDCchgGunOverTempFault:"--"
    property string m_strCellCollectLineCutFault:"--"
    property string m_strPrechgRelayAdhesion:"--"
    property string m_strDCchgPositiveRelayAdhesion:"--"
    property string m_strWakeUpType:"--"
    property string m_strBattTempImbalanceFault:"--"
    property string m_strBattLessTempFault:"--"
    property string m_strWarmSts:"--"
    //13EF
    property string m_strGeneralVolt:"--"
    property string m_strGeneralCurrent:"--"
    property string m_strSOC:"--"
    property string m_strBattSerialData:"--"
    property string m_strCellVoltSensorFault:"--"
    property string m_strGeneralVoltSensorFault:"--"
    property string m_str12VLessVolt:"--"
    property string m_str12VOverVolt:"--"
    //33EF
    property string m_strBattMaxTemp:"--"
    property string m_strBattMaxTempCode:"--"
    property string m_strBattMinTemp:"--"
    property string m_strBattMinTempCode:"--"
    property string m_strDCchgGunBaseTemp0:"--"
    property string m_strDCchgGunBaseTemp1:"--"
    property string m_strAverageTemp:"--"
    //11EF
    property string m_strSystemFaultLevel:"--"
    property string m_strHVlock:"--"
    property string m_strPowerDownReq:"--"
    property string m_strBMSMaxDischgPower:"--"
    property string m_strBMSMaxChgPower:"--"
    property string m_strDCchgVoltDemand:"--"
    property string m_strDCchgCurrentDemand:"--"
    property string m_strSystemStsCode:"--"

    //主驱诊断信息
    property string m_strMotSpeed:"--"
    property string m_strMotTorque:"--"
    property string m_strRotaryWarning:"--"
    property string m_strIntePass:"--"
    property string m_strGearSts:"--"
    property string m_strBackBrake:"--"
    property string m_strAccPdlSts:"--"
    property string m_strBusbardischarg:"--"
    property string m_strBrakeActive:"--"
    property string m_strMotSpeedValid:"--"

    property string m_strOverCurrentFault:"--"
    property string m_strPowerLimtWarning:"--"
    property string m_strMCUTempWarning:"--"
    property string m_strMotTempWarning:"--"
    property string m_strBusbarOverVoltFault:"--"
    property string m_strBusbarLessVoltFault:"--"
    property string m_strSpeedControlValid:"--"
    property string m_strGeneralFaultWarning:"--"
    property string m_strGearWarning:"--"
    property string m_strHoldReq:"--"
    property string m_strApdlPercent:"--"


    //行车制动诊断信息 61
    property string m_strEHB_WorkSts:"--"
    property string m_strBrakePress:"--"
    property string m_strpedalPercent:"--"
    property string m_strPistonDisplacement:"--"
    property string m_strTargetPress:"--"
    //property int m_nBrakeSts:0

    property string m_strParkReq:"--"
    property string m_strBrakeSts:"--"
    property string m_strfaultLevel:"--"
    //5F
    property string m_strfaultCode1:"--"
    property string m_strfaultCode2:"--"
    property string m_strfaultCode3:"--"
    //60
    property string m_nBrakeSts60:"--"
    property string m_nParklight_sts:"--"
    property string m_nFaultlight_sts:"--"
    property string m_nSwitch_sts:"--"
    property string m_nSystem_sts:"--"
    property string m_nFault_message:"--"


    //诊断EPS信息
    property string m_strWorkModel:"--"
    property string m_strTargeTangle:"--"
    property string m_strWheelPalstance:"--"
    //property string m_strTargetTorque:"--"

    property string m_strAutoCMD_model:"--"
    property string m_strCurrentangle:"--"
    //EPS 5C
    property string m_strOut_torque:"--"
    property string m_strTarget_torque:"--"
    property string m_strFaultCode_92:"--"

    //诊断12VDC信息
    property string m_strOutEnable:"--"
    property string m_strState:"--"
    property string m_strINVoltage:"--"
    property string m_strINCurrent:"--"
    property string m_strDCDCTemperature:"--"
    property string m_strOverTemperature:"--"

    property string m_strOut_voltage:"--"
    property string m_strOut_current:"--"
    property string m_strIn_over_current:"--"
    property string m_strOut_over_current:"--"
    property string m_strIn_over_voltage:"--"
    property string m_strIn_less_voltage:"--"
    property string m_strOut_over_voltage:"--"
    property string m_strOut_less_voltage:"--"

    //诊断48VDC信息
    property string m_strOUTVolt:"--"
    property string m_strOUTCurrent:"--"
    property string m_strDCSts:"--"
    property string m_strOUTCutDownSts:"--"
    property string m_strFaultLevel:"--"
    property string m_strRadiatorTemp:"--"
    property string m_strINCutDownSts:"--"

    //诊断风机信息902
    property string m_strFaultLevl:"--"
    property string m_strModSts:"--"
    property string m_strEnSts:"--"
    property string m_strPrechargeAllow:"--"
    property string m_strDirSts:"--"
    property string m_strActTorValid:"--"
    property string m_strActSpdValid:"--"
    property string m_strActTor:"--"
    property string m_strActSpd:"--"

    //A02
    property string m_strDCVolt:"--"
    property string m_strDCCur:"--"
    property string m_strACCur:"--"

    //B02
    property string m_strMotorMinAvaTor:"--"
    property string m_strMotorMaxAvaTor:"--"
    property string m_strMotorIGBTTemp:"--"
    property string m_strMTemp:"--"
    property string m_strCTemp:"--"

    //C02
    property string m_strMOvSpdSts:"--"
    property string m_strMBlockSts:"--"
    property string m_strMOvTempSts:"--"
    property string m_strMOvCurSts:"--"
    property string m_strMShrSts:"--"
    property string m_strMShrGrdSts:"--"
    property string m_strCOvTempSts:"--"
    property string m_strCAuxBatSts:"--"
    property string m_strPreChaSts:"--"
    property string m_strIGBTModSts:"--"
    property string m_strIGBTOvTempSts:"--"
    property string m_strIGBTOvCurSts:"--"
    property string m_strCOvVoltSts:"--"
    property string m_strCLowVoltSts:"--"
    property string m_strIGBTTempSenSts:"--"
    property string m_strCANFault:"--"
    property string m_strMTempSenSts:"--"
    property string m_strCTempSenSts:"--"
    property string m_strCVoltSenSts:"--"
    property string m_strCCurSenSts:"--"
    property string m_strACCurSenSts:"--"
    property string m_strCTranFaultSts:"--"
    property string m_strMCutOffSts:"--"
    //扫盘信息
    property string m_strMainVoltage:"--"
    property string m_strCurrentMotcurrent:"--"
    property string m_strEnableSts:"--"
    property string m_strWheelSts:"--"
    property string m_strMotTemperature:"--"
    property string m_strMotCurrentSpeed: "--"
    property string m_strOverCurrent:"--"
    property string m_strOverVoltage:"--"
    property string m_strSweepOverTemperature:"--"
    property string m_strLochedRotor:"--"
    property string m_strHallSignalError:"--"
    property string m_strMotFualtItself:"--"
    property bool slType: false
    property bool srType: false

    //诊断高压水泵信息 15Data
    property string m_strHigMotspeed:"--"
    //property string m_strMCUintSts:"--"
    property string m_strMOTBusbarVolt:"--"
    property string m_strMotTemp:"--"
    property string m_strIGBTTemp:"--"
    property string m_strMOT_current_AC:"--"
    property string m_strMOTFaultCodeSign:"--"

    // 16Data
    property string m_strMCUintSts:"--"
    property string m_strMCUModelSts:"--"
    //诊断通信信息
    property int commuInit:2
    property int m_nBMS_CANerror:commuInit
    property int m_nMCU_CANerror:commuInit

    property int m_nEHB_CANerror:commuInit
    property int m_nEPB_CANerror:commuInit
    property int m_nEPS_CANerror:commuInit
    property int m_nDC48V_CANerror:commuInit
    property int m_nAC_CANerror:commuInit
    property int m_nADU_CANerror:commuInit
    property int m_nICU_CANerror:commuInit
    property int m_nDC12V_CANerror:commuInit
    property int m_nGPS_CANerror:commuInit
    property int m_nFJI_CANerror:commuInit
    property int m_nWP_CANerror:commuInit
    property int m_nSPL_CANerror:commuInit
    property int m_nSPR_CANerror:commuInit

    property int indexTemp: 0
    property int currentIndex: gConfig.currentIndex
    // 左右切换tab按钮
    // 上一个tab
    property var lastTab: ["qrc:/resource/asset/image/diagnosis/lastTab_light.png","qrc:/resource/asset/image/diagnosis/lastTab.png"]
    // 下一个tab
    property var nextTab: ["qrc:/resource/asset/image/diagnosis/nextTab_light.png","qrc:/resource/asset/image/diagnosis/nextTab.png"]

    Rectangle {
        id: diagnosis_infor_id
        x: 0
        y: 0
        width: 1446
        height: 100
        color: gConfig.titleBackground[currentIndex]

        Text {
            id: text1
            anchors.centerIn:parent
            width: 144
            height: 50
            color: gConfig.textColor[currentIndex]
            text: qsTr("诊断信息")
            font.pixelSize: 36
            font.styleName: "Regular"
            horizontalAlignment : Text.AlignHCenter
        }
    }
    Rectangle {
        id: rootid
        x: 0
        y: 100
        width: 1446
        height: 860
        TabView {
            id: tabview_id
            anchors.fill: parent
            property string selected_color :  "#5B89FF"
            property string unselected_color :  gConfig.tabButtonColor[currentIndex]
           
            style: TabViewStyle {
                frameOverlap: 1
                tab: Rectangle { // for each tab
                    color: styleData.selected ? tabview_id.selected_color : gConfig.tabButtonColor[currentIndex]
                    implicitWidth: 201
                    implicitHeight: 90
                    // onColorChanged: {
                    //     console.log("current: "+ currentIndex)
                    //     console.log("color: "+ gConfig.tabButtonColor[currentIndex])
                    // }
                    radius: 2
                    Text {
                        width: 150
                        height: 39
                        anchors.centerIn: parent
                        verticalAlignment : Text.AlignVCenter
                        horizontalAlignment : Text.AlignHCenter
                        text: styleData.title
                        font.pixelSize: styleData.selected ? 32 : 28
                        color: gConfig.textColor[currentIndex]
                    }

                }

                tabBar:  Rectangle { color: gConfig.tabButtonColor[currentIndex] }
            }
	    property int myIndex:indexTemp
            currentIndex: 0
            onMyIndexChanged:
            {
                currentIndex = myIndex
            }
            onCurrentIndexChanged: {
                indexTemp = currentIndex
            }


            Component.onCompleted : {
                addTab("IO信息", io_content_id)
                addTab("电池信息", battery_content_id)
                addTab("主驱信息", mainDrive_content_id)
                addTab("制动信息", brake_content_id)
                addTab("EPS信息", eps_content_id)
                addTab("12VDC信息",dc12_content_id )
                addTab("48VDC信息", dc48_content_id)
                //addTab("EPS标定", epsCali_content_id)
                addTab("风机信息", fan_content_id)
                addTab("左扫盘信息", left_content_id)
                addTab("右扫盘信息", right_content_id)
                addTab("高压水泵信息", highPrePumps_content_id)
                addTab("通讯信息", communication_content_id)
            }
        }

        // IO信息
        Component {
            id : io_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle {
                    id: io_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            console.log("选中的index:"+currentIndex)
                            io_rectange_id.state  ==  'selected'  ?  io_rectange_id.state  =  ""  :  io_rectange_id.state  =  'selected';
                            if (io_rectange_id.state  ==  'selected')
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_IO, 1)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_IO_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_IO71_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_IO78_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_IO79_DATA)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_IO, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: io_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }
                Rectangle{
                    x: 420
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel

                            property string str1:statuscode_id.ioStatus[m_nLeft]
                            property string str2:statuscode_id.ioStatus[m_nRight]
                            property string str3:statuscode_id.ioStatus[m_nWorkFlag]
                            property string str4:statuscode_id.ioStatus[m_nTrunOnFlag]
                            property string str5:statuscode_id.ioStatus[m_nLowBeam_I]
                            property string str6:statuscode_id.ioStatus[m_nSmallLight]
                            property string str7:statuscode_id.ioStatus[m_nAutoDrive]
                            property string str8:statuscode_id.ioStatus[m_nEmergencyFlash]
                            property string str9:statuscode_id.ioStatus[m_nStop]

                            property string str10:statuscode_id.ioStatus[m_nBrakeOil_line]
                            property string str11:statuscode_id.ioStatus[m_nBox_up]
                            property string str12:statuscode_id.ioStatus[m_nBox_dowm]
                            property string str13:statuscode_id.ioStatus[m_nBox_Arrive]
                            property string str14:statuscode_id.ioStatus[m_nChengGan_Arrive]
                            property string str15:statuscode_id.ioStatus[m_nEban_switch]
                            property string str16:statuscode_id.ioStatus[m_nBoxDoor_switch]
                            property string str17:statuscode_id.ioStatus[m_nLeftBrush_arrive]
                            property string str18:statuscode_id.ioStatus[m_nRightBrush_arrive]
                            property string str19:statuscode_id.ioStatus[m_nLeftBrush_open_s]
                            property string str20:statuscode_id.ioStatus[m_nLeftBrush_close_s]
                            property string str21:statuscode_id.ioStatus[m_nRightBrush_open_s]
                            property string str22:statuscode_id.ioStatus[m_nRightBrush_close_s]
                            property string str23:statuscode_id.ioStatus[m_ndustbin_returnSwitch]
                            property string str24:m_strWaterLine_show

                            property string str25:statuscode_id.ioStatus[m_nTurnLeftLight]
                            property string str26:statuscode_id.ioStatus[m_nTurnRightLight]
                            property string str27:statuscode_id.ioStatus[m_nLowBeam]
                            property string str28:statuscode_id.ioStatus[m_nWorkLight_relay]
                            property string str29:statuscode_id.ioStatus[m_nsmall_light]
                            property string str30:statuscode_id.ioStatus[m_nreversing_light]
                            property string str31:statuscode_id.ioStatus[m_nbrake_light]
                            property string str32:statuscode_id.ioStatus[m_nReversing_buzzer]

                            property string str33:statuscode_id.ioStatus[m_nBoxDoor_open]
                            property string str34:statuscode_id.ioStatus[m_nBoxDoor_close]
                            property string str35:statuscode_id.ioStatus[m_nLeftBrush_up]
                            property string str36:statuscode_id.ioStatus[m_nLeftBrush_down]
                            property string str37:statuscode_id.ioStatus[m_nLeftBrush_open]
                            property string str38:statuscode_id.ioStatus[m_nLeftBrush_close]
                            property string str39:statuscode_id.ioStatus[m_nRightBrush_up]
                            property string str40:statuscode_id.ioStatus[m_nRightBrush_down]
                            property string str41:statuscode_id.ioStatus[m_nRightBrush_open]
                            property string str42:statuscode_id.ioStatus[m_nRightBrush_close]
                            property string str43:statuscode_id.ioStatus[m_nEban_switch_open]
                            property string str44:statuscode_id.ioStatus[m_nEban_switch_close]
                            property string str45:statuscode_id.ioStatus[m_nXiZwitch_up]
                            property string str46:statuscode_id.ioStatus[m_nXiZwitch_down]
                            property string str47:statuscode_id.ioStatus[m_nDustbin_up]
                            property string str48:statuscode_id.ioStatus[m_nDustbin_down]
                            property string str49:statuscode_id.ioStatus[m_nLVWaterRoad_relay]
                            property string str50:statuscode_id.ioStatus[m_nSewagecyclevalve]
                            property string str51:statuscode_id.ioStatus[m_nDelayCutDown]
                            property bool completedFlag: false

                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '左转向', status : str1})
                                    id_tabModel.append({name : '右转向', status : str2})
                                    id_tabModel.append({name : '工作档', status : str3})
                                    id_tabModel.append({name : '点火档', status : str4})
                                    id_tabModel.append({name : '近光灯', status : str5})
                                    id_tabModel.append({name : '小灯I', status : str6})
                                    id_tabModel.append({name : '无人驾驶', status : str7})
                                    id_tabModel.append({name : '双闪', status : str8})
                                    id_tabModel.append({name : '急停', status : str9})
                                    id_tabModel.append({name : '刹车液位', status : str10})
                                    id_tabModel.append({name : '遥控升箱体', status : str11})
                                    id_tabModel.append({name : '遥控降箱体', status : str12})
                                    id_tabModel.append({name : '箱体升到位', status : str13})
                                    id_tabModel.append({name : '撑杆到位', status : str14})
                                    id_tabModel.append({name : '颚板踏板开关', status : str15})
                                    id_tabModel.append({name : '箱门开关', status : str16})
                                    id_tabModel.append({name : '左扫刷到位', status : str17})
                                    id_tabModel.append({name : '右扫刷到位', status : str18})
                                    id_tabModel.append({name : '左扫刷展', status : str19})
                                    id_tabModel.append({name : '左扫刷收', status : str20})
                                    id_tabModel.append({name : '右扫刷展', status : str21})
                                    id_tabModel.append({name : '右扫刷收', status : str22})
                                    id_tabModel.append({name : '垃圾箱回位开关', status : str23})
                                    id_tabModel.append({name : '水位显示', status : str24})
                                    id_tabModel.append({name : '左转灯', status : str25})
                                    id_tabModel.append({name : '右转灯', status : str26})
                                    id_tabModel.append({name : '近光灯', status : str27})
                                    id_tabModel.append({name : '工作灯继电器', status : str28})
                                    id_tabModel.append({name : '小灯', status : str29})
                                    id_tabModel.append({name : '倒车灯', status : str30})
                                    id_tabModel.append({name : '刹车灯', status : str31})
                                    id_tabModel.append({name : '倒车蜂鸣器', status : str32})
                                    id_tabModel.append({name : '箱门开', status : str33})
                                    id_tabModel.append({name : '箱门关', status : str34})
                                    id_tabModel.append({name : '左扫盘上', status : str35})
                                    id_tabModel.append({name : '左扫盘下', status : str36})
                                    id_tabModel.append({name : '左扫盘展', status : str37})
                                    id_tabModel.append({name : '左扫盘收', status : str38})
                                    id_tabModel.append({name : '右扫盘上', status : str39})
                                    id_tabModel.append({name : '右扫盘下', status : str40})
                                    id_tabModel.append({name : '右扫盘展', status : str41})
                                    id_tabModel.append({name : '右扫盘收', status : str42})
                                    id_tabModel.append({name : '颚板开', status : str43})
                                    id_tabModel.append({name : '颚板关', status : str44})
                                    id_tabModel.append({name : '吸嘴上', status : str45})
                                    id_tabModel.append({name : '吸嘴下', status : str46})
                                    id_tabModel.append({name : '垃圾箱升', status : str47})
                                    id_tabModel.append({name : '垃圾箱降', status : str48})
                                    id_tabModel.append({name : '低压水路继电器', status : str49})
                                    id_tabModel.append({name : '污水循环球阀', status : str50})
                                    id_tabModel.append({name : '延时断电', status : str51})
                                    completedFlag = true;
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_IO_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_IO71_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_IO78_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_IO79_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag)    setProperty(7, "status", str8);
                            }
                            onStr9Changed:{
                                if (completedFlag)    setProperty(8, "status", str9);
                            }
                            onStr10Changed:{
                                if (completedFlag)    setProperty(9, "status", str10);
                            }
                            onStr11Changed:{
                                if (completedFlag)    setProperty(10, "status", str11);
                            }
                            onStr12Changed:{
                                if (completedFlag)    setProperty(11, "status", str12);
                            }
                            onStr13Changed:{
                                if (completedFlag)    setProperty(12, "status", str13);
                            }
                            onStr14Changed:{
                                if (completedFlag)    setProperty(13, "status", str14);
                            }
                            onStr15Changed:{
                                if (completedFlag)    setProperty(14, "status", str15);
                            }
                            onStr16Changed:{
                                if (completedFlag)    setProperty(15, "status", str16);
                            }
                            onStr17Changed:{
                                if (completedFlag)    setProperty(16, "status", str17);
                            }
                            onStr18Changed:{
                                if (completedFlag)    setProperty(17, "status", str18);
                            }
                            onStr19Changed:{
                                if (completedFlag)    setProperty(18, "status", str19);
                            }
                            onStr20Changed:{
                                if (completedFlag)    setProperty(19, "status", str20);
                            }
                            onStr21Changed:{
                                if (completedFlag)    setProperty(20, "status", str21);
                            }
                            onStr22Changed:{
                                if (completedFlag)    setProperty(21, "status", str22);
                            }
                            onStr23Changed:{
                                if (completedFlag)    setProperty(22, "status", str23);
                            }
                            onStr24Changed:{
                                if (completedFlag)    setProperty(23, "status", str24);
                            }
                            onStr25Changed:{
                                if (completedFlag)    setProperty(24, "status", str25);
                            }
                            onStr26Changed:{
                                if (completedFlag)    setProperty(25, "status", str26);
                            }
                            onStr27Changed:{
                                if (completedFlag)    setProperty(26, "status", str27);
                            }
                            onStr28Changed:{
                                if (completedFlag)    setProperty(27, "status", str28);
                            }
                            onStr29Changed:{
                                if (completedFlag)    setProperty(28, "status", str29);
                            }
                            onStr30Changed:{
                                if (completedFlag)    setProperty(29, "status", str30);
                            }
                            onStr31Changed:{
                                if (completedFlag)    setProperty(30, "status", str31);
                            }
                            onStr32Changed:{
                                if (completedFlag)    setProperty(31, "status", str32);
                            }
                            onStr33Changed:{
                                if (completedFlag)    setProperty(32, "status", str33);
                            }
                            onStr34Changed:{
                                if (completedFlag)    setProperty(33, "status", str34);
                            }
                            onStr35Changed:{
                                if (completedFlag)    setProperty(34, "status", str35);
                            }
                            onStr36Changed:{
                                if (completedFlag)    setProperty(35, "status", str36);
                            }
                            onStr37Changed:{
                                if (completedFlag)    setProperty(36, "status", str37);
                            }
                            onStr38Changed:{
                                if (completedFlag)    setProperty(37, "status", str38);
                            }
                            onStr39Changed:{
                                if (completedFlag)    setProperty(38, "status", str39);
                            }
                            onStr40Changed:{
                                if (completedFlag)    setProperty(39, "status", str40);
                            }
                            onStr41Changed:{
                                if (completedFlag)    setProperty(40, "status", str41);
                            }
                            onStr42Changed:{
                                if (completedFlag)    setProperty(41, "status", str42);
                            }
                            onStr43Changed:{
                                if (completedFlag)    setProperty(42, "status", str43);
                            }
                            onStr44Changed:{
                                if (completedFlag)    setProperty(43, "status", str44);
                            }
                            onStr45Changed:{
                                if (completedFlag)    setProperty(44, "status", str45);
                            }
                            onStr46Changed:{
                                if (completedFlag)    setProperty(45, "status", str46);
                            }
                            onStr47Changed:{
                                if (completedFlag)    setProperty(46, "status", str47);
                            }
                            onStr48Changed:{
                                if (completedFlag)    setProperty(47, "status", str48);
                            }
                            onStr49Changed:{
                                if (completedFlag)    setProperty(48, "status", str49);
                            }
                            onStr50Changed:{
                                if (completedFlag)    setProperty(49, "status", str50);
                            }
                            onStr51Changed:{
                                if (completedFlag)    setProperty(50, "status", str51);
                            }
                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: status === "正常" ? "#32c9c9" :(status === "异常" ? "#ec3030" : gConfig.textColor[currentIndex]);font.pixelSize: 32}
                        }
                        highlightRangeMode: ListView.StrictlyEnforceRange
                    }
                }
                // Rectangle {
                //        x: 824
                //        y: 134
                //        width: 32
                //        height: 32
                //        color: m_nLeft ? "#32c9c9" : "#ff8c38"
                //        radius: 16;           // 圆角，通过圆角来画出一个圆形窗体出来
                //        clip: true;            // 截断，在Rectangle控件内的子控件，超出他本身大小后会被截断
                //        Text{
                //            width: 20
                //            height: 15
                //            anchors.centerIn: parent
                //            color: gConfig.textColor[currentIndex]
                //            //text: m_nLeft ? String.fromCharCode(0x2714) : String.fromCharCode(0x2718)// 对号1
                //            text:String.fromCharCode(0x2714)
                //            font.pixelSize: 20
                //     }
                //    }
                // Rectangle {
                //        x: 824
                //        y: 214
                //        width: 32
                //        height: 32
                //        color: m_nRight ? "#32c9c9" : "#ff8c38"
                //       // opacity: 0.5;          // 透明度，缺省为1
                //        radius: 16;           // 圆角，通过圆角来画出一个圆形窗体出来
                //        clip: true;            // 截断，在Rectangle控件内的子控件，超出他本身大小后会被截断
                //        Text{
                //            width: 22
                //            height: 15
                //            anchors.centerIn: parent
                //            color: gConfig.textColor[currentIndex]
                //           // text: !m_nRight ? String.fromCharCode(0x2714) : String.fromCharCode(0x2718)
                //            text: String.fromCharCode(0x2714) 
                //            font.pixelSize: 20
                //     }
                //    }
            }
        }

        // 电池信息
        Component {
            id : battery_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle{
                    x: 420
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel

                            property string str1:m_strBattOverTempFault
                            property string str2:m_strInsulationFault
                            property string str3:m_strCellLessVoltWarning
                            property string str4:m_strCellOverVoltWarning
                            property string str5:m_strBattLessElectWarning
                            property string str6:m_strPositiveRelayAdhesion
                            property string str7:m_strPTCRelayAdhesion
                            property string str8:m_strSOHWarning
                            property string str9:m_strPositionRelaySts
                            property string str10:m_strPTCRelaySts
                            property string str11:m_strBattVoltImbalance
                            property string str12:m_strDischgOverCurrent
                            property string str13:m_strChgOverCurrent
                            property string str14:m_strItselfCANerror
                            property string str15:m_strBattGeneralLessVolt
                            property string str16:m_strBattGeneralOverVolt
                            property string str17:m_strBMSHardwareFault
                            property string str18:m_strCANerror
                            property string str19:m_strCCsignConnetSts
                            property string str20:m_strPrechargeSts
                            property string str21:m_strBMSsts
                            property string str22:m_strBackChgEnb
                            property string str23:m_strWarmModel
                            property string str24:m_strBalanceSts
                            property string str25:m_strSOCLow
                            property string str26:m_strCurrentSensorFault
                            property string str27:m_strTempSensorFault
                            property string str28:m_strNegativeRelayAdhesion
                            property string str29:m_strPrechgRelaySts
                            property string str30:m_strNegativeRelaySts
                            property string str31:m_strDCchgPositiveRelaySts
                            property string str32:m_strDCchgGunOverTempFault
                            property string str33:m_strCellCollectLineCutFault
                            property string str34:m_strPrechgRelayAdhesion
                            property string str35:m_strDCchgPositiveRelayAdhesion
                            property string str36:m_strWakeUpType
                            property string str37:m_strBattTempImbalanceFault
                            property string str38:m_strBattLessTempFault
                            property string str39:m_strWarmSts
                            property string str40:m_strGeneralVolt
                            property string str41:m_strGeneralCurrent
                            property string str42:m_strSOC
                            property string str43:m_strBattSerialData
                            property string str44:m_strCellVoltSensorFault
                            property string str45:m_strGeneralVoltSensorFault
                            property string str46:m_str12VLessVolt
                            property string str47:m_str12VOverVolt
                            property string str48:m_strBattMaxTemp
                            property string str49:m_strBattMaxTempCode
                            property string str50:m_strBattMinTemp
                            property string str51:m_strBattMinTempCode
                            property string str52:m_strDCchgGunBaseTemp0
                            property string str53:m_strDCchgGunBaseTemp1
                            property string str54:m_strAverageTemp
                            property string str55:m_strSystemFaultLevel
                            property string str56:m_strHVlock
                            property string str57:m_strPowerDownReq
                            property string str58:m_strBMSMaxDischgPower
                            property string str59:m_strBMSMaxChgPower
                            property string str60:m_strDCchgVoltDemand
                            property string str61:m_strDCchgCurrentDemand
                            property string str62:m_strSystemStsCode
                            property bool completedFlag: false

                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '电池温度过高故障', status : str1})
                                    id_tabModel.append({name : '绝缘报警', status : str2})
                                    id_tabModel.append({name : '单体欠压报警', status : str3})
                                    id_tabModel.append({name : '单体过压报警', status : str4})
                                    id_tabModel.append({name : '动力电池馈电报警', status : str5})
                                    id_tabModel.append({name : '主正继电器粘连报警', status : str6})
                                    id_tabModel.append({name : 'PTC继电器粘连报警未做', status : str7})
                                    id_tabModel.append({name : 'SOH报警', status : str8})
                                    id_tabModel.append({name : '主正继电器状态', status : str9})
                                    id_tabModel.append({name : 'PTC继电器状态', status : str10})
                                    id_tabModel.append({name : '电池组电压不均衡', status : str11})
                                    id_tabModel.append({name : '放电过流（包括短路）', status : str12})
                                    id_tabModel.append({name : '充电过流', status : str13})
                                    id_tabModel.append({name : '模块内部通讯故障未做', status : str14})
                                    id_tabModel.append({name : '电池组总电压过低报警', status : str15})
                                    id_tabModel.append({name : '电池组总电压过高报警', status : str16})
                                    id_tabModel.append({name : 'BMS硬件故障未做', status : str17})
                                    id_tabModel.append({name : '通讯故障', status : str18})
                                    id_tabModel.append({name : 'CC信号连接状态', status : str19})
                                    id_tabModel.append({name : '预充状态', status : str20})
                                    id_tabModel.append({name : 'BMS状态', status : str21})
                                    id_tabModel.append({name : '回馈充电使能', status : str22})
                                    id_tabModel.append({name : '加热模式', status : str23})
                                    id_tabModel.append({name : '均衡状态', status : str24})
                                    id_tabModel.append({name : 'Soc过低', status : str25})
                                    id_tabModel.append({name : '电流传感器故障', status : str26})
                                    id_tabModel.append({name : '温度传感器故障', status : str27})
                                    id_tabModel.append({name : '主负继电器粘连', status : str28})
                                    id_tabModel.append({name : '预充继电器状态', status : str29})
                                    id_tabModel.append({name : '主负继电器状态', status : str30})
                                    id_tabModel.append({name : '快充正继电器状态', status : str31})
                                    id_tabModel.append({name : '快充枪过温故障', status : str32})
                                    id_tabModel.append({name : '单体采集线束断线故障', status : str33})
                                    id_tabModel.append({name : '预充继电器粘连', status : str34})
                                    id_tabModel.append({name : '快充正继电器粘连', status : str35})
                                    id_tabModel.append({name : '保留唤醒类型', status : str36})
                                    id_tabModel.append({name : '电池温度不均衡故障', status : str37})
                                    id_tabModel.append({name : '电池温度过低故障', status : str38})
                                    id_tabModel.append({name : '加热状态', status : str39})
                                    id_tabModel.append({name : '总电压', status : str40})
                                    id_tabModel.append({name : '总电流', status : str41})
                                    id_tabModel.append({name : 'SOC', status : str42})
                                    id_tabModel.append({name : '电池串数', status : str43})
                                    id_tabModel.append({name : '单体电压传感器故障', status : str44})
                                    id_tabModel.append({name : '总压传感器故障', status : str45})
                                    id_tabModel.append({name : '12V低压欠压', status : str46})
                                    id_tabModel.append({name : '12V低压过压', status : str47})
                                    id_tabModel.append({name : '电池最高温度', status : str48})
                                    id_tabModel.append({name : '电池最高温度传感器号', status : str49})
                                    id_tabModel.append({name : '电池最低温度', status : str50})
                                    id_tabModel.append({name : '电池最低温度传感器号', status : str51})
                                    id_tabModel.append({name : '快充枪底座温度0', status : str52})
                                    id_tabModel.append({name : '快充枪底座温度1', status : str53})
                                    id_tabModel.append({name : '平均温度', status : str54})
                                    id_tabModel.append({name : '系统故障等级', status : str55})
                                    id_tabModel.append({name : '高压互锁', status : str56})
                                    id_tabModel.append({name : '请求下电', status : str57})
                                    id_tabModel.append({name : 'BMS最大放电功率', status : str58})
                                    id_tabModel.append({name : 'BMS最大充电功率', status : str59})
                                    id_tabModel.append({name : '快充电压需求', status : str60})
                                    id_tabModel.append({name : '快充电流需求', status : str61})
                                    id_tabModel.append({name : '系统状态代码', status : str62})

                                    completedFlag = true;
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BATTERY_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BATTERY13EF_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BATTERY33EF_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BATTERY11EF_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag)    setProperty(7, "status", str8);
                            }
                            onStr9Changed:{
                                if (completedFlag)    setProperty(8, "status", str9);
                            }
                            onStr10Changed:{
                                if (completedFlag)    setProperty(9, "status", str10);
                            }
                            onStr11Changed:{
                                if (completedFlag)    setProperty(10, "status", str11);
                            }
                            onStr12Changed:{
                                if (completedFlag)    setProperty(11, "status", str12);
                            }
                            onStr13Changed:{
                                if (completedFlag)    setProperty(12, "status", str13);
                            }
                            onStr14Changed:{
                                if (completedFlag)    setProperty(13, "status", str14);
                            }
                            onStr15Changed:{
                                if (completedFlag)    setProperty(14, "status", str15);
                            }
                            onStr16Changed:{
                                if (completedFlag)    setProperty(15, "status", str16);
                            }
                            onStr17Changed:{
                                if (completedFlag)    setProperty(16, "status", str17);
                            }
                            onStr18Changed:{
                                if (completedFlag)    setProperty(17, "status", str18);
                            }
                            onStr19Changed:{
                                if (completedFlag)    setProperty(18, "status", str19);
                            }
                            onStr20Changed:{
                                if (completedFlag)    setProperty(19, "status", str20);
                            }
                            onStr21Changed:{
                                if (completedFlag)    setProperty(20, "status", str21);
                            }
                            onStr22Changed:{
                                if (completedFlag)    setProperty(21, "status", str22);
                            }
                            onStr23Changed:{
                                if (completedFlag)    setProperty(22, "status", str23);
                            }
                            onStr24Changed:{
                                if (completedFlag)    setProperty(23, "status", str24);
                            }
                            onStr25Changed:{
                                if (completedFlag)    setProperty(24, "status", str25);
                            }
                            onStr26Changed:{
                                if (completedFlag)    setProperty(25, "status", str26);
                            }
                            onStr27Changed:{
                                if (completedFlag)    setProperty(26, "status", str27);
                            }
                            onStr28Changed:{
                                if (completedFlag)    setProperty(27, "status", str28);
                            }
                            onStr29Changed:{
                                if (completedFlag)    setProperty(28, "status", str29);
                            }
                            onStr30Changed:{
                                if (completedFlag)    setProperty(29, "status", str30);
                            }
                            onStr31Changed:{
                                if (completedFlag)    setProperty(30, "status", str31);
                            }
                            onStr32Changed:{
                                if (completedFlag)    setProperty(31, "status", str32);
                            }
                            onStr33Changed:{
                                if (completedFlag)    setProperty(32, "status", str33);
                            }
                            onStr34Changed:{
                                if (completedFlag)    setProperty(33, "status", str34);
                            }
                            onStr35Changed:{
                                if (completedFlag)    setProperty(34, "status", str35);
                            }
                            onStr36Changed:{
                                if (completedFlag)    setProperty(35, "status", str36);
                            }
                            onStr37Changed:{
                                if (completedFlag)    setProperty(36, "status", str37);
                            }
                            onStr38Changed:{
                                if (completedFlag)    setProperty(37, "status", str38);
                            }
                            onStr39Changed:{
                                if (completedFlag)    setProperty(38, "status", str39);
                            }
                            onStr40Changed:{
                                if (completedFlag)    setProperty(39, "status", str40);
                            }
                            onStr41Changed:{
                                if (completedFlag)    setProperty(40, "status", str41);
                            }
                            onStr42Changed:{
                                if (completedFlag)    setProperty(41, "status", str42);
                            }
                            onStr43Changed:{
                                if (completedFlag)    setProperty(42, "status", str43);
                            }
                            onStr44Changed:{
                                if (completedFlag)    setProperty(43, "status", str44);
                            }
                            onStr45Changed:{
                                if (completedFlag)    setProperty(44, "status", str45);
                            }
                            onStr46Changed:{
                                if (completedFlag)    setProperty(45, "status", str46);
                            }
                            onStr47Changed:{
                                if (completedFlag)    setProperty(46, "status", str47);
                            }
                            onStr48Changed:{
                                if (completedFlag)    setProperty(47, "status", str48);
                            }
                            onStr49Changed:{
                                if (completedFlag)    setProperty(48, "status", str49);
                            }
                            onStr50Changed:{
                                if (completedFlag)    setProperty(49, "status", str50);
                            }
                            onStr51Changed:{
                                if (completedFlag)    setProperty(50, "status", str51);
                            }
                            onStr52Changed:{
                                if (completedFlag)    setProperty(51, "status", str52);
                            }
                            onStr53Changed:{
                                if (completedFlag)    setProperty(52, "status", str53);
                            }
                            onStr54Changed:{
                                if (completedFlag)    setProperty(53, "status", str54);
                            }
                            onStr55Changed:{
                                if (completedFlag)    setProperty(54, "status", str55);
                            }
                            onStr56Changed:{
                                if (completedFlag)    setProperty(55, "status", str56);
                            }
                            onStr57Changed:{
                                if (completedFlag)    setProperty(56, "status", str57);
                            }
                            onStr58Changed:{
                                if (completedFlag)    setProperty(57, "status", str58);
                            }
                            onStr59Changed:{
                                if (completedFlag)    setProperty(58, "status", str59);
                            }
                            onStr60Changed:{
                                if (completedFlag)    setProperty(59, "status", str60);
                            }
                            onStr61Changed:{
                                if (completedFlag)    setProperty(60, "status", str61);
                            }
                            onStr62Changed:{
                                if (completedFlag)    setProperty(61, "status", str62);
                            }
                        }
                        //显示滚动条
//                        ScrollBar.vertical: ScrollBar {
//                            policy: ScrollBar.AlwaysOn
//                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }

//                        delegate: Text {
//                            //height: list.height / 8
//                            text: name + '       ' + status
//                            color: "#ffffff"
//                            font.pointSize: 16
//                        }

                        // 这个设置，滚动将达到预期效果
                        highlightRangeMode: ListView.StrictlyEnforceRange
                    }
                }
                Rectangle {
                    id: bary_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            bary_rectange_id.state  ==  'selected'  ?  bary_rectange_id.state  =  ""  :  bary_rectange_id.state  =  'selected';
                            if (bary_rectange_id.state  ==  'selected')
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_BAR, 1)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BATTERY_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BATTERY13EF_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BATTERY33EF_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BATTERY11EF_DATA)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_BAR, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: bary_rectange_id
                                color: "#5B89FF"

                            }
                        }
                    ]
                }
            }
        }
        // 主驱信息
        Component {
            id : mainDrive_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle{
                    x: 420
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {

                            id: id_tabModel
                            property string str1:m_strMotSpeed
                            property string str2:m_strMotTorque
                            property string str3:m_strRotaryWarning
                            property string str4:m_strIntePass
                            property string str5:m_strGearSts
                            property string str6:m_strBackBrake
                            property string str7:m_strAccPdlSts
                            property string str8:m_strBusbardischarg
                            property string str9:m_strBrakeActive
                            property string str10:m_strMotSpeedValid
                            property string str11:m_strOverCurrentFault
                            property string str12:m_strPowerLimtWarning
                            property string str13:m_strMCUTempWarning
                            property string str14:m_strMotTempWarning
                            property string str15:m_strBusbarOverVoltFault
                            property string str16:m_strBusbarLessVoltFault
                            property string str17:m_strSpeedControlValid
                            property string str18:m_strGeneralFaultWarning
                            property string str19:m_strGearWarning
                            property string str20:m_strHoldReq
                            property string str21:m_strApdlPercent

                            property bool completedFlag: false

                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '电机转速', status : str1})
                                    id_tabModel.append({name : '电机转矩', status : str2})
                                    id_tabModel.append({name : '旋变报警', status : str3})
                                    id_tabModel.append({name : '自检通过', status : str4})
                                    id_tabModel.append({name : '档位状态', status : str5})
                                    id_tabModel.append({name : '回馈制动', status : str6})
                                    id_tabModel.append({name : '油门踏板状态', status : str7})
                                    id_tabModel.append({name : '母线放电', status : str8})
                                    id_tabModel.append({name : '刹车激活', status : str9})
                                    id_tabModel.append({name : '电机速度有效性', status : str10})
                                    id_tabModel.append({name : '过流故障', status : str11})
                                    id_tabModel.append({name : '功率限幅报警', status : str12})
                                    id_tabModel.append({name : '控制器温度报警', status : str13})
                                    id_tabModel.append({name : '电机温度报警', status : str14})
                                    id_tabModel.append({name : '母线过压故障', status : str15})
                                    id_tabModel.append({name : '母线欠压故障', status : str16})
                                    id_tabModel.append({name : '速度控制生效', status : str17})
                                    id_tabModel.append({name : '综合故障报警', status : str18})
                                    id_tabModel.append({name : '档位告警', status : str19})
                                    id_tabModel.append({name : '驻车请求', status : str20})
                                    id_tabModel.append({name : '油门行程', status : str21})

                                    completedFlag  = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_MAINDRI_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag)    setProperty(7, "status", str8);
                            }
                            onStr9Changed:{
                                if (completedFlag)    setProperty(8, "status", str9);
                            }
                            onStr10Changed:{
                                if (completedFlag)    setProperty(9, "status", str10);
                            }
                            onStr11Changed:{
                                if (completedFlag)    setProperty(10, "status", str11);
                            }
                            onStr12Changed:{
                                if (completedFlag)    setProperty(11, "status", str12);
                            }
                            onStr13Changed:{
                                if (completedFlag)    setProperty(12, "status", str13);
                            }
                            onStr14Changed:{
                                if (completedFlag)    setProperty(13, "status", str14);
                            }
                            onStr15Changed:{
                                if (completedFlag)    setProperty(14, "status", str15);
                            }
                            onStr16Changed:{
                                if (completedFlag)    setProperty(15, "status", str16);
                            }
                            onStr17Changed:{
                                if (completedFlag)    setProperty(16, "status", str17);
                            }
                            onStr18Changed:{
                                if (completedFlag)    setProperty(17, "status", str18);
                            }
                            onStr19Changed:{
                                if (completedFlag)    setProperty(18, "status", str19);
                            }
                            onStr20Changed:{
                                if (completedFlag)    setProperty(19, "status", str20);
                            }
                            onStr21Changed:{
                                if (completedFlag)    setProperty(20, "status", str21);
                            }

                        }
                        //显示滚动条
//                        ScrollBar.vertical: ScrollBar {
//                            policy: ScrollBar.AlwaysOn
//                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }

//                        delegate: Text {
//                            //height: list.height / 8
//                            text: name + '       ' + status
//                            color: "#ffffff"
//                            font.pointSize: 16
//                        }

                        // 这个设置，滚动将达到预期效果
                        highlightRangeMode: ListView.StrictlyEnforceRange
                    }
                }

                Rectangle {
                    id: mainDri_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            mainDri_rectange_id.state  ==  'selected'  ?  mainDri_rectange_id.state  =  ""  :  mainDri_rectange_id.state  =  'selected';
                            if (mainDri_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_MAINDRI_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_MAINDRI, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_MAINDRI, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: mainDri_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }
            }

        }


        // 制动信息
        Component {
            id : brake_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle{
                    //x: 435
                    x: 420
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel

                            property string str1:m_strEHB_WorkSts
                            property string str2:m_strBrakePress
                            property string str3:m_strpedalPercent
                            property string str4:m_strPistonDisplacement
                            property string str5:m_strTargetPress
                            property string str6:m_strParkReq
                            property string str7:m_strBrakeSts
                            property string str8:m_strfaultLevel
                            property string str9:m_strfaultCode1
                            property string str10:m_strfaultCode2
                            property string str11:m_strfaultCode3
                            property string str12:m_nBrakeSts60
                            property string str13:m_nParklight_sts
                            property string str14:m_nFaultlight_sts
                            property string str15:m_nSwitch_sts
                            property string str16:m_nSystem_sts
                            property string str17:m_nFault_message

                            property bool completedFlag: false

                            Component.onCompleted:{ 
                                    id_tabModel.append({name : 'EHB工作状态', status : str1 })
                                    id_tabModel.append({name : '当前制动压力', status : str2})
                                    id_tabModel.append({name : '踏板开度', status : str3})
                                    id_tabModel.append({name : '主缸活塞位移', status : str4})
                                    id_tabModel.append({name : '目标压力', status : str5})
                                    id_tabModel.append({name : '驻车制动请求', status : str6})
                                    id_tabModel.append({name : '制动状态', status : str7})
                                    id_tabModel.append({name : '故障等级', status : str8})
                                    id_tabModel.append({name : '故障码1', status : str9})
                                    id_tabModel.append({name : '故障码2', status : str10})
                                    id_tabModel.append({name : '故障码3', status : str11})
                                    id_tabModel.append({name : '刹车灯请求', status : str12})
                                    id_tabModel.append({name : '驻车灯状态', status : str13})
                                    id_tabModel.append({name : '故障灯状态', status : str14})
                                    id_tabModel.append({name : '开关状态', status : str15})
                                    id_tabModel.append({name : '系统状态', status : str16})
                                    id_tabModel.append({name : '故障信息', status : str17})

                                    completedFlag = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BRAKE_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BRAKE60_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BRAKE5F_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag)    setProperty(7, "status", str8);
                            }
                            onStr9Changed:{
                                if (completedFlag)    setProperty(8, "status", str9);
                            }
                            onStr10Changed:{
                                if (completedFlag)    setProperty(9, "status", str10);
                            }
                            onStr11Changed:{
                                if (completedFlag)    setProperty(10, "status", str11);
                            }
                            onStr12Changed:{
                                if (completedFlag)    setProperty(11, "status", str12);
                            }
                            onStr13Changed:{
                                if (completedFlag)    setProperty(12, "status", str13);
                            }
                            onStr14Changed:{
                                if (completedFlag)    setProperty(13, "status", str14);
                            }
                            onStr15Changed:{
                                if (completedFlag)    setProperty(14, "status", str15);
                            }
                            onStr16Changed:{
                                if (completedFlag)    setProperty(15, "status", str16);
                            }
                            onStr17Changed:{
                                if (completedFlag)    setProperty(16, "status", str17);
                            }

                        }
                        //显示滚动条
//                        ScrollBar.vertical: ScrollBar {
//                            policy: ScrollBar.AlwaysOn
//                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding:100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }

//                        delegate: Text {
//                            //height: list.height / 8
//                            text: name + '       ' + status
//                            color: "#ffffff"
//                            font.pointSize: 16
//                        }

                        // 这个设置，滚动将达到预期效果
                        //highlightRangeMode: ListView.StrictlyEnforceRange
                    }
                }
                /*Rectangle {
                                x: 824
                                y: 536
                                property int brkSts:m_nBrakeSts
                                width: 32
                                height: 32
                                color: brkSts ? "#32c9c9" : "#8892a5"
                                radius: 16;
                                clip: true;
                                Text{
                                        width: 20
                                        height: 15
                                        anchors.centerIn: parent
                                        color: "#ffffff"
                                        text: String.fromCharCode(0x2714)
                                        font.pixelSize: 20
                                    }
                            }*/
                Rectangle {
                    id: bak_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            bak_rectange_id.state  ==  'selected'  ?  bak_rectange_id.state  =  ""  :  bak_rectange_id.state  =  'selected';
                            if (bak_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BRAKE_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BRAKE60_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_BRAKE5F_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_BRAKE, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_BRAKE, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: bak_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }

            }
        }

        // EPS信息
        Component {
            id : eps_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle{
                    x: 420
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {

                            id: id_tabModel
                            property string str1:m_strWorkModel
                            property string str2:m_strTargeTangle
                            property string str3:m_strWheelPalstance
                            //property string str4:m_strTargetTorque
                            property string str4:m_strAutoCMD_model
                            property string str5:m_strCurrentangle
                            property string str6:m_strOut_torque
                            property string str7:m_strTarget_torque
                            property string str8:m_strFaultCode_92

                            property bool completedFlag: false
                           
                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '工作模式', status : str1 })
                                    id_tabModel.append({name : '目标角度', status : str2})
                                    id_tabModel.append({name : '方向盘角速度', status : str3})
                                    //id_tabModel.append({name : '输出扭矩', status : str4})
                                    id_tabModel.append({name : '自动指令模式', status : str4})
                                    id_tabModel.append({name : '当前角度', status : str5})
                                    id_tabModel.append({name : '输出扭矩', status : str6})
                                    id_tabModel.append({name : '目标扭矩', status : str7})
                                    id_tabModel.append({name : '故障码', status : str8})

                                    completedFlag = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_EPS_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_EPS5C_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            // onStr4Changed:{
                            //     if (completedFlag)    setProperty(3, "status", str4);
                            // }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag)    setProperty(7, "status", str8);
                            }
                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }
                    }
                }
                Rectangle {
                    id: eps_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            eps_rectange_id.state  ==  'selected'  ?  eps_rectange_id.state  =  ""  :  eps_rectange_id.state  =  'selected';
                            if (eps_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_EPS_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_EPS, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_EPS, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: eps_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }

            }
        }
        // 12VDC信息
        Component {
            id : dc12_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle{
                    x: 420
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel
                            property string str1:m_strOutEnable
                            property string str2:m_strState
                            property string str3:m_strINVoltage
                            property string str4:m_strINCurrent
                            property string str5:m_strDCDCTemperature
                            property string str6:m_strOverTemperature
                            property string str7:m_strOut_voltage
                            property string str8:m_strOut_current
                            property string str9:m_strIn_over_current
                            property string str10:m_strOut_over_current
                            property string str11:m_strIn_over_voltage
                            property string str12:m_strIn_less_voltage
                            property string str13:m_strOut_over_voltage
                            property string str14:m_strOut_less_voltage

                            property bool completedFlag: false
                           
                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '输出使能', status : str1 })
                                    id_tabModel.append({name : '状态', status : str2})
                                    id_tabModel.append({name : '输入电压', status : str3})
                                    id_tabModel.append({name : '输入电流', status : str4})
                                    id_tabModel.append({name : 'DCDC温度', status : str5})
                                    id_tabModel.append({name : '过温', status : str6})
                                    id_tabModel.append({name : '输出电压', status : str7})
                                    id_tabModel.append({name : '输出电流', status : str8})
                                    id_tabModel.append({name : '输入过流', status : str9})
                                    id_tabModel.append({name : '输出过流', status : str10})
                                    id_tabModel.append({name : '输入过压', status : str11})
                                    id_tabModel.append({name : '输入欠压', status : str12})
                                    id_tabModel.append({name : '输出过压', status : str13})
                                    id_tabModel.append({name : '输出欠压', status : str14})
                                    completedFlag = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_12VDC_DATA)
                                }
                            onStr1Changed:{
                               if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                               if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                               if (completedFlag)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                               if (completedFlag)    setProperty(7, "status", str8);
                            }
                            onStr9Changed:{
                               if (completedFlag)    setProperty(8, "status", str9);
                            }
                            onStr10Changed:{
                               if (completedFlag)    setProperty(9, "status", str10);
                            }
                            onStr11Changed:{
                               if (completedFlag)    setProperty(10, "status", str11);
                            }
                            onStr12Changed:{
                               if (completedFlag)    setProperty(11, "status", str12);
                            }
                            onStr13Changed:{
                               if (completedFlag)    setProperty(12, "status", str13);
                            }
                            onStr14Changed:{
                               if (completedFlag)    setProperty(13, "status", str14);
                            }
                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }
                    }
                }
                /*Rectangle {
                                x: 824
                                y: 130
                                property int enableSts:m_nOutEnable
                                width: 32
                                height: 32
                                color: enableSts ? "#32c9c9" : "#8892a5"
                                radius: 16;
                                clip: true;
                                Text{
                                        width: 20
                                        height: 15
                                        anchors.centerIn: parent
                                        color: "#ffffff"
                                        text: String.fromCharCode(0x2714)
                                        font.pixelSize: 20
                                    }
                            }*/

                /*Rectangle {
                                x: 824
                                y: 536
                                property int overTempera:m_nOverTemperature
                                width: 32
                                height: 32
                                color: overTempera ? "#ec3030" : "#8892a5"
                                radius: 16;
                                clip: true;
                                Text{
                                        width: 20
                                        height: 15
                                        anchors.centerIn: parent
                                        color: "#ffffff"
                                        text: String.fromCharCode(0x2714)
                                        font.pixelSize: 20
                                    }
                            }*/
                Rectangle {
                    id: dc12_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            dc12_rectange_id.state  ==  'selected'  ?  dc12_rectange_id.state  =  ""  :  dc12_rectange_id.state  =  'selected';
                            if (dc12_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_12VDC_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_12VDC, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_12VDC, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: dc12_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }

            }
        }

        // 48VDC信息
        Component {
            id : dc48_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle{
                    x: 420
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel
                            property string str1:m_strOUTVolt
                            property string str2:m_strOUTCurrent
                            property string str3:m_strDCSts
                            property string str4:m_strOUTCutDownSts
                            property string str5:m_strFaultLevel
                            property string str6:m_strRadiatorTemp
                            property string str7:m_strINCutDownSts
                            property bool completedFlag: false
                           
                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '输出电压', status : str1 })
                                    id_tabModel.append({name : '输出电流', status : str2})
                                    id_tabModel.append({name : 'DC状态', status : str3})
                                    id_tabModel.append({name : '输出切断状态', status : str4})
                                    id_tabModel.append({name : '故障等级', status : str5})
                                    id_tabModel.append({name : '散热器温度', status : str6})
                                    id_tabModel.append({name : '输入切断状态', status : str7})
                                    completedFlag = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_48VDC_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag)    setProperty(6, "status", str7);
                            }
                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }
                    }
                }
                Rectangle {
                    id: dc48_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            dc48_rectange_id.state  ==  'selected'  ?  dc48_rectange_id.state  =  ""  :  dc48_rectange_id.state  =  'selected';
                            if (dc48_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_48VDC_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_48VDC, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_48VDC, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: dc48_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }

            }
        }

        // 风机信息
        Component {
            id : fan_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle{
                    x: 420
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel
                            property string str1:m_strFaultLevl
                            property string str2:m_strModSts
                            property string str3:m_strEnSts
                            property string str4:m_strPrechargeAllow
                            property string str5:m_strDirSts
                            property string str6:m_strActTorValid
                            property string str7:m_strActTor
                            property string str8:m_strDirSts
                            property string str9:m_strActSpd

                            property string str10:m_strDCVolt
                            property string str11:m_strDCCur
                            property string str12:m_strACCur

                            property string str13:m_strMotorMinAvaTor
                            property string str14:m_strMotorMaxAvaTor
                            property string str15:m_strMotorIGBTTemp
                            property string str16:m_strMTemp
                            property string str17:m_strCTemp

                            property string str18:m_strMOvSpdSts
                            property string str19:m_strMBlockSts
                            property string str20:m_strMOvTempSts
                            property string str21:m_strMOvCurSts
                            property string str22:m_strMShrSts
                            property string str23:m_strMShrGrdSts
                            property string str24:m_strCOvTempSts
                            property string str25:m_strCAuxBatSts
                            property string str26:m_strPreChaSts
                            property string str27:m_strIGBTModSts
                            property string str28:m_strIGBTOvTempSts
                            property string str29:m_strIGBTOvCurSts
                            property string str30:m_strCOvVoltSts
                            property string str31:m_strCLowVoltSts
                            property string str32:m_strIGBTTempSenSts
                            property string str33:m_strCANFault
                            property string str34:m_strMTempSenSts
                            property string str35:m_strCTempSenSts
                            property string str36:m_strCVoltSenSts
                            property string str37:m_strCCurSenSts
                            property string str38:m_strACCurSenSts
                            property string str39:m_strCTranFaultSts
                            property string str40:m_strMCutOffSts                   
                            property bool completedFlag: false
                           
                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '电机故障等级', status : str1 })
                                    id_tabModel.append({name : '电机运行模式', status : str2})
                                    id_tabModel.append({name : '电机控制器允许运行', status : str3})
                                    id_tabModel.append({name : '电机控制器高压上电允许', status : str4})
                                    id_tabModel.append({name : '电机实际运行方向', status : str5})
                                    id_tabModel.append({name : '电机反馈转矩有效', status : str6})
                                    id_tabModel.append({name : '电机反馈转速有效', status : str7})
                                    id_tabModel.append({name : '电机实际转矩', status : str8})
                                    id_tabModel.append({name : '电机实际转速', status : str9})
                                    id_tabModel.append({name : '电机直流母线电压', status : str10})
                                    id_tabModel.append({name : '电机直流母线电流', status : str11})
                                    id_tabModel.append({name : '电机交流电流有效值', status : str12})
                                    id_tabModel.append({name : '电机允许最大回馈转矩', status : str13})
                                    id_tabModel.append({name : '电机允许最大驱动转矩', status : str14})
                                    id_tabModel.append({name : '电机IGBT温度', status : str15})
                                    id_tabModel.append({name : '电机温度', status : str16})
                                    id_tabModel.append({name : '电机控制器温度', status : str17})
                                    id_tabModel.append({name : '电机超速故障', status : str18})
                                    id_tabModel.append({name : '电机堵转故障', status : str19})
                                    id_tabModel.append({name : '电机超温故障', status : str20})
                                    id_tabModel.append({name : '电机过流故障', status : str21})
                                    id_tabModel.append({name : '电机电缆短路故障', status : str22})
                                    id_tabModel.append({name : '电机交流侧对地短路', status : str23})
                                    id_tabModel.append({name : '电机控制器过温故障', status : str24})
                                    id_tabModel.append({name : '电机控制器控制板低压异常', status : str25})
                                    id_tabModel.append({name : '电机控制器预充电异常', status : str26})
                                    id_tabModel.append({name : '电机控制器IGBT模块故障', status : str27})
                                    id_tabModel.append({name : '电机控制器IGBT过温故障', status : str28})
                                    id_tabModel.append({name : '电机控制器IGBT过流故障', status : str29})
                                    id_tabModel.append({name : '电机控制器母线过压故障', status : str30})
                                    id_tabModel.append({name : '电机控制器母线欠压故障', status : str31})
                                    id_tabModel.append({name : '电机控制器IGBT温度传感器故障', status : str32})
                                    id_tabModel.append({name : '电机控制器CAN故障', status : str33})
                                    id_tabModel.append({name : '电机温度传感器故障', status : str34})
                                    id_tabModel.append({name : '电机控制器温度传感器故障', status : str35})
                                    id_tabModel.append({name : '电机控制器母线电压传感器故障', status : str36})
                                    id_tabModel.append({name : '电机控制器母线电流传感器故障', status : str37})
                                    id_tabModel.append({name : '电机控制器相电流传感器故障', status : str38})
                                    id_tabModel.append({name : '电机旋变故障', status : str39})
                                    id_tabModel.append({name : '电机断路故障', status : str40})

                                    completedFlag = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_FAN902_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_FANA02_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_FANB02_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_FANC02_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag)    setProperty(7, "status", str8);
                            }
                            onStr9Changed:{
                                if (completedFlag)    setProperty(8, "status", str9);
                            }
                            onStr10Changed:{
                                if (completedFlag)    setProperty(9, "status", str10);
                            }
                            onStr11Changed:{
                                if (completedFlag)    setProperty(10, "status", str11);
                            }
                            onStr12Changed:{
                                if (completedFlag)    setProperty(11, "status", str12);
                            }
                            onStr13Changed:{
                                if (completedFlag)    setProperty(12, "status", str13);
                            }
                            onStr14Changed:{
                                if (completedFlag)    setProperty(13, "status", str14);
                            }
                            onStr15Changed:{
                                if (completedFlag)    setProperty(14, "status", str15);
                            }
                            onStr16Changed:{
                                if (completedFlag)    setProperty(15, "status", str16);
                            }
                            onStr17Changed:{
                                if (completedFlag)    setProperty(16, "status", str17);
                            }
                            onStr18Changed:{
                                if (completedFlag)    setProperty(17, "status", str18);
                            }
                            onStr19Changed:{
                                if (completedFlag)    setProperty(18, "status", str19);
                            }
                            onStr20Changed:{
                                if (completedFlag)    setProperty(19, "status", str20);
                            }
                            onStr21Changed:{
                                if (completedFlag)    setProperty(20, "status", str21);
                            }
                            onStr22Changed:{
                                if (completedFlag)    setProperty(21, "status", str22);
                            }
                            onStr23Changed:{
                                if (completedFlag)    setProperty(22, "status", str23);
                            }
                            onStr24Changed:{
                                if (completedFlag)    setProperty(23, "status", str24);
                            }
                            onStr25Changed:{
                                if (completedFlag)    setProperty(24, "status", str25);
                            }
                            onStr26Changed:{
                                if (completedFlag)    setProperty(25, "status", str26);
                            }
                            onStr27Changed:{
                                if (completedFlag)    setProperty(26, "status", str27);
                            }
                            onStr28Changed:{
                                if (completedFlag)    setProperty(27, "status", str28);
                            }
                            onStr29Changed:{
                                if (completedFlag)    setProperty(28, "status", str29);
                            }
                            onStr30Changed:{
                                if (completedFlag)    setProperty(29, "status", str30);
                            }
                            onStr31Changed:{
                                if (completedFlag)    setProperty(30, "status", str31);
                            }
                            onStr32Changed:{
                                if (completedFlag)    setProperty(31, "status", str32);
                            }
                            onStr33Changed:{
                                if (completedFlag)    setProperty(32, "status", str33);
                            }
                            onStr34Changed:{
                                if (completedFlag)    setProperty(33, "status", str34);
                            }
                            onStr35Changed:{
                                if (completedFlag)    setProperty(34, "status", str35);
                            }
                            onStr36Changed:{
                                if (completedFlag)    setProperty(35, "status", str36);
                            }
                            onStr37Changed:{
                                if (completedFlag)    setProperty(36, "status", str37);
                            }
                            onStr38Changed:{
                                if (completedFlag)    setProperty(37, "status", str38);
                            }
                            onStr39Changed:{
                                if (completedFlag)    setProperty(38, "status", str39);
                            }
                            onStr40Changed:{
                                if (completedFlag)    setProperty(39, "status", str40);
                            }
                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }
                    }
                }
                Rectangle {
                    id: fan_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            fan_rectange_id.state  ==  'selected'  ?  fan_rectange_id.state  =  ""  :  fan_rectange_id.state  =  'selected';
                            if (fan_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_FAN902_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_FANA02_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_FANB02_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_FANC02_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_FAN, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_FAN, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: fan_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }

            }
        }

        // 左扫盘信息
        Component {
            id : left_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]

                Rectangle{
                    x: 435
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel
                            property string str1:m_strMainVoltage
                            property string str2:m_strCurrentMotcurrent
                            property string str3:m_strEnableSts
                            property string str4:m_strWheelSts
                            property string str5:m_strMotTemperature
                            property string str6:m_strMotCurrentSpeed
                            property string str7:m_strOverCurrent
                            property string str8:m_strOverVoltage
                            property string str9:m_strSweepOverTemperature
                            property string str10:m_strLochedRotor
                            property string str11:m_strHallSignalError
                            property string str12:m_strMotFualtItself
                            property bool completedFlag: false
                           
                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '母线电压', status : str1 })
                                    id_tabModel.append({name : '当前电机电流', status : str2})
                                    id_tabModel.append({name : '使能状态', status : str3})
                                    id_tabModel.append({name : '方向状态', status : str4})
                                    id_tabModel.append({name : '电机温度', status : str5})
                                    id_tabModel.append({name : '电机实际转速', status : str6})
                                    id_tabModel.append({name : '过流', status : str7})
                                    id_tabModel.append({name : '过压', status : str8})
                                    id_tabModel.append({name : '过温', status : str9})
                                    id_tabModel.append({name : '堵转', status : str10})
                                    id_tabModel.append({name : '霍尔信号错误', status : str11})
                                    id_tabModel.append({name : '电机内部故障', status : str12})
                                    completedFlag = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_LEFTSWEEP_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag && slType)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag && slType)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag && slType)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag && slType)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag && slType)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag && slType)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag && slType)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag && slType)    setProperty(7, "status", str8);
                            }
                            onStr9Changed:{
                                if (completedFlag && slType)    setProperty(8, "status", str9);
                            }
                            onStr10Changed:{
                                if (completedFlag && slType)    setProperty(9, "status", str10);
                            }
                            onStr11Changed:{
                                if (completedFlag && slType)    setProperty(10, "status", str11);
                            }
                            onStr12Changed:{
                                if (completedFlag && slType)    setProperty(11, "status", str12);
                            }
                    }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }
                    }
                }
                Rectangle {
                    id: left_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            left_rectange_id.state  ==  'selected'  ?  left_rectange_id.state  =  ""  :  left_rectange_id.state  =  'selected';
                            if (left_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_LEFTSWEEP_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_LEFT, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_LEFT, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: left_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }

            }
        }

        // 右扫盘信息
        Component {
            id : right_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]
                Rectangle{
                    x: 435
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel
                            property string str1:m_strMainVoltage
                            property string str2:m_strCurrentMotcurrent
                            property string str3:m_strEnableSts
                            property string str4:m_strWheelSts
                            property string str5:m_strMotTemperature
                            property string str6:m_strMotCurrentSpeed
                            property string str7:m_strOverCurrent
                            property string str8:m_strOverVoltage
                            property string str9:m_strSweepOverTemperature
                            property string str10:m_strLochedRotor
                            property string str11:m_strHallSignalError
                            property string str12:m_strMotFualtItself
                            property bool completedFlag: false
                           
                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '母线电压', status : str1 })
                                    id_tabModel.append({name : '当前电机电流', status : str2})
                                    id_tabModel.append({name : '使能状态', status : str3})
                                    id_tabModel.append({name : '方向状态', status : str4})
                                    id_tabModel.append({name : '电机温度', status : str5})
                                    id_tabModel.append({name : '电机实际转速', status : str6})
                                    id_tabModel.append({name : '过流', status : str7})
                                    id_tabModel.append({name : '过压', status : str8})
                                    id_tabModel.append({name : '过温', status : str9})
                                    id_tabModel.append({name : '堵转', status : str10})
                                    id_tabModel.append({name : '霍尔信号错误', status : str11})
                                    id_tabModel.append({name : '电机内部故障', status : str12})
                                    completedFlag = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_RIGHTSWEEP_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag && srType)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag && srType)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag && srType)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag && srType)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag && srType)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag && srType)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag && srType)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag && srType)    setProperty(7, "status", str8);
                            }
                            onStr9Changed:{
                                if (completedFlag && srType)    setProperty(8, "status", str9);
                            }
                            onStr10Changed:{
                                if (completedFlag && srType)    setProperty(9, "status", str10);
                            }
                            onStr11Changed:{
                                if (completedFlag && srType)    setProperty(10, "status", str11);
                            }
                            onStr12Changed:{
                                if (completedFlag && slType)    setProperty(11, "status", str12);
                        }
                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }
                    }
                }
                Rectangle {
                    id: right_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            right_rectange_id.state  ==  'selected'  ?  right_rectange_id.state  =  ""  :  right_rectange_id.state  =  'selected';
                            if (right_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_RIGHTSWEEP_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_RIGHT, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_RIGHT, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: right_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }

            }
        }

        // 高压水泵信息
        Component {
            id : highPrePumps_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]
                Rectangle{
                    x: 435
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel
                            property string str1:m_strHigMotspeed
                            //property string str2:m_strMCUintSts
                            property string str2:m_strMOTBusbarVolt
                            property string str3:m_strMotTemp
                            property string str4:m_strIGBTTemp
                            property string str5:m_strMOT_current_AC
                            property string str6:m_strMOTFaultCodeSign
                            property string str7:m_strMCUintSts
                            property string str8:m_strMCUModelSts

                            property bool completedFlag: false
                           
                            Component.onCompleted:{ 
                                    id_tabModel.append({name : '电动/发电机转速', status : str1 })
                                    //id_tabModel.append({name : '电机控制器自检状态', status : str2})
                                    id_tabModel.append({name : '电机母线电压(UDC)', status : str2})
                                    id_tabModel.append({name : '电机温度(MT)', status : str3})
                                    id_tabModel.append({name : '模块温度(CT)', status : str4})
                                    id_tabModel.append({name : '电机交流输出电流', status : str5})
                                    id_tabModel.append({name : '电机故障码信号(MErr)', status : str6})
                                    id_tabModel.append({name : '电机控制器自检状态', status : str7})
                                    id_tabModel.append({name : '控制模式状态字', status : str8})
                                    
                                    completedFlag = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_HIGPREPUM15_DATA)
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_HIGPREPUM16_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag)    setProperty(7, "status", str8);
                            }

                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color: gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }
                    }
                }
                Rectangle {
                    id: highPrePumps_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            highPrePumps_rectange_id.state  ==  'selected'  ?  highPrePumps_rectange_id.state  =  ""  :  highPrePumps_rectange_id.state  =  'selected';
                            if (highPrePumps_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_HIGPREPUM15_DATA)
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_HIGPREPUM16_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_HIGPREDUMP, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_HIGPREDUMP, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: highPrePumps_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }

            }
        }
        // 通讯信息
        Component {
            id : communication_content_id
            Rectangle {
                width: 1446
                height: 770
                // color: "#2b2b2b"
                color: gConfig.background[currentIndex]
                Rectangle{
                    x: 435
                    y: 124
                    width: 670
                    height: 612
                    // color: "#2b2b2b"
                    color: gConfig.background[currentIndex]
                    ListView {
                        id: list
                        anchors.fill : parent
                        spacing: 36
                        //orientation: ListView.Horizontal
                        model: ListModel {
                            id: id_tabModel
                            property string str1:statuscode_id.commuSts[m_nBMS_CANerror]
                            property string str2:statuscode_id.commuSts[m_nMCU_CANerror]
                            property string str3:statuscode_id.commuSts[m_nEHB_CANerror]
                            property string str4:statuscode_id.commuSts[m_nEPB_CANerror]
                            property string str5:statuscode_id.commuSts[m_nEPS_CANerror]
                            property string str6:statuscode_id.commuSts[m_nDC48V_CANerror]
                            property string str7:statuscode_id.commuSts[m_nAC_CANerror]
                            property string str8:statuscode_id.commuSts[m_nADU_CANerror]
                            property string str9:statuscode_id.commuSts[m_nICU_CANerror]
                            property string str10:statuscode_id.commuSts[m_nDC12V_CANerror]
                            property string str11:statuscode_id.commuSts[m_nGPS_CANerror]
                            property string str12:statuscode_id.commuSts[m_nFJI_CANerror]
                            property string str13:statuscode_id.commuSts[m_nWP_CANerror]
                            property string str14:statuscode_id.commuSts[m_nSPL_CANerror]
                            property string str15:statuscode_id.commuSts[m_nSPR_CANerror]

                            property bool completedFlag: false
                           
                            Component.onCompleted:{ 
                                    id_tabModel.append({name : 'BMS通讯故障', status : str1 })
                                    id_tabModel.append({name : 'MCU通讯故障', status : str2})
                                    id_tabModel.append({name : 'EHB通讯故障', status : str3})
                                    id_tabModel.append({name : 'EPB通讯故障', status : str4})
                                    id_tabModel.append({name : 'EPS通讯故障', status : str5})
                                    id_tabModel.append({name : '48VDC通讯故障', status : str6})
                                    id_tabModel.append({name : '空调通讯故障', status : str7})
                                    id_tabModel.append({name : '无人通讯故障', status : str8})
                                    id_tabModel.append({name : '显示屏通讯故障', status : str9})
                                    id_tabModel.append({name : '12VDC通讯故障', status : str10})
                                    id_tabModel.append({name : 'GPS通讯故障', status : str11})
                                    id_tabModel.append({name : '风机通讯故障', status : str12})
                                    id_tabModel.append({name : '水泵通讯故障', status : str13})
                                    id_tabModel.append({name : '左扫刷通讯故障', status : str14})
                                    id_tabModel.append({name : '右扫刷通讯故障', status : str15})

                                    completedFlag = true
                                    item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_COMMUNI_DATA)
                                }
                            onStr1Changed:{
                                if (completedFlag)    setProperty(0, "status", str1);
                            }
                            onStr2Changed:{
                                if (completedFlag)    setProperty(1, "status", str2);
                            }
                            onStr3Changed:{
                                if (completedFlag)    setProperty(2, "status", str3);
                            }
                            onStr4Changed:{
                                if (completedFlag)    setProperty(3, "status", str4);
                            }
                            onStr5Changed:{
                                if (completedFlag)    setProperty(4, "status", str5);
                            }
                            onStr6Changed:{
                                if (completedFlag)    setProperty(5, "status", str6);
                            }
                            onStr7Changed:{
                                if (completedFlag)    setProperty(6, "status", str7);
                            }
                            onStr8Changed:{
                                if (completedFlag)    setProperty(7, "status", str8);
                            }
                            onStr9Changed:{
                                if (completedFlag)    setProperty(8, "status", str9);
                            }
                            onStr10Changed:{
                                if (completedFlag)    setProperty(9, "status", str10);
                            }
                            onStr11Changed:{
                                if (completedFlag)    setProperty(10, "status", str11);
                            }
                            onStr12Changed:{
                                if (completedFlag)    setProperty(11, "status", str12);
                            }
                            onStr13Changed:{
                                if (completedFlag)    setProperty(12, "status", str13);
                            }
                            onStr14Changed:{
                                if (completedFlag)    setProperty(13, "status", str14);
                            }
                            onStr15Changed:{
                                if (completedFlag)    setProperty(14, "status", str15);
                            }

                        }

                        delegate: Row {
                            Text {text: name; leftPadding: 200 - contentWidth; width: 300;color: gConfig.textColor[currentIndex]; font.pixelSize: 32}
                            Text {text: status; leftPadding: 100; width: 300;color:  gConfig.textColor[currentIndex];font.pixelSize: 32}
                        }
                    }
                }
                Rectangle {
                    id: communication_rectange_id
                    x: 40
                    y: 40
                    color: gConfig.tabButtonColor[currentIndex]
                    width: 120
                    height: 60
                    Text {
                        width: 48
                        height: 34
                        anchors.centerIn: parent
                        color: gConfig.textColor[currentIndex]
                        text: qsTr("开始")
                        font.pixelSize: 24
                        font.styleName: "Regular"
                    }
                    MouseArea  {
                        anchors.fill:  parent
                        onClicked:  {
                            communication_rectange_id.state  ==  'selected'  ?  communication_rectange_id.state  =  ""  :  communication_rectange_id.state  =  'selected';
                            if (communication_rectange_id.state  ==  'selected')
                            {
                                item_id.qmlSignalUpdateData(TDMsgType.DiagnosisType.DIAGNOSIS_COMMUNI_DATA)
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_COMMU, 1)
                            }else
                            {
                                //item_id.qmlSignalDiagnosis(TDMsgType.DiagnosisType.DIAGNOSIS_COMMU, 0)
                            }
                        }
                    }
                    states: [
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: communication_rectange_id
                                color: "#5B89FF"
                            }
                        }
                    ]
                }
                // Rectangle {
                //        x: 824
                //        y: 130
                //        width: 32
                //        height: 32
                //        color: m_nBMS_CANerror ? "#ec3030" : "#8892a5"
                //        radius: 16;           // 圆角，通过圆角来画出一个圆形窗体出来
                //        clip: true;            // 截断，在Rectangle控件内的子控件，超出他本身大小后会被截断
                //        Text{
                //            width: 20
                //            height: 15
                //            anchors.centerIn: parent
                //            color: gConfig.textColor[currentIndex]
                //            text: m_nBMS_CANerror ? String.fromCharCode(0x2714) : String.fromCharCode(0x2718)// 对号1
                //            font.pixelSize: 20
                //     }
                //    }
                // Rectangle {
                //        x: 824
                //        y: 210
                //        width: 32
                //        height: 32
                //        color: m_nMCU_CANerror ? "#ec3030" : "#8892a5"
                //       // opacity: 0.5;        
                //        radius: 16;          
                //        clip: true;           
                //        Text{
                //            width: 22
                //            height: 15
                //            anchors.centerIn: parent
                //            color: gConfig.textColor[currentIndex]
                //            text: m_nMCU_CANerror ? String.fromCharCode(0x2714) : String.fromCharCode(0x2718)
                //            font.pixelSize: 20
                //     }
                //    }

            }
        }

    }
    Button{
           id: nextTab_page_id
            x: 1420
            y: 100
            width: 26
            height: 90
            background: Rectangle {
                // color: "#3b3b3b"
                color: gConfig.tabButtonColor[currentIndex]
                Image {
                    width: 26
                    height: 26
                    anchors.verticalCenter: parent.verticalCenter
                    source:  nextTab[currentIndex]
                 }
            }
                    onClicked: {
                        if (indexTemp >= 11)
                        {
                            indexTemp = 11
                        }else
                        {
                            indexTemp++
                        }


                 }
    }
    Button{
           id: lastTab_page_id
            x: 0
            y: 100
            width: 26
            height: 90
            background: Rectangle {
                // color: "#3b3b3b"
                color: gConfig.tabButtonColor[currentIndex]
                Image {
                    width: 26
                    height: 26
                    anchors.verticalCenter: parent.verticalCenter
                    source:  lastTab[currentIndex]
                 }
            }
                    onClicked: {
                        if (indexTemp == 0)
                        {
                            indexTemp = 0
                        }else
                        {
                            indexTemp--
                        }


                 }
    }
   
     Connections {
        target: CUIDataHandle
        
        function onSignalDiagnosisIO(nTurnLeft, nTurnRight, nWorkFlag, nTrunOnFlag,
                           nLowBeam, nSmallLight, nAutoDrive, nEmergencyFlash, nStop)
        {
            m_nLeft = nTurnLeft
            m_nRight = nTurnRight
            m_nWorkFlag = nWorkFlag
            m_nTrunOnFlag = nTrunOnFlag
            m_nLowBeam_I = nLowBeam
            m_nSmallLight = nSmallLight
            m_nAutoDrive = nAutoDrive
            m_nEmergencyFlash = nEmergencyFlash
            m_nStop = nStop
        }

        function onSignalDiagnosisIO71(nBrakeOil_line, nBox_up, nBox_dowm, nBox_Arrive, nChengGan_Arrive,
                             nEban_switch, nBoxDoor_switch, nLeftBrush_arrive, nRightBrush_arrive, nLeftBrush_open,
                             nLeftBrush_close, nRightBrush_open, nRightBrush_close, ndustbin_returnSwitch, nWaterLine_show)
                             {
                                m_nBrakeOil_line = nBrakeOil_line
                                m_nBox_up = nBox_up
                                m_nBox_dowm = nBox_dowm
                                m_nBox_Arrive = nBox_Arrive
                                m_nChengGan_Arrive = nChengGan_Arrive
                                m_nEban_switch = nEban_switch
                                m_nBoxDoor_switch = nBoxDoor_switch
                                m_nLeftBrush_arrive = nLeftBrush_arrive
                                m_nRightBrush_arrive = nRightBrush_arrive
                                m_nLeftBrush_open_s= nLeftBrush_open
                                m_nLeftBrush_close_s = nLeftBrush_close
                                m_nRightBrush_open_s= nRightBrush_open
                                m_nRightBrush_close_s = nRightBrush_close
                                m_ndustbin_returnSwitch = ndustbin_returnSwitch
                                m_strWaterLine_show = nWaterLine_show.toString() + "%"
                             }
        
        function onSignalDiagnosisIO78(nTurnLeftLight, nTurnRightLight, nLowBeam, nWorkLight_relay, nsmall_light,
                             nreversing_light, nbrake_light, nReversing_buzzer)
                             {
                                m_nTurnLeftLight = nTurnLeftLight
                                m_nTurnRightLight = nTurnRightLight
                                m_nLowBeam = nLowBeam
                                m_nWorkLight_relay = nWorkLight_relay
                                m_nsmall_light = nsmall_light
                                m_nreversing_light = nreversing_light
                                m_nbrake_light = nbrake_light
                                m_nReversing_buzzer = nReversing_buzzer
                             }
   
        function onSignalDiagnosisIO79(nBoxDoor_open, nBoxDoor_close, nLeftBrush_up, nLeftBrush_down, nLeftBrush_open,
                             nLeftBrush_close, nRightBrush_up, nRightBrush_down, nRightBrush_open, nRightBrush_close, nEban_switch_open,
                             nEban_switch_close, nXiZwitch_up, nXiZwitch_down, nDustbin_up, nDustbin_down, nLVWaterRoad_relay,
                             nSewagecyclevalve, nDelayCutDown)
                             {
                                m_nBoxDoor_open = nBoxDoor_open
                                m_nBoxDoor_close = nBoxDoor_close
                                m_nLeftBrush_up = nLeftBrush_up
                                m_nLeftBrush_down = nLeftBrush_down
                                m_nLeftBrush_open = nLeftBrush_open
                                m_nLeftBrush_close = nLeftBrush_close
                                m_nRightBrush_up = nRightBrush_up
                                m_nRightBrush_down = nRightBrush_down
                                m_nRightBrush_open = nRightBrush_open
                                m_nRightBrush_close = nRightBrush_close
                                m_nEban_switch_open = nEban_switch_open
                                m_nEban_switch_close = nEban_switch_close
                                m_nXiZwitch_up = nXiZwitch_up
                                m_nXiZwitch_down = nXiZwitch_down
                                m_nDustbin_up = nDustbin_up
                                m_nDustbin_down = nDustbin_down
                                m_nLVWaterRoad_relay = nLVWaterRoad_relay
                                m_nSewagecyclevalve = nSewagecyclevalve
                                m_nDelayCutDown = nDelayCutDown
                             }
        
        //诊断电池信息
        function onSignalDiagnosisBattery(nBattOverTempFault, nInsulationFault, nCellLessVoltWarning, nCellOverVoltWarning, nBattLessElectWarning, nPositiveRelayAdhesion,
                                nPTCRelayAdhesion, nSOHWarning, nPositionRelaySts, nPTCRelaySts, nBattVoltImbalance, nDischgOverCurrent,
                                nChgOverCurrent, nItselfCANerror, nBattGeneralLessVolt, nBattGeneralOverVolt, nBMSHardwareFault,
                                nCANerror, nCCsignConnetSts, nPrechargeSts, nBMSsts, nBackChgEnb, nWarmModel, nBalanceSts,
                                nSOCLow, nCurrentSensorFault, nTempSensorFault, nNegativeRelayAdhesion, nPrechgRelaySts, nNegativeRelaySts,
                                nDCchgPositiveRelaySts, nDCchgGunOverTempFault, nCellCollectLineCutFault, nPrechgRelayAdhesion, nDCchgPositiveRelayAdhesion,
                                nWakeUpType, nBattTempImbalanceFault, nBattLessTempFault, nWarmSts)
                                {
                                    m_strBattOverTempFault = statuscode_id.battOverTemp[nBattOverTempFault]
                                    m_strInsulationFault = statuscode_id.insuWarn[nInsulationFault]
                                    m_strCellLessVoltWarning = statuscode_id.insuWarn[nCellLessVoltWarning]
                                    m_strCellOverVoltWarning = statuscode_id.insuWarn[nCellOverVoltWarning]
                                    m_strBattLessElectWarning = statuscode_id.lessElcWarn[nBattLessElectWarning]
                                    m_strPositiveRelayAdhesion = statuscode_id.adhessWarn[nPositiveRelayAdhesion]
                                    m_strPTCRelayAdhesion = statuscode_id.adhessWarn[nPTCRelayAdhesion]
                                    m_strSOHWarning = statuscode_id.sohWarn[nSOHWarning]
                                    m_strPositionRelaySts = statuscode_id.relaySts[nPositionRelaySts]
                                    m_strPTCRelaySts = statuscode_id.relaySts[nPTCRelaySts]
                                    m_strBattVoltImbalance = statuscode_id.insuWarn[nBattVoltImbalance]
                                    m_strDischgOverCurrent = statuscode_id.insuWarn[nDischgOverCurrent]
                                    m_strChgOverCurrent = statuscode_id.insuWarn[nChgOverCurrent]
                                    m_strItselfCANerror = statuscode_id.sohWarn[nItselfCANerror]
                                    m_strBattGeneralLessVolt = statuscode_id.insuWarn[nBattGeneralLessVolt]
                                    m_strBattGeneralOverVolt = statuscode_id.insuWarn[nBattGeneralLessVolt]
                                    m_strBMSHardwareFault = statuscode_id.sohWarn[nBMSHardwareFault]
                                    m_strCANerror = statuscode_id.sohWarn[nCANerror]
                                    m_strCCsignConnetSts = statuscode_id.connecSts[nCCsignConnetSts]
                                    m_strPrechargeSts = statuscode_id.prechargeSts[nPrechargeSts]
                                    m_strBMSsts = statuscode_id.bmsSts[nBMSsts]
                                    m_strBackChgEnb = statuscode_id.backEnb[nBackChgEnb]
                                    m_strWarmModel = nWarmModel
                                    m_strBalanceSts = statuscode_id.balanceSts[nBalanceSts]
                                    m_strSOCLow = statuscode_id.socLow[nSOCLow]
                                    m_strCurrentSensorFault = statuscode_id.socLow[nCurrentSensorFault]
                                    m_strTempSensorFault = statuscode_id.socLow[nTempSensorFault]
                                    m_strNegativeRelayAdhesion = statuscode_id.adhessWarn[nNegativeRelayAdhesion]
                                    m_strPrechgRelaySts = statuscode_id.relaySts[nPrechgRelaySts]
                                    m_strNegativeRelaySts = statuscode_id.relaySts[nNegativeRelaySts]
                                    m_strDCchgPositiveRelaySts = statuscode_id.relaySts[nDCchgPositiveRelaySts]
                                    m_strDCchgGunOverTempFault = statuscode_id.socLow[nDCchgGunOverTempFault]
                                    m_strCellCollectLineCutFault = statuscode_id.socLow[nCellCollectLineCutFault]
                                    m_strPrechgRelayAdhesion = statuscode_id.adhessWarn[nPrechgRelayAdhesion]
                                    m_strDCchgPositiveRelayAdhesion = statuscode_id.adhessWarn[nDCchgPositiveRelayAdhesion]
                                    m_strWakeUpType = statuscode_id.wakeUpType[nWakeUpType]
                                    m_strBattTempImbalanceFault = statuscode_id.battBalan[nBattTempImbalanceFault]
                                    m_strBattLessTempFault = statuscode_id.battLess[nBattLessTempFault]
                                    m_strWarmSts = statuscode_id.warmSts[nWarmSts]
                                }
        function onSignalDiagnosisBattery13EF(nGeneralVolt, nGeneralCurrent, nSOC, nBattSerialData, nCellVoltSensorFault,
                                    nGeneralVoltSensorFault, n12VLessVolt, n12VOverVolt)
        {
            m_strGeneralVolt = nGeneralVolt.toString() + "V"
            m_strGeneralCurrent = nGeneralCurrent.toString() + "A"
            m_strSOC = nSOC.toString() + "%"
            m_strBattSerialData = nBattSerialData.toString();
            m_strCellVoltSensorFault = statuscode_id.insuWarn[nCellVoltSensorFault]
            m_strGeneralVoltSensorFault = statuscode_id.insuWarn[nGeneralVoltSensorFault]
            m_str12VLessVolt = statuscode_id.insuWarn[n12VLessVolt]
            m_str12VOverVolt = statuscode_id.insuWarn[n12VOverVolt]
        }

        function onSignalDiagnosisBattery33EF(nBattMaxTemp, nBattMaxTempCode, nBattMinTemp, nBattMinTempCode,
                                    nDCchgGunBaseTemp0,nDCchgGunBaseTemp1,nAverageTemp)
                                    {
                                        m_strBattMaxTemp = nBattMaxTemp.toString() + "℃"
                                        m_strBattMaxTempCode = nBattMaxTempCode.toString()
                                        m_strBattMinTemp = nBattMinTemp.toString() + "℃"
                                        m_strBattMinTempCode = nBattMinTempCode.toString()
                                        m_strDCchgGunBaseTemp0 = nDCchgGunBaseTemp0.toString() + "℃"
                                        m_strDCchgGunBaseTemp1 = nDCchgGunBaseTemp1.toString() + "℃"
                                        m_strAverageTemp = nAverageTemp.toString() + "℃"
                                    }
                                
        function onSignalDiagnosisBattery11EF(nSystemFaultLevel, nHVlock, nPowerDownReq, nBMSMaxDischgPower,
                                    nBMSMaxChgPower, nDCchgVoltDemand, nDCchgCurrentDemand, nSystemStsCode)
                                    {
                                        m_strSystemFaultLevel = statuscode_id.sysFault[nSystemFaultLevel]
                                        m_strHVlock = statuscode_id.hVLock[nHVlock]
                                        m_strPowerDownReq = statuscode_id.pwReq[nPowerDownReq]
                                        m_strBMSMaxDischgPower = nBMSMaxDischgPower.toString() + "kw"
                                        m_strBMSMaxChgPower = nBMSMaxChgPower.toString() + "kw"
                                        m_strDCchgVoltDemand = nDCchgVoltDemand.toString()
                                        m_strDCchgCurrentDemand = nDCchgCurrentDemand.toString()
                                        m_strSystemStsCode = nSystemStsCode.toString()
                                    }

        function onSignalDiagnosisMainDri(nMotSpeed, nMotTorque, nRotaryWarning, nIntePass,
                                nGearSts, nBackBrake, nAccPdlSts, nBusbardischarg,
                                nBrakeActive, nMotSpeedValid, nOverCurrentFault,
                                nPowerLimtWarning, nMCUTempWarning, nMotTempWarning, nBusbarOverVoltFault, nBusbarLessVoltFault,
                                nSpeedControlValid, nGeneralFaultWarning, nGearWarning, nHoldReq, nApdlPercent)
                                {
                                    m_strMotSpeed = nMotSpeed.toString() + "rpm"
                                    m_strMotTorque = nMotTorque.toString() + "%"
                                    m_strRotaryWarning = statuscode_id.otherWarn[nRotaryWarning]
                                    m_strIntePass = statuscode_id.intePass[nIntePass]
                                    m_strGearSts = statuscode_id.gearSts[nGearSts]
                                    m_strBackBrake = statuscode_id.backBk[nBackBrake]
                                    m_strAccPdlSts = statuscode_id.accSts[nAccPdlSts]
                                    m_strBusbardischarg = statuscode_id.busBadDis[nBusbardischarg]
                                    m_strBrakeActive = statuscode_id.brakeAct[nBrakeActive]
                                    m_strMotSpeedValid = statuscode_id.mainWarn[nMotSpeedValid]

                                    m_strOverCurrentFault = statuscode_id.otherWarn[nOverCurrentFault]
                                    m_strPowerLimtWarning = statuscode_id.otherWarn[nPowerLimtWarning]
                                    m_strMCUTempWarning = statuscode_id.otherWarn[nMCUTempWarning]
                                    m_strMotTempWarning = statuscode_id.otherWarn[nMotTempWarning]
                                    m_strBusbarOverVoltFault = statuscode_id.otherWarn[nBusbarOverVoltFault]
                                    m_strBusbarLessVoltFault = statuscode_id.otherWarn[nBusbarLessVoltFault]
                                    m_strSpeedControlValid = statuscode_id.backBk[nSpeedControlValid]
                                    m_strGeneralFaultWarning = statuscode_id.comSts[nGeneralFaultWarning]
                                    m_strGearWarning = statuscode_id.mainWarn[nGearWarning]
                                    m_strHoldReq = statuscode_id.mainWarn[nHoldReq]
                                    m_strApdlPercent = nApdlPercent.toString() + "%"

                                }
        function onSignalDiagnosisBrake(nEHB_WorkSts, nBrakePress, npedalPercent,
                                        nPistonDisplacement, nTargetPress,
                                        nParkReq, nBrakeSts, nfaultLevel)
                                    {
                                        m_strEHB_WorkSts = "0x" + nEHB_WorkSts.toString()
                                        m_strBrakePress = nBrakePress.toString() + "bar"
                                        m_strpedalPercent = npedalPercent.toString() + "%"
                                        m_strPistonDisplacement = nPistonDisplacement.toString() + "mm"
                                        m_strTargetPress = nTargetPress.toString() + "bar"
                                        m_strParkReq = "0x" + nParkReq.toString()
                                        m_strBrakeSts = "0x" + nBrakeSts.toString()
                                        m_strfaultLevel = "0x" + nfaultLevel.toString()
                                    }
        function onSignalDiagnosisBrake5F(nfaultCode1, nfaultCode2, nfaultCode3)
        {
            m_strfaultCode1 = "0x" + nfaultCode1.toString()
            m_strfaultCode2 = "0x" + nfaultCode2.toString()
            m_strfaultCode3 = "0x" + nfaultCode3.toString()
        }

        function onSignalDiagnosisBrake60(nBrakeSts, nParklight_sts, nFaultlight_sts, nSwitch_sts,
                                nSystem_sts, nFault_message)
                                {
                                    m_nBrakeSts60 = statuscode_id.brakelightSts[nBrakeSts]
                                    m_nParklight_sts = nParklight_sts.toString()
                                    m_nFaultlight_sts = nFaultlight_sts.toString()
                                    m_nSwitch_sts = nSwitch_sts.toString()
                                    m_nSystem_sts = nSystem_sts.toString()
                                    m_nFault_message = "0x" + nFault_message.toString()
                                }

        function onSignalDiagnosisEPS(nWorkModel,
                            nTargeTangle,
                            nWheelPalstance, nAutoCMD_model, nCurrentangle)
                            {
                                m_strWorkModel = "0x" + nWorkModel.toString()
                                m_strTargeTangle = nTargeTangle.toString() + "°"
                                m_strWheelPalstance = nWheelPalstance.toString() + "°/S"
                                m_strAutoCMD_model = "0x" + nAutoCMD_model.toString()
                                m_strCurrentangle = nCurrentangle.toString() + "°"
                            }

        function onSignalDiagnosisEPS5C(nOut_torque, nTarget_torque, nFaultCode_92)
        {
            m_strOut_torque = nOut_torque.toString() + "N.m"
            m_strTarget_torque = nTarget_torque.toString() + "N.m"
            m_strFaultCode_92 = "0x" + nFaultCode_92.toString()
        }

        function onSignalDiagnosis12VDC(nOutEnable,
                              nState,
                              nINVoltage,
                              nINCurrent,
                              nDCDCTemperature,
                              nOverTemperature,
                              nOut_voltage, nOut_current, nIn_over_current, 
                              nOut_over_current, nIn_over_voltage, nIn_less_voltage,
                              nOut_over_voltage, nOut_less_voltage)
                              {
                                  m_strOutEnable = statuscode_id.enableSwi[nOutEnable]
                                  m_strState = statuscode_id.outState[nState]
                                  m_strINVoltage = nINVoltage.toString() + "V"
                                  m_strINCurrent = nINCurrent.toString() + "A"
                                  m_strDCDCTemperature = nDCDCTemperature.toString() + "°C"
                                  m_strOverTemperature = statuscode_id.dcState[nOverTemperature]
                                  m_strOut_voltage = nOut_voltage.toString() + "V"
                                  m_strOut_current = nOut_current.toString() + "A"
                                  m_strIn_over_current = statuscode_id.dcState[nIn_over_current]
                                  m_strOut_over_current = statuscode_id.dcState[nOut_over_current]
                                  m_strIn_over_voltage = statuscode_id.dcState[nIn_over_voltage]
                                  m_strIn_less_voltage = statuscode_id.dcState[nIn_less_voltage]
                                  m_strOut_over_voltage = statuscode_id.dcState[nOut_over_voltage]
                                  m_strOut_less_voltage = statuscode_id.dcState[nOut_less_voltage]

                              }
        function onSignalDiagnosis48VDC(nOUTVolt,
                              nOUTCurrent,
                              nDCSts,
                              nOUTCutDownSts,
                              nFaultLevel,
                              nRadiatorTemp, nINCutDownSts)
                              {
                                 m_strOUTVolt = nOUTVolt.toString() + "V"
                                 m_strOUTCurrent = nOUTCurrent.toString() + "A"
                                 m_strDCSts = statuscode_id.vcState[nDCSts]
                                 m_strOUTCutDownSts = statuscode_id.cutSts[nOUTCutDownSts]
                                 m_strFaultLevel = statuscode_id.volWarn[nFaultLevel]
                                 m_strRadiatorTemp = nRadiatorTemp.toString() + "°C"
                                 m_strINCutDownSts = statuscode_id.cutSts[nINCutDownSts]
                              }
        
        function onSignalDiagnosisFan902(nFaultLevl,
                                    nModSts,
                                    nEnSts,
                                    nPrechargeAllow,
                                    nDirSts,
                                    nActTorValid,
                                    nActSpdValid,
                                    nActTor,
                                    nActSpd)
                                    {
                                        m_strFaultLevl = statuscode_id.fanFaultLevel[nFaultLevl]
                                        m_strModSts = statuscode_id.fanModeSts[nModSts]                                  
                                        m_strEnSts = statuscode_id.enSts[nEnSts]
                                        m_strPrechargeAllow = statuscode_id.preAllow[nPrechargeAllow]
                                        m_strDirSts = statuscode_id.dirSts[nDirSts]
                                        m_strActTorValid = statuscode_id.fanValid[nActTorValid]
                                        m_strActSpdValid = statuscode_id.fanValid[nActSpdValid]
                                        
                                        m_strActTor = nActTor.toString() + "Nm"
                                        m_strActSpd = nActSpd.toString() + "rpm"
                                    }
        function onSignalDiagnosisFanA02(nDCVolt, nDCCur, nACCur)
        {
            m_strDCVolt = nDCVolt.toString() + "V";
            m_strDCCur = nDCCur.toString() + "A";
            m_strACCur = nACCur.toString() + "A";
        }

        function onSignalDiagnosisFanB02(nMotorMinAvaTor, nMotorMaxAvaTor, nMotorIGBTTemp,
                               nMTemp, nCTemp)
                               {
                                   m_strMotorMinAvaTor = nMotorMinAvaTor.toString() + "Nm"
                                   m_strMotorMaxAvaTor = nMotorMaxAvaTor.toString() + "Nm"
                                   m_strMotorIGBTTemp = nMotorIGBTTemp.toString() + "°C"
                                   m_strMTemp = nMTemp.toString() + "°C"
                                   m_strCTemp = nCTemp.toString() + "°C"
                               }
        function onSignalDiagnosisFanC02(nMOvSpdSts, nMBlockSts, nMOvTempSts, nMOvCurSts, nMShrSts,
                                nMShrGrdSts, nCOvTempSts, nCAuxBatSts, nPreChaSts, nIGBTModSts,
                                nIGBTOvTempSts, nIGBTOvCurSts, nCOvVoltSts, nCLowVoltSts, nIGBTTempSenSts,
                                nCANFault, nMTempSenSts, nCTempSenSts, nCVoltSenSts, nCCurSenSts,
                                nACCurSenSts, nCTranFaultSts, nMCutOffSts)
                               {
                                    m_strMOvSpdSts = statuscode_id.fanC02Sts[nMOvSpdSts]
                                    m_strMBlockSts = statuscode_id.fanC02Sts[nMBlockSts]
                                    m_strMOvTempSts = statuscode_id.fanC02Sts[nMOvTempSts]
                                    m_strMOvCurSts = statuscode_id.fanC02Sts[nMOvCurSts]
                                    m_strMShrSts = statuscode_id.fanC02Sts[nMShrSts]
                                    m_strMShrGrdSts = statuscode_id.fanC02Sts[nMShrGrdSts]
                                    m_strCOvTempSts = statuscode_id.fanC02Sts[nCOvTempSts]
                                    m_strCAuxBatSts = statuscode_id.fanC02Sts[nCAuxBatSts]
                                    m_strPreChaSts = statuscode_id.fanC02Sts[nPreChaSts]
                                    m_strIGBTModSts = statuscode_id.fanC02Sts[nIGBTModSts]
                                    m_strIGBTOvTempSts = statuscode_id.fanC02Sts[nIGBTOvTempSts]
                                    m_strIGBTOvCurSts = statuscode_id.fanC02Sts[nIGBTOvCurSts]
                                    m_strCOvVoltSts = statuscode_id.fanC02Sts[nCOvVoltSts]
                                    m_strCLowVoltSts = statuscode_id.fanC02Sts[nCLowVoltSts]
                                    m_strIGBTTempSenSts = statuscode_id.fanC02Sts[nIGBTTempSenSts]
                                    m_strCANFault = statuscode_id.fanC02Sts[nCANFault]
                                    m_strMTempSenSts = statuscode_id.fanC02Sts[nMTempSenSts]
                                    m_strCTempSenSts = statuscode_id.fanC02Sts[nCTempSenSts]
                                    m_strCVoltSenSts = statuscode_id.fanC02Sts[nCVoltSenSts]
                                    m_strCCurSenSts = statuscode_id.fanC02Sts[nCCurSenSts]
                                    m_strACCurSenSts = statuscode_id.fanC02Sts[nACCurSenSts]
                                    m_strCTranFaultSts = statuscode_id.fanC02Sts[nCTranFaultSts]
                                    m_strMCutOffSts = statuscode_id.fanC02Sts[nMCutOffSts]
                               }
        function onSignalDiagnosisSweepDisk(nMainVoltage, nCurrentMotcurrent, nEnableSts,
                                  nWheelSts, nMotTemperature, nMotCurrentSpeed, nOverCurrent, nOverVoltage, nOverTemperature,
                                  nLochedRotor, nHallSignalError, nMotFualtItself, sweepType)
                                  {
                                      slType = false
                                      srType = false
                                      if (sweepType == 16)
                                      {
                                          slType = true
                                      }else
                                      {
                                          srType = true
                                      }
                                      m_strMainVoltage = nMainVoltage.toString() + "V"
                                      m_strCurrentMotcurrent = nCurrentMotcurrent.toString() + "A"
                                    
                                      if (nEnableSts == 0)
                                      {
                                          m_strEnableSts = "待机"
                                      }else
                                      {
                                          m_strEnableSts = "使能"
                                      }
                                      if (nWheelSts == 0)
                                      {
                                          m_strWheelSts = "无动作"
                                      }else if (nWheelSts == 1)
                                      {
                                          m_strWheelSts = "正转"
                                      }
                                      else
                                      {
                                          m_strWheelSts = "反转"
                                      }
                                      m_strMotTemperature = nMotTemperature.toString() + "°C"
                                      m_strMotCurrentSpeed = nMotCurrentSpeed.toString() + "rpm"
                                      if (nOverCurrent == 0)
                                      {
                                          m_strOverCurrent = "正常"
                                      }else
                                      {
                                          m_strOverCurrent = "过流"
                                      }
                                      if (nOverVoltage == 0)
                                      {
                                          m_strOverVoltage = "正常"
                                      }else
                                      {
                                          m_strOverVoltage = "过压"
                                      }
                                      if (nOverTemperature == 0)
                                      {
                                          m_strSweepOverTemperature = "正常"
                                      }else
                                      {
                                          m_strSweepOverTemperature = "过温"
                                      }
                                      if (nLochedRotor == 0)
                                      {
                                          m_strLochedRotor = "正常"
                                      }else
                                      {
                                          m_strLochedRotor = "堵转"
                                      }
                                      if (nHallSignalError == 0)
                                      {
                                          m_strHallSignalError = "正常"
                                      }else
                                      {
                                          m_strHallSignalError = "信号错误"
                                      }
                                      if (nMotFualtItself == 0)
                                      {
                                          m_strMotFualtItself = "正常"
                                      }else
                                      {
                                          m_strMotFualtItself = "内部故障"
                                      }


                                  }
        function onSignalDiagnosisHigPreDump15(nMOTspeed, nMOTBusbarVolt, nMotTemp,
                                     nIGBTTemp, nMOT_current_AC, nMOTFaultCodeSign)
        {
            m_strHigMotspeed = nMOTspeed.toString() + "rpm"
            m_strMOTBusbarVolt = nMOTBusbarVolt.toString() + "V"
            m_strMotTemp = nMotTemp.toString() + "°C"
            m_strIGBTTemp = nIGBTTemp.toString() + "°C"
            m_strMOT_current_AC = nMOT_current_AC.toString() + "A"
            m_strMOTFaultCodeSign = nMOTFaultCodeSign.toString()
        }
        function onSignalDiagnosisHigPreDump16(nMCUintSts, nMCUModelSts)
        {
            m_strMCUintSts = "0x" + nMCUintSts.toString()
            m_strMCUModelSts = nMCUModelSts.toString()
        }
        function onSignalDiagnosisCommu(nBMS_CANerror, nMCU_CANerror, nEHB_CANerror, nEPB_CANerror,
                              nEPS_CANerror, nDC48V_CANerror, nAC_CANerror, nADU_CANerror, nICU_CANerror, nDC12V_CANerror,
                              nGPS_CANerror, nFJI_CANerror, nWP_CANerror, nSPL_CANerror, nSPR_CANerror)
        {
            m_nBMS_CANerror = nBMS_CANerror
            m_nMCU_CANerror = nMCU_CANerror
            m_nEHB_CANerror = nEHB_CANerror
            m_nEPB_CANerror = nEPB_CANerror
            m_nEPS_CANerror = nEPS_CANerror
            m_nDC48V_CANerror = nDC48V_CANerror
            m_nAC_CANerror = nAC_CANerror
            m_nADU_CANerror = nADU_CANerror
            m_nICU_CANerror = nICU_CANerror
            m_nDC12V_CANerror = nDC12V_CANerror
            m_nGPS_CANerror = nGPS_CANerror
            m_nFJI_CANerror = nFJI_CANerror
            m_nWP_CANerror = nWP_CANerror
            m_nSPL_CANerror = nSPL_CANerror
            m_nSPR_CANerror = nSPR_CANerror
        }
   
    }
    Connections {
        target: item_id
        function onQmlSignalDiagnosis(val, onOff)
        {
            CUIDataHandle.slotDiagnosisCmd(val, onOff)
        }
        function onQmlSignalUpdateData(dataType)
        {
            CUIDataHandle.slotDiagnosisUpdateData(dataType)
        }
    }

}

